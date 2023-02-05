#include "Coordinator.h"

#include "../IteratorLogic/Iterator.h"

#include <stdio.h>
#include <stdlib.h>

/* Public declarations */

unsigned int Coordinator_init_sm        (CoordinatorSM_struct &coordinatorInstance)
{
    /* create comm ports */
    ///TODO: create port interfaces

    // /* allocate iterator array (possible out of scope array)*/
    IteratorSM_struct iterators[coordinatorInstance.workerNumber];
    coordinatorInstance.iteratorInstanceArray = iterators;

    /* allocate iterator pointer */
    // coordinatorInstance.iteratorInstanceArray = (IteratorSM_struct*) malloc(sizeof(IteratorSM_struct) * coordinatorInstance.workerNumber);

    for(unsigned int i = 0u; i < coordinatorInstance.workerNumber; ++i)
    {
        coordinatorInstance.iteratorInstanceArray[i].bufferSize = coordinatorInstance.workerBufferSize;
        coordinatorInstance.iteratorInstanceArray[i].smID = i;


    }

    printf("Coordinator_SM initialized\n");
    

    return 0;
}
unsigned int Coordinator_checkForEvents (CoordinatorSM_struct &coordinatorInstance);
unsigned int Coordinator_pause          (CoordinatorSM_struct &coordinatorInstance);
unsigned int Coordinator_resume         (CoordinatorSM_struct &coordinatorInstance);
unsigned int Coordinator_shutdown       (CoordinatorSM_struct &coordinatorInstance);

unsigned int Coordinator_initWorkers    (CoordinatorSM_struct &coordinatorInstance)
{
    for(unsigned int i = 0u; i < coordinatorInstance.workerNumber; ++i)
    {
        coordinatorInstance.iteratorInstanceArray[i].stateMachineHandle = std::thread(Iterator_init, std::ref(coordinatorInstance.iteratorInstanceArray[i]));
        coordinatorInstance.iteratorInstanceArray[i].stateMachineHandle.detach();
    }
    printf("Coordinator_SM workers initialized\n");
    return 0;
}
unsigned int Coordinator_startWorkers   (CoordinatorSM_struct &coordinatorInstance)
{
    for(unsigned int i = 0u; i < coordinatorInstance.workerNumber; ++i)
    {
        
    }
}
unsigned int Coordinator_pauseWorkers   (CoordinatorSM_struct &coordinatorInstance);
unsigned int Coordinator_stopWorkers    (CoordinatorSM_struct &coordinatorInstance);
unsigned int Coordinator_resetWorkers   (CoordinatorSM_struct &coordinatorInstance);