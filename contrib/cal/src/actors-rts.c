#define _GNU_SOURCE
#include <stdarg.h>
#include <stdlib.h>
#include <errno.h>
#ifndef __ERIKA__
#include <strings.h>
#include <semaphore.h>
#include <sched.h>
#else
#include <ee.h>
#endif
#include <string.h>
#include "actors-rts.h"
#include <pthread.h>
#include <limits.h>
#ifndef __ERIKA__
#include "xmlTrace.h"
#include "xmlParser.h"
#endif
#include "internal.h"

#define DEFAULT_FIFO_LENGTH	4096

static int arg_loopmax = INT_MAX;
/*
 * Memory organization for runtime:
 *
 *   We should make sure that data is aligned on CACHE_LINE_SIZE
 *   boundaries. In order to make it possible to migrate ports 
 *   between cpus, we allocate space for all ports on all processors.
 *
 *   Producers (OutputPorts):
 *     Global access: numWritten 
 *                    buffer
 *     Local access:  writePos
 *                    capacity
 *                    availSpace
 *                    numReaders
 *                    reader
 *
 *   Consumers (InputPorts):
 *     Global access: numRead 
 *                    buffer
 *     Local access:  readPos
 *                    capacity
 *                    availTokens
 *                    writer
 *
 *   care has to be taken so that:
 *     1. numRead/numWriten and buffers doesn't share the same cacheline.
 *     2. numRead/numWriten are protected with appropriate barriers
 */

#define FLAG_TIMING      0x01
#define FLAG_SINGLE_CPU  0x02

int numActiveActors=0;

void (*cb_add_threads)(int)=0;
void (*cb_register_thread)(int)=0;

static struct {
  int num_outputs;
  int num_inputs;
  int global_bytes;
  int local_bytes;
  int shared_bytes;
  int buffer_bytes;
} memory_statistics;


const int exit_code_terminate[1] = {-1};
const int exit_code_yield[1] = {-2};

/*
 * Error reporting
 */
void runtimeError(AbstractActorInstance *pInst, const char *format,...) {
  va_list ap;
  va_start(ap,format);
  vfprintf(stderr,format,ap);
  fprintf(stderr,"\n");
  va_end(ap);
  exit(1);
}

int rangeError(int x, int y, const char *filename, int line) {
  runtimeError(NULL, "Range check error: %d %d %s(%d)\n", 
	       x, y, filename, line);
  return 0;
}

#ifndef __ERIKA__
static inline unsigned long long READ_TIMER()
{
  unsigned long long result;
#if defined(__i386__)
  __asm__ __volatile__ ("rdtsc" : "=A" (result));
#else
  struct timeval tim;
  gettimeofday(&tim, NULL);
  result=tim.tv_sec*1000000+tim.tv_usec;
#endif  
  return result;
}
#else
static inline unsigned long long READ_TIMER(void)
{
  EE_UINT32 time1;
  EE_freetimer_get_value(&time1);
  return (~(EE_UINT32)0 - time1) / (CPU_FREQUENCY / 1000000);
}
#endif

static void add_timer(art_timer_t *timer,
          time_base_t *tb)
{
  long long tmp;

  tmp = READ_TIMER();
  *timer += tmp - *tb;
  *tb = tmp;
}

void actionTrace(AbstractActorInstance *instance,
                 int localActionIndex,
                 char *actionName)
{
  if (instance->traceFile)
    xmlTraceAction(instance->traceFile,
		   instance->firstActionIndex + localActionIndex);
}

unsigned int timestamp()
{
  static unsigned long long init=0;
  unsigned long long now=0;

  if(!init){
    init=READ_TIMER();
  }else{
    now=READ_TIMER() - init;
  }
  return (unsigned int)now;
}

#ifndef __ERIKA__
void enable_tracing(cpu_runtime_data_t *runtime, 
		    int numInstances, 
		    char *networkName)
{
  int i,j,k=0;
  FILE *netfile;
  int firstActionIndex = 0;
  AbstractActorInstance **instances = (AbstractActorInstance **) malloc(numInstances * sizeof(AbstractActorInstance *));

  for (i = 0 ; i < runtime->cpu_count ; i++) {
    char filename[32];
    cpu_runtime_data_t *cpu = &runtime[i];
    sprintf(filename,"trace_%d.xml",i);
    cpu->traceFile=xmlCreateTrace(filename);
    for(j=0; j<cpu->actors; j++)
    {
      AbstractActorInstance *pInstance=cpu->actor[j];
      pInstance->firstActionIndex=firstActionIndex;
      firstActionIndex += pInstance->actor->numActions;
      pInstance->traceFile=cpu->traceFile;
      instances[k++]=pInstance;
    }
  }

  netfile=xmlCreateTrace("net_trace.xml");
  xmlDeclareNetwork(netfile,networkName,instances,numInstances);
  xmlCloseTrace(netfile);

}
#endif

/*
 * Create runtime instances for all needed special cases
 */

#ifndef __ERIKA__
static pthread_mutex_t mutex;
#endif
static int sleepers;
static int curr_sleep_event;
static int terminate;

#define TIMING_PROBES

#define EXECUTE_NETWORK single_cpu_timed_execute_network
#define READ_BARRIER()
#define WRITE_BARRIER()
#define MUTEX_LOCK()
#define MUTEX_UNLOCK()
#include "actors_execute_network.h"
#undef EXECUTE_NETWORK
#undef READ_BARRIER
#undef WRITE_BARRIER
#undef MUTEX_LOCK
#undef MUTEX_UNLOCK

