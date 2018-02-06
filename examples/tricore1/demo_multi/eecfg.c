/* Jan Kleinsorge, 2010 */

#include "ee.h"

/* Sizes in WORDS!  */
#define STACK_1_SIZE 64
#define STACK_2_SIZE 64
#define STACK_3_SIZE 64

EE_STACK EE_tc1_stack_1[STACK_1_SIZE];
EE_STACK EE_tc1_stack_2[STACK_2_SIZE];
EE_STACK EE_tc1_stack_3[STACK_3_SIZE];

struct EE_TOS EE_tc1_system_tos[EE_MAX_TASK + 1] = {
    {NULL},
    {(EE_ADDR)&EE_tc1_stack_1[STACK_1_SIZE - 3]},
    {(EE_ADDR)&EE_tc1_stack_2[STACK_2_SIZE - 3]} 
};

struct EE_CTX EE_tc1_system_ctx[EE_MAX_TASK + 1] = {
    {0, NULL, 0 },              /* main */
    {0, NULL, 1 },              /* task0 */
    {0, NULL, 2 },              /* task1 */
};

struct EE_TOS EE_tc1_IRQ_tos = {
    (EE_ADDR)&EE_tc1_stack_3[STACK_3_SIZE - 3]
};


EE_UREG EE_tc1_active_tos = 0; /* main */

DeclareTask(Task0);
DeclareTask(Task1);

const EE_FADDR EE_hal_thread_body[EE_MAX_TASK] = {
    (EE_FADDR)FuncTask0, 
    (EE_FADDR)FuncTask1  
};

const EE_TYPEPRIO EE_th_ready_prio[EE_MAX_TASK] = {
    0x1,            
    0x2             
};

const EE_TYPEPRIO EE_th_dispatch_prio[EE_MAX_TASK] = {
    0x1,           
    0x2            
};

#if defined(__MULTI__) || defined(__WITH_STATUS__)
EE_TYPESTATUS EE_th_status[EE_MAX_TASK] = {
    EE_READY,
    EE_READY        
};
#endif

EE_TID EE_th_next[EE_MAX_TASK] = {
    EE_NIL,
    EE_NIL    
};

EE_TYPEPRIO EE_th_nact[EE_MAX_TASK];

EE_TID EE_stkfirst = EE_NIL;

EE_TID EE_rqfirst  = EE_NIL;

EE_TYPEPRIO EE_sys_ceiling= 0x0000;

const EE_TYPEPRIO EE_resource_ceiling[EE_MAX_RESOURCE]= {
    0x2              /* resource RES_SCHEDULER */
};

EE_TYPEPRIO EE_resource_oldceiling[EE_MAX_RESOURCE];


