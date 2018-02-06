/*
 * Author: Antonio Marcello Catinella
 *
 * Files used to redefine not usable types and methods into Erika Enterprise
 */


#ifndef _CAL_REDEFINITIONS_H
#define _CAL_REDEFINITIONS_H

#include <system_conf.h>
#include <stdlib.h>


#define CPU_SETSIZE 1

#if CPU_DCACHE_ENABLED == 1
#define CACHE_LINE_SIZE CPU_DCACHE_BYTES_PER_LINE
#else
#define CACHE_LINE_SIZE 4
#endif

#define mb()   // asm volatile("mfence":::"memory")
#define rmb()  // asm volatile("lfence":::"memory")
#define wmb()  // asm volatile("sfence" ::: "memory")

typedef int pthread_t;
typedef int sem_t;
typedef int pthread_mutex_t;
typedef int cpu_set_t;

int posix_memalign(void **memptr, size_t alignment, size_t size)
{
  void *dummy = malloc(size);
  if (dummy) {
    *memptr = dummy;
    return 0;
  } else {
    return -1;
  }
}


int sem_post(sem_t *sem)
{
  return 0;
}

int sem_init(sem_t *sem, int pshared, unsigned int value)
{
  return 0;
}

int sem_wait(sem_t *sem)
{
  return 0;
}

int sem_trywait(sem_t *sem)
{
  return 0;
}

int pthread_mutex_lock (pthread_mutex_t *mutex)
{
  return 0;
}

int pthread_mutex_unlock (pthread_mutex_t *mutex)
{
  return 0;
}

void CPU_ZERO(cpu_set_t *set) {}

void CPU_SET(int cpu, cpu_set_t *set) {}

int CPU_ISSET(int cpu, cpu_set_t *set)
{
  return 1;
}

void xmlCloseTrace(FILE *f) {}

void xmlTraceWakeup(FILE *f, int whom) {}

void xmlTraceStatus(FILE *f, int status) {}

void xmlTraceAction(FILE *f, int actionIndex) {}

#endif