#ifndef __ERIKA__
#define EXECUTE_NETWORK multi_cpu_timed_execute_network
#define READ_BARRIER() rmb()
#define WRITE_BARRIER() wmb()
#define MUTEX_LOCK() pthread_mutex_lock(&mutex)
#define MUTEX_UNLOCK() pthread_mutex_unlock(&mutex)
#include "actors_execute_network.h"
#undef EXECUTE_NETWORK
#undef READ_BARRIER
#undef WRITE_BARRIER
#undef MUTEX_LOCK
#undef MUTEX_UNLOCK
#endif

#undef TIMING_PROBES

#define EXECUTE_NETWORK single_cpu_execute_network
#define READ_BARRIER()
#define WRITE_BARRIER()
#define MUTEX_LOCK()
#define MUTEX_UNLOCK()
#include "actors_execute_network.h"
#undef EXECUTE_NETWORK
#undef READ_BARRIER
#undef WRITE_BARRIER
#undef MUTEX_LOCK
#undef MUTEX_UNLOCK

#ifndef __ERIKA__
#define EXECUTE_NETWORK multi_cpu_execute_network
#define READ_BARRIER() rmb()
#define WRITE_BARRIER() wmb()
#define MUTEX_LOCK() pthread_mutex_lock(&mutex)
#define MUTEX_UNLOCK() pthread_mutex_unlock(&mutex)
#include "actors_execute_network.h"
#undef EXECUTE_NETWORK
#undef READ_BARRIER
#undef WRITE_BARRIER
#undef MUTEX_LOCK
#undef MUTEX_UNLOCK
#endif

/* 
 * We need to know processor affinity, etc before we allocate the true 
 * datastructures. For now we collect the actor layout in dummy objects
 * and unfolds them when execNetwork is invoked.
 */

typedef struct InputPort_1 {
  struct AbstractActorInstance_1 *owner;
  struct OutputPort_1 *output;
  int created;
  int capacity;
  InputPort *input;
} InputPort_1_t;

typedef struct OutputPort_1 {
  struct AbstractActorInstance_1 *owner;
  int created;
  int capacity;
  int buffer_bytes;
  int numberOfReaders;
  OutputPort *output;
} OutputPort_1_t;

typedef struct Parameter_1 {
  struct Parameter_1 *next;
  const char *key;
  const char *value;
} Parameter_1_t;

typedef struct AbstractActorInstance_1 {
  ActorClass *actorClass;
  int index;
  InputPort *input_list;
  InputPort_1_t *input;
  OutputPort *output_list;
  OutputPort_1_t *output;  
  Parameter_1_t *parameter;
  int affinity;
} ActorInstance_1_t;

AbstractActorInstance *createActorInstance(ActorClass *actorClass)
{
  ActorInstance_1_t *result;

  result = malloc(sizeof(*result));
  result->actorClass = actorClass;
  result->input = (InputPort_1_t*)calloc(actorClass->numInputPorts,
					     sizeof(*result->input));
  result->output = (OutputPort_1_t*)calloc(actorClass->numOutputPorts,
					      sizeof(*result->output));
  result->parameter = NULL;
  result->affinity = -1;
  return (AbstractActorInstance*)result;
}

OutputPort *createOutputPort(AbstractActorInstance *pInstance,
			     const char *portName,
			     int numberOfReaders)
{
  OutputPort *result = NULL;
  ActorInstance_1_t *instance = (ActorInstance_1_t*)pInstance;
  int i;

  for (i = 0 ; i < instance->actorClass->numOutputPorts ; i++) {
    if (strcmp(instance->actorClass->outputPortDescriptions[i].name, 
	       portName)  == 0) {
      instance->output[i].owner = instance;
      instance->output[i].created++;
      instance->output[i].numberOfReaders = numberOfReaders;
      result = (OutputPort*)&instance->output[i];
      break;
    }
  }
  
  return result;
}

InputPort *createInputPort(AbstractActorInstance *pInstance,
			   const char *portName,
			   int capacity)
{
  InputPort *result = NULL;
  ActorInstance_1_t *instance = (ActorInstance_1_t*)pInstance;
  int i;

  for (i = 0 ; i < instance->actorClass->numInputPorts ; i++) {
    if (strcmp(instance->actorClass->inputPortDescriptions[i].name, 
	       portName)  == 0) {
      instance->input[i].owner = instance;
      instance->input[i].created++;
      instance->input[i].capacity = capacity;
      result = (InputPort*)&instance->input[i];
      break;
    }
  }
  
  return result;
}

void connectPorts(OutputPort *outputPort, InputPort *inputPort)
{
  OutputPort_1_t *output = (OutputPort_1_t*)outputPort;
  InputPort_1_t *input = (InputPort_1_t*)inputPort;

  input->output = output;
}

void setParameter(AbstractActorInstance *pInstance,
		  const char *key,
		  const char *value)
{
  ActorInstance_1_t *instance = (ActorInstance_1_t*)pInstance;
  
  if (strcmp(key, "affinity") == 0) {
    instance->affinity = atoi(value);
  } else if (strcmp(key, "activeMode") == 0){
		instance->actorClass->actorExecMode=atoi(value);
	}else {
    Parameter_1_t *parameter = malloc(sizeof(*parameter));

    parameter->next = instance->parameter;
    parameter->key = key;
    if (value[0] != '$') {
      parameter->value = value;
    } else {
      char *tmp;

      tmp = getenv(&value[1]);
      if (tmp == NULL) {
	printf("No environment declaration for '%s'\n", &value[1]);
	exit(1);
      } else {
	parameter->value = strdup(tmp);
      }
    }
    instance->parameter = parameter;
  }
}

#ifndef __ERIKA__
static int nr_of_cpus(cpu_set_t *cpu_set)
{
  int result, i;

  for (result = 0, i = 0 ; cpu_set && i < CPU_SETSIZE ; i++) {
    if (CPU_ISSET(i, cpu_set)) { result++; }
  }
  return result;
}
#else
static int nr_of_cpus(cpu_set_t *cpu_set)
{
  return 1;
}
#endif

