#include "IterationManager.h"
#include "../Ports.h"

CoordinatorSM_struct coordinatorData[MAX_COORDINATOR_NO];
IteratorSM_struct    iteratorData[MAX_ITERATOR_NO];
unsigned int init_IterationManager(IterationManagerData data)
{
    initPort(&(data.iterationManagerRxPort), ITERATION_PORT_BUFFER_SIZE);
    //bind memoryManager
    //bind fileManager
    // for(int i = 0; i < data.iteratorNumber; i++)
    // {
    //     //create an iteratorSM
    // }
    //bind iteratorSM to coordinatorSM
    data.managerInitialized = true;
    return ITERATION_MANAGER_E_OK;
}

unsigned int iterationManager_start()
{
    //bind notification ports
    //send start message to coordinatorSM
    //confirm iteration start
    return ITERATION_MANAGER_E_OK;
}

unsigned int iterationManager_getInfo()
{
    //send message to coordinator
    return ITERATION_MANAGER_E_OK;
}

unsigned int testWorkoad()
{
    //send message to coordinator
    return ITERATION_MANAGER_E_OK;
}