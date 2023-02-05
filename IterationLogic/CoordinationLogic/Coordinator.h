#ifndef COORDINATOR_H
#define COORDINATOR_H

#include "Coordinator_Types.h"

unsigned int Coordinator_init_sm        (CoordinatorSM_struct &coordinatorInstance);
unsigned int Coordinator_checkForEvents (CoordinatorSM_struct &coordinatorInstance);
unsigned int Coordinator_pause          (CoordinatorSM_struct &coordinatorInstance);
unsigned int Coordinator_resume         (CoordinatorSM_struct &coordinatorInstance);
unsigned int Coordinator_shutdown       (CoordinatorSM_struct &coordinatorInstance);
unsigned int Coordinator_reset_sm       (CoordinatorSM_struct &coordinatorInstance);

unsigned int Coordinator_initWorkers    (CoordinatorSM_struct &coordinatorInstance);
unsigned int Coordinator_startWorkers   (CoordinatorSM_struct &coordinatorInstance);
unsigned int Coordinator_pauseWorkers   (CoordinatorSM_struct &coordinatorInstance);
unsigned int Coordinator_stopWorkers    (CoordinatorSM_struct &coordinatorInstance);
unsigned int Coordinator_resetWorkers   (CoordinatorSM_struct &coordinatorInstance);

#endif