static int index_nodes(ActorInstance_1_t **instance,
		       int numInstances)
{
  int i;
  for (i = 0 ; i < numInstances ; i++) {
    int j;
	
    for (j =  i - 1 ; j >= 0 ; j--) {
      if (strcmp(instance[i]->actorClass->name,
		 instance[j]->actorClass->name) == 0) {
	instance[i]->index = instance[j]->index + 1;
	break;
      }
    }
  }
  return 0;
}

static int set_affinity(ActorInstance_1_t **instance,
			int numInstances,
			char *arg)
{
  int result = 0;
  char *p;
  int affinity = 0;

  for (p = arg ; p && *p && *p != '=' ; p++) {
    affinity = affinity * 10 + *p - '0';
  }
  while (p && *p && (*p == '=' || *p == ',')) {
    char *name;
    int len = 0;
    int index = 0;

    for (len = 0, p++, name = p ; p && *p && *p != '/' ; p++, len++) {}
    if (p && *p && *p == '/') {
      int i, found;
      for (p++ ; p && *p && *p != ',' ; p++) {
	index = index * 10 + *p - '0';
      }
      for (found = 0, i = 0 ; i < numInstances ; i++) {
	if (strncmp(instance[i]->actorClass->name, name, len) == 0 &&
	    len == strlen(instance[i]->actorClass->name) &&
	    instance[i]->index == index) {
	  instance[i]->affinity = affinity;
	  found = 1;
	  break;
	}
      }
      if (! found) {
	result = 1;
      }
    }
  }
  return result;
}

#ifndef __ERIKA__
static int set_instance_affinity(ActorInstance_1_t *instance,
				 AffinityID *config,
				 int numInstances)
{
  int i;
  char instanceName[128];
  sprintf(instanceName,"%s/%d",instance->actorClass->name,instance->index);
  for(i=0; i<numInstances; i++)
  {
    if(!config[i].flag
       && strcmp(instanceName,config[i].name)==0)
    {
      instance->affinity = config[i].affinity;
      config[i].flag=1;  // We don't need to compare/check this one again
      return i;
    }
  }
  return -1; // not found
}


/*
 * Sort the instances in the same order as they appear in the configuration
 * file and set their affinities
 */

static ActorInstance_1_t **sort_instances(ActorInstance_1_t **unsorted,
					  AffinityID *config,
                                          int numInstances) {
  ActorInstance_1_t **sorted=calloc(numInstances,sizeof(ActorInstance_1_t*));
  int i;

  for (i=0; i<numInstances; ++i) {
    int iSorted=set_instance_affinity(unsorted[i],config,numInstances);

    if (iSorted<0 || iSorted>=numInstances) {
      runtimeError(NULL,"sort_instances: not mentioned in config file: %s/%d\n",
		   unsorted[i]->actorClass->name,
		   unsorted[i]->index);
    }
    
    sorted[iSorted]=unsorted[i];
  }

  for (i=0; i<numInstances; ++i) {
    if (sorted[i]==NULL) {
      runtimeError(NULL,"sort_instances: instance not found: %s\n",
		   config[i].name);
    }
  }

  return sorted;
}

static void set_instance_fifo(ActorInstance_1_t **instance,ConnectID *connect,int numInstances)
{
  int i,j;

  for(i=0; i<numInstances; i++)
  {
    char instanceName[128];
    sprintf(instanceName,"%s/%d",instance[i]->actorClass->name,instance[i]->index);
    if(strcmp(instanceName,connect->dst)==0)
    {
      for (j = 0 ; j < instance[i]->actorClass->numInputPorts ; j++)
      {
        if (strcmp(instance[i]->actorClass->inputPortDescriptions[j].name,
                   connect->dst_port)  == 0) {
          instance[i]->input[j].capacity = connect->size;
          return;
        }
      }
    }
  }
}

static ActorInstance_1_t **set_config(ActorInstance_1_t **instances,
				      int numInstances,
				      char *filename)
{
  int numConnects;
  ActorInstance_1_t **sortedInstances=NULL;

  numConnects = xmlParser(filename, numInstances);
  if(numConnects >= 0)
  {
    int i;
    // Set actor instance infinity
    sortedInstances=
      sort_instances(instances,instanceAfinity,numInstances);

    //Set input ports fifo size
    for(i=0; i<numConnects; i++)
      set_instance_fifo(instances,&connects[i],numInstances);
  }

  return sortedInstances;
}
#endif

