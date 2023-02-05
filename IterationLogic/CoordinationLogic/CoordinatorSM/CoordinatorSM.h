#ifndef COORDINATOR_SM_H
#define COORDINATOR_SM_H

#include "../Coordinator.h"

unsigned int CoordinatorSM_init (CoordinatorSM_struct &coordinatorInstance);
unsigned int CoordinatorSM_run  (CoordinatorSM_struct &coordinatorInstance);
unsigned int CoordinatorSM_reset(CoordinatorSM_struct &coordinatorInstance);

#endif