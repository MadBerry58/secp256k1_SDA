#ifndef SECP251K1_SANDBOX_ITERATIONMANAGER_STATEMACHINES_H
#define SECP251K1_SANDBOX_ITERATIONMANAGER_STATEMACHINES_H

#include "IteratorSM/IteratorSM.h"
#include "CoordinatorSM/CoordinatorSM.h"

std::thread *startIteratorSM(IteratorSMStruct *messageStruct);
unsigned int stopIteratorSM(IteratorSMStruct *messageStruct);

std::thread *startCoordinatorSM(CoordinatorSMStruct *messageStruct);
unsigned int stopCoordinatorSM(CoordinatorSMStruct *messageStruct);

#endif