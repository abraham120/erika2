/*
 * Actor switch (ActorClass_art_switch)
 * Generated on Fri Jan 28 11:05:23 CET 2011 from switch_0.xlim
 * by xlim2c version 0.6 (June 3, 2009)
 */

#include "actors-rts.h"
#include <ee.h>

#define OUT0_outp ART_OUTPUT(0)

typedef struct {
  AbstractActorInstance base;
} ActorInstance_switch_0;


ART_ACTION_CONTEXT(0,1)

ART_ACTION(switch_0_a0_actionAtLine_5,ActorInstance_switch_0);
ART_ACTION_SCHEDULER(switch_0_action_scheduler);
static void switch_0_constructor(AbstractActorInstance*);


static const PortDescription outputPortDescriptions[]={
  {"outp", sizeof(int32_t)}
};

static const int portRate_1[] = {
  1
};

static const ActionDescription actionDescriptions[] = {
  {"actionAtLine_5", 0, portRate_1}
};

ActorClass ActorClass_art_switch = INIT_ActorClass(
  "art_switch",
  ActorInstance_switch_0,
  switch_0_constructor,
  0, /* no setParam */
  switch_0_action_scheduler,
  0, /* no destructor */
  0, 0,
  1, outputPortDescriptions,
  1, actionDescriptions
);


ART_ACTION(switch_0_a0_actionAtLine_5,ActorInstance_switch_0) {
  unsigned swstate;
  swstate = EE_switch_read_all();
  ART_ACTION_ENTER(switch_0_a0_actionAtLine_5,0);
  pinWrite_int32_t(OUT0_outp, swstate);
  ART_ACTION_EXIT(switch_0_a0_actionAtLine_5,0);
}

static const int exitcode_block_outp_1[] = {
  EXITCODE_BLOCK(1), 0, 1
};

ART_ACTION_SCHEDULER(switch_0_action_scheduler) {
  ActorInstance_switch_0 *thisActor=(ActorInstance_switch_0*) pBase;
  const int *exitCode=EXIT_CODE_YIELD;
  ART_ACTION_SCHEDULER_ENTER(0,1);
  ART_ACTION_SCHEDULER_LOOP {
    ART_ACTION_SCHEDULER_LOOP_TOP;
    int32_t t5;
    t5=pinAvailOut_int32_t(OUT0_outp);
    if ((t5>=(1))) {
      ART_FIRE_ACTION(switch_0_a0_actionAtLine_5);
    }
    else {
      exitCode=exitcode_block_outp_1; goto action_scheduler_exit;
    }
    ART_ACTION_SCHEDULER_LOOP_BOTTOM;
  }
  action_scheduler_exit:
  ART_ACTION_SCHEDULER_EXIT(0,1);
  return exitCode;
}

static void switch_0_constructor(AbstractActorInstance *pBase) {
}
