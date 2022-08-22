#include "StateMachines.h"

/**
 * @brief Start coordinator state machine
 * @details Coordinator state machine handles the iterator threads by modeling the data buffers and initialization data,
 * in order to allow parallel work distribution
 * 
 * @return unsigned int 
 */
std::thread *startIteratorSM(IteratorSMStruct *messageStruct)
{
    init_IteratorSM(messageStruct);
    std::thread iteratorSMThread(IteratorSM, messageStruct);
    iteratorSMThread.detach(); /* prevent the destructor from joining the thread */
    messageStruct->stateMachineHandle = &iteratorSMThread;
    return messageStruct->stateMachineHandle;
}
unsigned int stopIteratorSM(IteratorSMStruct *messageStruct)
{
    messageStruct->stateMachineHandle->join();
    std::cout << "\n\nIteratorSM thread stopped\n" << std::endl;
    return 0;
}

std::thread *startCoordinatorSM(CoordinatorSMStruct *messageStruct)
{
    init_CoordinatorSM(messageStruct);
    std::thread coordinatorSMThread(CoordinatorSM, messageStruct);
    coordinatorSMThread.detach(); /* prevent the destructor from joining the thread */
    messageStruct->stateMachineHandle = &coordinatorSMThread;
    return messageStruct->stateMachineHandle;
}
unsigned int stopCoordinatorSM(CoordinatorSMStruct *messageStruct)
{
    messageStruct->stateMachineHandle->join();
    std::cout << "\n\nCoordinatorSM thread stopped\n" << std::endl;
    return 0;
}