static int check_network(ActorInstance_1_t **instance,
			 int numInstances,
			 cpu_set_t *used_cpus,
			 int *flags,
			 int affinity_is_set)
{
  int result = 0;
  int i;
  cpu_set_t cpu_set;
  
  CPU_ZERO(&cpu_set);
  for (i = 0 ; i < numInstances ; i++) {
    // Check that we have processor affinity, else force single CPU mode
    if (instance[i]->affinity == -1) {
      if (!(*flags & FLAG_SINGLE_CPU)) {
//	printf("Forcing single CPU mode:%s\n", 
//               affinity_is_set? "" : " no affinity/configuration specified");
	*flags |= FLAG_SINGLE_CPU;
      }
      if (affinity_is_set)
	printf("No affinity %s/%d\n", instance[i]->actorClass->name,
	      instance[i]->index);
      // else: don't bitch about every actor!
      instance[i]->affinity = 0;
    }
  }
  for (i = 0 ; i < numInstances ; i++) {
    int j;
    
    if ((*flags & FLAG_SINGLE_CPU)) {
      instance[i]->affinity = 0;
    }
    CPU_SET(instance[i]->affinity, &cpu_set);
 
    // Check that everything has been connected
    for (j = 0 ; j < instance[i]->actorClass->numOutputPorts ; j++) {
      if (instance[i] != instance[i]->output[j].owner) {
	printf("Wrong owner\n");
	result = 1;
      }
      if (instance[i]->output[j].created != 1) {
	printf("Not created once %d\n", instance[i]->output[j].created);
	result = 1;
      }
    }
    for (j = 0 ; j < instance[i]->actorClass->numInputPorts ; j++) {
      if (instance[i]->input[j].created != 1) {
	printf("Not created once %d\n", instance[i]->input[j].created);
	result = 1;
      }
      if (instance[i] != instance[i]->input[j].owner) {
	printf("Wrong owner\n");
	result = 1;
      }
      if (instance[i]->input[j].output == NULL) {
	printf("Not connected\n");
	result = 1;
      }
    }

  }
#ifndef __ERIKA__
  {
    // Check that all needed cpus are present
    cpu_set_t old;
    int err;

    err = sched_getaffinity(0, sizeof(old), &old);
    if (err == 0) {
      int i, n_cpu;
      
      for (n_cpu = 0, i = 0 ; i < CPU_SETSIZE ; i++) {
	if (CPU_ISSET(i, &cpu_set)) {
	  cpu_set_t new;
	  
	  n_cpu++;
	  CPU_ZERO(&new);
	  CPU_SET(i, &new);
	  err = sched_setaffinity(0, sizeof(new), &new);
	  if (err) {
	    printf("System does not have a processor #%d\n", i);
	    result = 1;
	  }
	}
      }
      err = sched_setaffinity(0, sizeof(old), &old);
    }
  }
  if (result == 0 && used_cpus) {
    *used_cpus = cpu_set;
  }
#else
  *used_cpus = 1;
#endif
  return result;
}

static void info_network(ActorInstance_1_t **instance,
			 int numInstances,
			 cpu_set_t *used_cpus)
{
  int i;

  printf("Need %d cpus\n", nr_of_cpus(used_cpus));
  for (i = 0 ; i < CPU_SETSIZE ; i++) {
    int j, reported;

    for (reported = 0, j = 0 ; j < numInstances ; j++) {
      if (instance[j]->affinity == i) {
	reported++;
	if (reported == 1) {
	  printf("--affinity%d=%s/%d", 
		 i, instance[j]->actorClass->name, instance[j]->index);
	} else {
	  printf(",%s/%d", 
		 instance[j]->actorClass->name, instance[j]->index);
	}
      }
    }
    if (reported) {
      printf("\n");
    }
  }
}

static void *cache_aligned_calloc(size_t size)
{
  void *result; 
  
  if (posix_memalign(&result, CACHE_LINE_SIZE, size) != 0) {
    runtimeError(NULL, "Failed to align %d bytes\n", size);
  }
  memset(result, 0, size);
  return result;
}

static int cache_bytes(int n)
{
  return ((n + CACHE_LINE_SIZE - 1) / CACHE_LINE_SIZE) * CACHE_LINE_SIZE;
}

