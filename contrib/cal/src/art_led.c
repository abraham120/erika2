/*
 * Actor led (ActorClass_art_led)
 * Generated on Fri Jan 28 11:05:26 CET 2011 from led_0.xlim
 * by xlim2c version 0.6 (June 3, 2009)
 */

#include "actors-rts.h"
#include <ee.h>

#define IN0_inp ART_INPUT(0)

typedef struct {
  AbstractActorInstance base;
} ActorInstance_led_0;


ART_ACTION_CONTEXT(1,0)

ART_ACTION(led_0_a0_actionAtLine_5,ActorInstance_led_0);
ART_ACTION_SCHEDULER(led_0_action_scheduler);
static void led_0_constructor(AbstractActorInstance*);

static const PortDescription inputPortDescriptions[]={
  {"inp", sizeof(int32_t)}
};


static const int portRate_1[] = {
  1
};

static const ActionDescription actionDescriptions[] = {
  {"actionAtLine_5", portRate_1, 0}
};

ActorClass ActorClass_art_led = INIT_ActorClass(
  "art_led",
  ActorInstance_led_0,
  led_0_constructor,
  0, /* no setParam */
  led_0_action_scheduler,
  0, /* no destructor */
  1, inputPortDescriptions,
  0, 0,
  1, actionDescriptions
);


ART_ACTION(led_0_a0_actionAtLine_5,ActorInstance_led_0) {
  int32_t t0;
  ART_ACTION_ENTER(led_0_a0_actionAtLine_5,0);
  t0=pinRead_int32_t(IN0_inp);
  EE_led_set_all(t0);
  ART_ACTION_EXIT(led_0_a0_actionAtLine_5,0);
}

static const int exitcode_block_inp_1[] = {
  EXITCODE_BLOCK(1), 0, 1
};

ART_ACTION_SCHEDULER(led_0_action_scheduler) {
  ActorInstance_led_0 *thisActor=(ActorInstance_led_0*) pBase;
  const int *exitCode=EXIT_CODE_YIELD;
  ART_ACTION_SCHEDULER_ENTER(1,0);
  ART_ACTION_SCHEDULER_LOOP {
    ART_ACTION_SCHEDULER_LOOP_TOP;
    int32_t t3;
    t3=pinAvailIn_int32_t(IN0_inp);
    if ((t3>=(1))) {
      ART_FIRE_ACTION(led_0_a0_actionAtLine_5);
    }
    else {
      exitCode=exitcode_block_inp_1; goto action_scheduler_exit;
    }
    ART_ACTION_SCHEDULER_LOOP_BOTTOM;
  }
  action_scheduler_exit:
  ART_ACTION_SCHEDULER_EXIT(1,0);
  return exitCode;
}

static void led_0_constructor(AbstractActorInstance *pBase) {
}
