#include <ee.h>
#include "ee_cal.h"

void EE_cal_init() {}

void EE_cal_start(EE_TID task_id) {
  ActivateTask(task_id);
}