static cpu_runtime_data_t *allocate_network(
  ActorInstance_1_t **instance, 
  int numInstances,
  cpu_set_t *used_cpus,
  int fifo_size)
{
  cpu_runtime_data_t *result;
  int num_outputs, num_inputs, buffer_bytes, index;
  int cpu, shared_bytes, local_bytes, actor_bytes, global_bytes;
  void *buffer_p, *global_p, *shared_p, *local_p;
  InputPort *input_p, **reader_p;
  OutputPort *output_p;
  int i, j, k;

  /* Set fifo capacity of inputs (when unspecified) and outputs (max) */
  for (i = 0 ; i < numInstances ; i++) {
    for (j = 0 ; j < instance[i]->actorClass->numInputPorts ; j++) {
      if (instance[i]->input[j].capacity == 0) {
	instance[i]->input[j].capacity = fifo_size / 
	  instance[i]->actorClass->inputPortDescriptions[j].tokenSize;
      }
      if (instance[i]->input[j].output->capacity < 
	  instance[i]->input[j].capacity) {
	instance[i]->input[j].output->capacity =
	  instance[i]->input[j].capacity;
      }
    }
  }
      
  /* now set capacity of inputs to that of their output */
  /* 
   * TODO: we might want a scheme, in which we keep a smaller capacity
   * on individual inputs. Then remove this loop, but the implementation
   * of the FIFO then has to separate the concepts of capacity and buffer size
   */
  for (i = 0 ; i < numInstances ; i++) {
    for (j = 0 ; j < instance[i]->actorClass->numInputPorts ; j++) {
      instance[i]->input[j].capacity = instance[i]->input[j].output->capacity;
    }
  }
  
  /* Count number of inputs and outputs and needed buffer space */
  num_outputs = 0;
  num_inputs = 0;
  buffer_bytes = 0;
  actor_bytes = 0;
  for (i = 0 ; i < numInstances ; i++) {
    actor_bytes += instance[i]->actorClass->sizeActorInstance;
    num_outputs += instance[i]->actorClass->numOutputPorts;
    num_inputs += instance[i]->actorClass->numInputPorts;
    for (j = 0 ; j < instance[i]->actorClass->numOutputPorts ; j++) {
      instance[i]->output[j].buffer_bytes = cache_bytes(
	instance[i]->output[j].capacity * 
	instance[i]->actorClass->outputPortDescriptions[j].tokenSize);
      buffer_bytes += instance[i]->output[j].buffer_bytes;
    }
  }
  /* Global data: (semi-)constant (may only be changed in such a way that
   *              all cpus get a coherent view)
   * Local data:  only used by a single cpu
   * Shared data: written by one cpu, read by many, used to control 
   *              buffer access
   * Buffer data: the actual buffers containing data, written by one thread,
   *              read by many.
   * Access to buffer/shared data has to use barriers properly.
   */
  global_bytes = cache_bytes(
    num_outputs * sizeof(OutputPort) /* actor.output  */ +
    num_inputs * sizeof(InputPort)   /* actor.input   */ +
    num_inputs * sizeof(InputPort*)  /* output.reader */);
  local_bytes = cache_bytes(
    (num_outputs + num_inputs) * sizeof(LocalContext) +
    numInstances * sizeof(AbstractActorInstance *) + 
    actor_bytes +
    nr_of_cpus(used_cpus) * sizeof(*result[0].has_affected));
  shared_bytes = 
    cache_bytes(sizeof(*result[0].sleep))+
    cache_bytes((num_outputs + num_inputs) * sizeof(SharedContext));
  memory_statistics.num_outputs=num_outputs;
  memory_statistics.num_inputs=num_inputs;
  memory_statistics.global_bytes=global_bytes;
  memory_statistics.local_bytes=local_bytes * nr_of_cpus(used_cpus);
  memory_statistics.shared_bytes=shared_bytes * nr_of_cpus(used_cpus);
  memory_statistics.buffer_bytes=buffer_bytes;
  result = malloc(sizeof(*result) * nr_of_cpus(used_cpus));
  buffer_p = cache_aligned_calloc(
    buffer_bytes +
    global_bytes +
    shared_bytes * nr_of_cpus(used_cpus) + 
    local_bytes * nr_of_cpus(used_cpus));
  global_p = buffer_p + buffer_bytes;
  shared_p = global_p + global_bytes;
  local_p = shared_p + shared_bytes * nr_of_cpus(used_cpus);

  output_p = global_p;
  global_p += num_outputs * sizeof(OutputPort);
  input_p = global_p;
  global_p += num_inputs * sizeof(InputPort);
  reader_p = global_p;
  global_p += num_inputs * sizeof(InputPort*);

  /* Assign ports and output buffers, and assign indices into local and
   * shared data structures. 
   * NOTE: the result will be sparse, since all cpus share index space. This
   *       will give a higher number of used cache-lines, but will simplify
   *       actor migration (if this ever will be implemented).
   */ 
  index = 0;
  for (i = 0 ; i < numInstances ; i++) {
    if (instance[i]->actorClass->numOutputPorts) {
      instance[i]->output_list = output_p;
    }
    if (instance[i]->actorClass->numInputPorts) {
      instance[i]->input_list = input_p;
    }
    for (j = 0 ; j < instance[i]->actorClass->numOutputPorts ; j++) {
      OutputPort *output = output_p++;
      
      instance[i]->output[j].output = output;
      output->index = index++;
      /*
       * buffer points to end of buffer to avoid compare with capacity on
       * each erad/write (compare with 0 assumed cheap) 
       */
      buffer_p += instance[i]->output[j].buffer_bytes;
      output->buffer = buffer_p;
      output->capacity = instance[i]->output[j].capacity;
      output->readers = 0;
      output->reader = reader_p;
      reader_p += instance[i]->output[j].numberOfReaders;
    }
    for (j = 0 ; j < instance[i]->actorClass->numInputPorts ; j++) {
      InputPort *input = input_p++;

      instance[i]->input[j].input = input;
      input->index = index++;
      input->capacity = instance[i]->input[j].capacity;
    }
  }
  /* Connect the newly assigned ports */
  for (i = 0 ; i < numInstances ; i++) {
    for (j = 0 ; j < instance[i]->actorClass->numInputPorts ; j++) {
      InputPort *input = instance[i]->input[j].input;
      OutputPort *output = instance[i]->input[j].output->output;

      output->reader[output->readers] = input;
      output->readers++;
      input->writer = output;
      input->buffer = output->buffer;
    }
  }

  /* Setup CPU local data */
  for (cpu = -1, i = 0 ; i < CPU_SETSIZE ; i++) {
    if (CPU_ISSET(i, used_cpus)) {
      void *cpu_shared_p, *cpu_local_p, *cpu_actor_data;

      cpu++;
      /* Get cpu data */
      cpu_shared_p = shared_p;
      shared_p += shared_bytes;
      cpu_local_p = local_p;
      local_p += local_bytes;
	
      result[cpu].cpu = result;
      result[cpu].cpu_count = nr_of_cpus(used_cpus);
      result[cpu].cpu_index = cpu;
      result[cpu].physical_id = i;
      result[cpu].sem = malloc(sizeof(*result[cpu].sem));
      sem_init(result[cpu].sem, 0, 0); 

      // Data accessed from multiple cpus
      result[cpu].sleep = cpu_shared_p;
      cpu_shared_p += cache_bytes(sizeof(*result[cpu].sleep));
      result[cpu].shared = cpu_shared_p;

      // Data accessed from this cpu only
      result[cpu].local = cpu_local_p;
      cpu_local_p += (num_outputs + num_inputs) * sizeof(LocalContext);
      result[cpu].actors = 0;
      result[cpu].actor = cpu_local_p;
      cpu_local_p += numInstances * sizeof(AbstractActorInstance *);
      cpu_actor_data = cpu_local_p;
      cpu_local_p += actor_bytes;
      result[cpu].actor_data = cpu_actor_data;
      result[cpu].has_affected = cpu_local_p;
      cpu_local_p += (nr_of_cpus(used_cpus) * sizeof(*result[0].has_affected));
      result[cpu].traceFile=0;

      for (j = 0 ; j < numInstances ; j++) {
	if (instance[j]->affinity == result[cpu].physical_id) {
	  AbstractActorInstance *actor;
	  char buf[1024];

	  actor = cpu_actor_data;
	  result[cpu].actor[result[cpu].actors] = cpu_actor_data;
	  result[cpu].actors++;
	  cpu_actor_data += instance[j]->actorClass->sizeActorInstance;

	  actor->actor = instance[j]->actorClass;
	  sprintf(buf, "%s/%d", 
		  instance[j]->actorClass->name,
		  instance[j]->index);
	  actor->name = strdup(buf);
	  actor->cpu_index = cpu;
	  actor->outputs = instance[j]->actorClass->numOutputPorts;
	  actor->output = instance[j]->output_list;
	  actor->inputs = instance[j]->actorClass->numInputPorts;
	  actor->input = instance[j]->input_list;
	  actor->fired=0;
	  actor->terminated=0;
	  actor->nloops=0;
	  actor->total=0;
	  actor->firstActionIndex=0;
	  actor->traceFile=0;

	  actor->cpu=(int*)&result[cpu];
	  for (k = 0 ; k < actor->outputs ; k++) {
	    OutputPort *output = &actor->output[k];

	    output->cpu = cpu;
	    output->actor = actor;
	    output->shared = &result[cpu].shared[output->index];
	    output->local = &result[cpu].local[output->index];
	    output->local->pos = -(output->capacity);
	  }
	  for (k = 0 ; k < actor->inputs ; k++) {
	    InputPort *input = &actor->input[k];

	    input->cpu = cpu;
	    input->actor = actor;
	    input->shared = &result[cpu].shared[input->index];
	    input->local = &result[cpu].local[input->index];
	    input->local->pos = -(input->capacity);
	  }
	  if (actor->actor->set_param) {
	    struct Parameter_1 *p;

	    for (p = instance[j]->parameter ; p ; p = p->next) {
//	      printf("Call set_param[%d, %p, %s %s]...\n", j, actor, p->key, p->value);
	      actor->actor->set_param(actor, p->key, p->value);
	    }
	  }
	  if (actor->actor->constructor) {
//	    printf("Call constructor[%d, %p]...\n", j, actor);
	    actor->actor->constructor(actor);
	  }
	}
      }
    }
  }

  //get the number of active actors
  for (i = 0 ; i < numInstances ; i++) {
    if(instance[i]->actorClass->actorExecMode==1){
      numActiveActors++;
	}
  }
    
  return result;
}

