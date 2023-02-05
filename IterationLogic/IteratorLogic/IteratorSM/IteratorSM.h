#ifndef SECP251K1_SANDBOX_ITERATIONMANAGER_ITERATOR_SM_H
#define SECP251K1_SANDBOX_ITERATIONMANAGER_ITERATOR_SM_H

#include "../Iterator.h"

unsigned int IteratorSM_init (IteratorSM_struct &coordinatorInstance);
unsigned int IteratorSM_run  (IteratorSM_struct &coordinatorInstance);
unsigned int IteratorSM_reset(IteratorSM_struct &coordinatorInstance);

#endif