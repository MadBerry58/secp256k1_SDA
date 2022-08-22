#ifndef SECP251K1_SANDBOX_ITERATIONMANAGER_COORDINATOR_SM_H
#define SECP251K1_SANDBOX_ITERATIONMANAGER_COORDINATOR_SM_H

#include "../StateMachines.h"
#include "../../../../Arithmetic/Algorithms/Algorithms.h"

unsigned int init_CoordinatorSM(CoordinatorSMStruct *data);
unsigned int CoordinatorSM(CoordinatorSMStruct *data);

#endif