static void run_destructors(cpu_runtime_data_t *runtime)
{
  int i, j;

  for (i = 0 ; i < runtime[0].cpu_count ; i++) {
    cpu_runtime_data_t *cpu = &runtime[i];
    if(cpu->traceFile)
      xmlCloseTrace(cpu->traceFile);

    for (j = 0 ; j < runtime[i].actors ; j++) {
      AbstractActorInstance *actor = runtime[i].actor[j];

      if (actor->actor->destructor) {
	actor->actor->destructor(actor);
      }
    }
  }
  
  
}

static void deallocate_network(cpu_runtime_data_t *runtime)
{
  int i, j;

  for (i = 0 ; i < runtime[0].cpu_count ; i++) {
    for (j = 0 ; j < runtime[i].actors ; j++) {
    }
  }
  
  
}

#ifndef __ERIKA__
static void *run_with_affinity(void *arg) 
{
  cpu_runtime_data_t *cpu = arg;
  cpu_set_t affinity;
  
  CPU_ZERO(&affinity);
  CPU_SET(cpu->physical_id, &affinity);
  sched_setaffinity(0, sizeof(cpu_set_t), &affinity);

  return cpu->main(cpu, arg_loopmax);
}

static void run_threads(cpu_runtime_data_t *runtime,
			void *(execute)(cpu_runtime_data_t *, int))
{
  int i;

  for (i = 0 ; i < runtime->cpu_count ; i++) {
    runtime[i].main = execute;
    pthread_create(&runtime[i].thread,
		   NULL,
		   run_with_affinity,
		   &runtime[i]);
  }

  if(cb_add_threads)
	cb_add_threads(runtime->cpu_count+1);

  for (i = 0 ; i < runtime->cpu_count ; i++) {
    pthread_join(runtime[i].thread, NULL);
  }
}
#endif

static void show_result(cpu_runtime_data_t *cpu, 
                        int show_statistics, 
			int show_timing)
{
  int i;

  if (show_statistics || show_timing) {

    printf("### Statistics ###\n");
    
    if (show_statistics) {
      printf("Memory usage:\n");
      printf("Global memory: %12u bytes\n", memory_statistics.global_bytes);
      printf("Local memory:  %12u\n", memory_statistics.local_bytes);
      printf("Shared memory: %12u\n", memory_statistics.shared_bytes);
      printf("Buffers:       %12u\n", memory_statistics.buffer_bytes);
      printf("  #outputs:    %12u\n", memory_statistics.num_outputs);
      printf("  #inputs:     %12u\n", memory_statistics.num_inputs);
    }

    for (i = 0 ; i < cpu->cpu_count ; i++) {
      int j;

      printf("\nCPU%d:\n", i);
      if (show_timing) {
	printf("prefire:       %12Lu cycles\n", cpu[i].statistics.prefire);
	printf("read_barrier:  %12Lu\n", cpu[i].statistics.read_barrier);
	printf("fire:          %12Lu\n", cpu[i].statistics.fire);
	printf("write_barrier: %12Lu\n", cpu[i].statistics.write_barrier);
	printf("postfire:      %12Lu\n", cpu[i].statistics.postfire);
	printf("sync_unblocked:%12Lu\n", cpu[i].statistics.sync_unblocked);
	printf("sync_blocked:  %12Lu\n", cpu[i].statistics.sync_blocked);
	printf("sync_sleep:    %12Lu\n", cpu[i].statistics.sync_sleep);
	printf("total:         %12Lu\n", cpu[i].statistics.total);
      }
      // subtract one from nsleep not to count the last time (termination)
      printf("nsleep:        %12Lu times\n", cpu[i].statistics.nsleep-1);
      printf("nloops:        %12Lu\n", cpu[i].statistics.nloops);

      if (show_timing)
	printf("%-32s  nloops timing (cycles)\n", "actor");
      else
	printf("%-32s  nloops\n", "actor");
      for (j = 0 ; j < cpu[i].actors ; j++) { 
	if (show_timing)
	  printf("%-32s %7Ld %12Lu\n",
	         cpu[i].actor[j]->name,
		 cpu[i].actor[j]->nloops,
		 cpu[i].actor[j]->total);
	else
	  printf("%-32s %7Ld\n",
	         cpu[i].actor[j]->name,
		 cpu[i].actor[j]->nloops);

      }
    }
  }
}

