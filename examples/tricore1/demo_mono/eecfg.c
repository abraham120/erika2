/* Jan Kleinsorge, 2010 */

#include "ee.h"

DeclareTask(Task0);
DeclareTask(Task1);


const EE_FADDR EE_hal_thread_body[EE_MAX_TASK] = {
    (EE_FADDR)EE_oo_thread_stub,
    (EE_FADDR)EE_oo_thread_stub
};



EE_UINT32 EE_terminate_data[EE_MAX_TASK];


const EE_FADDR EE_terminate_real_th_body[EE_MAX_TASK] = {
    (EE_FADDR)FuncTask0,
    (EE_FADDR)FuncTask1
};


const EE_TYPEPRIO EE_th_ready_prio[EE_MAX_TASK] = {
    0x2,
    0x1,
};


const EE_TYPEPRIO EE_th_dispatch_prio[EE_MAX_TASK] = {
    0x1,
    0x1,
};


EE_TYPESTATUS EE_th_status[EE_MAX_TASK] = {
    SUSPENDED,
    SUSPENDED        
};


EE_TID EE_th_next[EE_MAX_TASK] = {
    EE_NIL,
    EE_NIL
};


EE_TYPENACT EE_th_rnact[EE_MAX_TASK] = { 
    1, 
    1
};


/* Unused */
#ifndef __OO_NO_CHAINTASK__
EE_TID EE_th_terminate_nextask[EE_MAX_TASK] = {
    EE_NIL,
    EE_NIL
};
#endif


EE_UREG EE_th_resource_last[EE_MAX_TASK] = { 
    (EE_UREG)-1, 
    (EE_UREG)-1
};


EE_TID EE_stkfirst = EE_NIL;


EE_TID EE_rq_first  = EE_NIL;


EE_TYPEPRIO EE_sys_ceiling = 0x0000;


EE_TYPEAPPMODE EE_ApplicationMode;


static const EE_TID EE_oo_autostart_task_mode_OSDEFAULTAPPMODE[1] = { Task1 };


const struct EE_oo_autostart_task_type 
EE_oo_autostart_task_data[EE_MAX_APPMODE] = {
    { 1, EE_oo_autostart_task_mode_OSDEFAULTAPPMODE}
};


