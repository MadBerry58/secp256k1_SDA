#include "IterationManager.h"
#include "../Ports.cpp"

IterationManagerData iterationManagerDataStructure;
#define ITERATION_PORT_BUFFER_SIZE 5u
unsigned int init_MemoryManager(std::string initData)
{
    initPort(ITERATION_PORT_BUFFER_SIZE, iterationManagerDataStructure.iterationManagerRxPort);
    return 0;
}

int iterationManager_init(IterationManagerData data)
{
    CoordinatorSMStruct coordinatorData;
    //bind memoryManager
    //bind fileManager
    for(int i = 0; i < data.iteratorNumber; i++)
    {
        //create an iteratorSM
    }
    //bind iteratorSM to coordinatorSM
    return 0;
}

unsigned int iterationManager_start()
{
    //bind notification ports
    //send start message to coordinatorSM
    //confirm iteration start
    return 0;
}

unsigned int iterationManager_getInfo()
{
    //send message to coordinator
    return 0;
}

int testWorkoad()
{
    //send message to coordinator
    return 0;
}
