#ifndef SECP251K1_SANDBOX_ITERATIONMANAGER_STATEMACHINES_H
#define SECP251K1_SANDBOX_ITERATIONMANAGER_STATEMACHINES_H

#include "IteratorSM/IteratorSM.h"
#include "CoordinatorSM/CoordinatorSM.h"

std::thread *startIteratorSM(IteratorSM_struct *messageStruct);
unsigned int stopIteratorSM(IteratorSM_struct *messageStruct);

std::thread *startCoordinatorSM(CoordinatorSM_struct *messageStruct);
unsigned int stopCoordinatorSM(CoordinatorSM_struct *messageStruct);

#endif