static void generate_config(FILE *f, 
                            cpu_runtime_data_t *cpu,
			    int with_complexity,
			    int with_bandwidth) {
  int i,j,k;

  fprintf(f,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
  fprintf(f,"<Configuration>\n");
  fprintf(f,"  <Partitioning>\n");
  for (i = 0 ; i < cpu->cpu_count ; i++) {
    fprintf(f,"    <Partition id=\"%u\">\n", i);
    for (j = 0 ; j < cpu[i].actors ; j++) {
      AbstractActorInstance *actor=cpu[i].actor[j];
      if (with_complexity)
	fprintf(f,"      <Instance actor-id=\"%s\" complexity=\"%Lu\"/>\n",
		actor->name, actor->total);
      else
	fprintf(f,"      <Instance actor-id=\"%s\"/>\n",actor->name);
    }
    fprintf(f,"    </Partition>\n");
  }

  for (i = 0 ; i < cpu->cpu_count ; i++) {
    for (j = 0 ; j < cpu[i].actors ; j++) {
      AbstractActorInstance *producer=cpu[i].actor[j];

      for (k=0; k<producer->outputs; ++k) {
	OutputPort *output=producer->output + k;
	const char *outputPortName=
	  producer->actor->outputPortDescriptions[k].name;
	int r;

	for (r=0; r<output->readers; ++r) {
	  InputPort *input=output->reader[r];
	  AbstractActorInstance *consumer=input->actor;
	  const char *inputPortName=0;
	  int s;

	  for (s=0; s<consumer->inputs; ++s)
	    if (consumer->input + s == input) {
	      inputPortName=consumer->actor->inputPortDescriptions[s].name;
	      break;
	    }

	  fprintf(f,"    <Connection src=\"%s\" src-port=\"%s\" "
		  "dst=\"%s\" dst-port=\"%s\" size=\"%u\"",
		  producer->name, outputPortName,
		  consumer->name, inputPortName,
		  input->capacity);

	  if (with_bandwidth) {
	    fprintf(f," bandwidth=\"%u\"/>\n",
		    atomic_get(&input->shared->count));
	  }
	  else {
	    fprintf(f,"/>\n");
	  }
	}
      }
    }
  }
  fprintf(f,"  </Partitioning>\n");
#ifndef __ERIKA__
//#ifdef RM  
  fprintf(f,"  <RMInterface name=\"%s\">\n",rmInterface.name);
  fprintf(f,"    <Category value=\"%s\"/>\n",get_category_string(rmInterface.categoryValue));
  fprintf(f,"    <InitialService index=\"%d\"/>\n",rmInterface.currentServiceIndex);
  fprintf(f,"    <GroupID base=\"%d\"/>\n",rmInterface.groupIDBase);
  fprintf(f,"    <ServiceLevels>\n");
  for(i=0; i<rmInterface.numServiceLevels; i++)
  {
  ServiceLevel   *serviceLevel=&rmInterface.serviceLevels[i];
  fprintf(f,"      <ServiceLevel index=\"%d\">\n",serviceLevel->index);
  fprintf(f,"        <QualityOfService quality=\"%d\"/>\n",serviceLevel->quality);
  fprintf(f,"        <Granularity value=\"%d\"/>\n",serviceLevel->granularityValue);
  fprintf(f,"        <TotalBW value=\"%d\" mode=\"%s\"/>\n",serviceLevel->totalBW,get_mode_string(serviceLevel->mode));
  fprintf(f,"        <VIDEO resolution=\"%s\" fps=\"%d\"/>\n",serviceLevel->resolution,serviceLevel->fps);		 
  fprintf(f,"        <BWDistributions>\n");
  for(j=0; j<serviceLevel->numBMDistributions; j++)
  {
  BWDistribution *bwDistribution=&serviceLevel->bwDistributions[j];
  fprintf(f,"          <BWDistribution id=\"%d\" value=\"%d\"/>\n",bwDistribution->id,bwDistribution->value);
  }
  fprintf(f,"        </BWDistributions>\n");
  fprintf(f,"      </ServiceLevel>\n");
  }
  fprintf(f,"    </ServiceLevels>\n");
  fprintf(f,"  </RMInterface>\n");
//#endif
#endif
  fprintf(f,"  <Scheduling type=\"RoundRobin\"/>\n");
  fprintf(f,"</Configuration>\n");
}

static void show_usage(char *name) {
  printf("Usage: %s [OPTION...]\n", name);
  printf("Executes network %s using the ACTORS run-time system\n", name);
  printf("\nOptions:\n"
         "--cfile=FILE            Sets affinity and/or FIFO capacities as\n"
         "                        specified in the configuration file\n"
         "--generate=FILE         Generate configuration file from current\n"
         "                        execution (also see --with_complexity and\n"
         "                        --width_bandwidth)\n"
         "--help                  Display this help list\n"
         "--loopmax=N             Restrict the maximum number of action\n"
         "                        firings per actor\n"
         "--statistics            Display run-time statistics\n"
         "--timing                Collect and display timing statistics\n"
         "--trace                 Generate execution trace:\n"
         "                        Action trace generated if actors are\n" 
         "                        compiled with CFLAGS=-DTRACE\n"
         "--with-complexity       Output per-actor complexity (cycles) in\n"
         "                        configuration file (see --generate)\n"
         "--with-bandwidth        Output per-connection bandwidth (#tokens)\n"
         "                        in configuration file (see --generate).\n"
         "                        Note: wraps around at 4G tokens\n"
         "--termination-report    Describe network state at termination\n");
}

int executeNetwork(int argc, 
		   char *argv[],
		   AbstractActorInstance **instance, 
		   int numInstances)
{
  int result = 0;
  cpu_set_t used_cpus;
  ActorInstance_1_t **instance_1;
  instance_1 = (ActorInstance_1_t**)instance;
  int i;
  int flags = 0;
  cpu_runtime_data_t *runtime_data;
  int arg_print_info = 0;
  int arg_fifo_size = DEFAULT_FIFO_LENGTH;
  char *configFilename=0;
  int show_statistics=0;
  int affinity_is_set=0;
  int show_timing=0;
  int generate_trace=0;
  const char *generateFileName=0;
  FILE *generateFile=0;
  int with_complexity=0;
  int with_bandwidth=0;
  int terminationReport=0;


  for (i = 1 ; i < argc ; i++) {
    if (strcmp(argv[i], "--timing") == 0) {
      show_timing=1;
      flags |= FLAG_TIMING;
    } else if (strcmp(argv[i], "--statistics") == 0) {
      show_statistics=1;
    } else if (strncmp(argv[i], "--loopmax=", 10) == 0) {
      arg_loopmax = atoi(&argv[i][10]);
    } else if (strncmp(argv[i], "--cfile=", 8) == 0) {
      configFilename = &argv[i][8];
    } else if (strncmp(argv[i], "--generate=", 11) == 0) {
      generateFileName = &argv[i][11];    
    } else if (strcmp(argv[i], "--with-complexity") == 0) {
      flags |= FLAG_TIMING;
      with_complexity=1;
    } else if (strcmp(argv[i], "--with-bandwidth") == 0) {
      with_bandwidth=1;
    } else if (strcmp(argv[i], "--trace") == 0) {
      generate_trace=1;
    } else if (strcmp(argv[i], "--termination-report") == 0) {
      terminationReport=1;
    } else if (strcmp(argv[i], "--help") == 0) {
      show_usage(argv[0]);
      exit(0);
    } else {
      printf("Invalid command-line argument '%s'\n", argv[i]);
      exit(1);
    }
  }

  if (!generateFileName && (with_bandwidth || with_complexity)) {
    printf("--with_bandwidth and --with_complexity requires --generate\n");
    exit(1);
  }

  result = index_nodes(instance_1, numInstances);
  if (result == 0) {
    // Assign command line affinity
    for (i = 1 ; i < argc ; i++) {
      if (strncmp(argv[i], "--affinity", 10) == 0) {
        set_affinity(instance_1, numInstances, &argv[i][10]);
	affinity_is_set=1;
      }
    }
  }

#ifndef __ERIKA__
  if (result == 0) {
    // Assign affinity and other params from config file
    if (configFilename) {
      instance_1=set_config(instance_1, numInstances, configFilename);
      affinity_is_set=1;
    }
  }
#endif

  if (result==0 && generateFileName) {
    generateFile=fopen(generateFileName,"w");
    if (!generateFile) {
      printf("Cannot create file \"%s\": %s\n", 
	     generateFileName, strerror(errno));
      exit(1);
    }
  }

  if (result == 0) {
    result = check_network(instance_1, numInstances, &used_cpus, &flags, 
                           affinity_is_set);
  }
  if (arg_print_info) {
    info_network(instance_1, numInstances, &used_cpus);
	printf("\n### XML Config ###\n");  
	printout_config();
	printf("### XML Config End ###\n\n");
  }
  if (result == 0) {
    runtime_data = allocate_network(instance_1, numInstances, &used_cpus,
				    arg_fifo_size);
  }
  if (result == 0) {
#ifndef __ERIKA__
    if (generate_trace)
      enable_tracing(runtime_data, numInstances, argv[0]);
#endif

    if(cb_register_thread)
	  cb_register_thread(0);

    if (nr_of_cpus(&used_cpus) == 1) {
      flags |= FLAG_SINGLE_CPU;
	  if(cb_add_threads)
		cb_add_threads(0);  
    }
    switch (flags) {
#ifndef __ERIKA__
      case 0: {
	run_threads(runtime_data, multi_cpu_execute_network);
      } break;
#endif
      case FLAG_SINGLE_CPU: {
	single_cpu_execute_network(runtime_data, arg_loopmax);
      } break;
#ifndef __ERIKA__
      case FLAG_TIMING: {
	run_threads(runtime_data, multi_cpu_timed_execute_network);
      } break;
#endif
      case FLAG_TIMING | FLAG_SINGLE_CPU: {
	single_cpu_timed_execute_network(runtime_data, arg_loopmax);
      } break;
    }
  }
  if (result == 0) {
#ifndef __ERIKA__
    if (buffer_report(runtime_data) || terminationReport)
      deadlock_report(runtime_data,numInstances,terminationReport);
#endif
    run_destructors(runtime_data);
    show_result(runtime_data, show_statistics, show_timing);
  }
  
  if (result==0 && generateFile) {
    generate_config(generateFile, 
		    runtime_data, 
		    with_complexity, 
		    with_bandwidth);
  }

  if (result == 0) {
    deallocate_network(runtime_data);
  }

  exit(result);
}

/*

x --affinity0=a1/0,a1/1 --affinity1=a2/0

*/
