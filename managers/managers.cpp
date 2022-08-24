#include "../Arithmetic/ModularArithmetic/Mod.h"
#include "../Arithmetic/PointArithmetic/Point.h"
#include "Ports.h"
#include "managers.h"

/* Manager initialization:
 * Each manager holds specific functionality, data structures and state machine control
 * Static components (do not use dedicated threads) are initialized by allocating all the required data
 * Runtime components (thread state machines) are initialized by allocating the initial data structures,
 * testing the communication ports to the other components and bringing the state machine into a ready state
 * 
 * After all the components are initialized, the iteration can be started.
 */


#define MANAGER_REPORT_PORT_BUFFER_SIZE 5u
Port managerReportPort;

IterationManagerData    iterationManagerStruct;
NetworkManagerData      networkManagerStruct;
MemoryManagerData       memoryManagerStruct;
FileManagerData         fileManagerStruct;
UISMStruct              uiManagerStruct;


unsigned int init_Managers(InitDataStruct initData)
{
    gmp_printf("Initial Testing Checkpoint 2: managers.cpp\n");
    unsigned long errorNo = 0u;

    /* Initialize manager report port */

    if((errorNo = initPort(&managerReportPort, MANAGER_REPORT_PORT_BUFFER_SIZE)) != COMM_E_OK)
    {
        printf("Manager port initialization failed with error code %lu\n", errorNo);
    }
    /* Initialize arithmetic functionality */

    if ((errorNo = init_Mod()) != MOD_E_OK)
    {
        printf("Modular Arithmetic init failed with code %lu\n", errorNo);
    }
    else if ((errorNo = init_Point()) != POINT_E_OK)
    {
        printf("Point Arithmetic init failed with code %lu\n", errorNo);
    }

    /* Initialize manager functionality */

    else if ((errorNo = init_FileManager(fileManagerStruct)) != INTEGRITY_E_FILE_INIT_OK)
    {
        printf("File Manager init failed with code %lu\n", errorNo);
    }
    else if ((errorNo = init_NetworkManager(networkManagerStruct)) != NETWORK_MANAGER_E_OK)
    {
        printf("Network Manager init failed with code %lu\n", errorNo);
    }
    else if ((errorNo = init_MemoryManager(memoryManagerStruct)) != MEMORY_MANAGER_E_OK)
    {
        printf("Memory Manager init failed with code %lu\n", errorNo);
    }
    else if ((errorNo = init_IterationManager(iterationManagerStruct)) != ITERATION_MANAGER_E_OK)
    {
        printf("Iteration Manager init failed with code %lu\n", errorNo);
    }
    else
    {
        printf("Manager init process finished successfully\n");
    }

    /* Bind comm ports */

    uiManagerStruct.parentPort          = &managerReportPort;
    iterationManagerStruct.parentPort   = &managerReportPort;
    networkManagerStruct.parentPort     = &managerReportPort;
    memoryManagerStruct.parentPort      = &managerReportPort;
    fileManagerStruct.parentPort        = &managerReportPort;

    /* Test comm ports */

    UserInterfaceSM_Init(&uiManagerStruct);
    std::thread uiManagerSMThread(UserInterfaceSM_Listen, &uiManagerStruct);
    uiManagerSMThread.detach(); /* prevent the destructor from joining the thread */
    uiManagerStruct.stateMachineHandle = &uiManagerSMThread;

    unsigned long long message = random();
    printf("Sending message %llu\n", message);
    
    while(PORT_MESSAGE_SENT != sendMessage(&(uiManagerStruct.uiManagerRxPort), ECHO, message))
    {
        sleep(0.4);
    }
    
    unsigned int receivedMessage = 0u;
    unsigned long long receivedMessageContainer = 0u; 
    
    printf("Entering while loop\n");
    while(PORT_MESSAGE_READ != readMessage(&(managerReportPort), &receivedMessage, &receivedMessageContainer))
    {
        sleep(0.4);
    }
    printf("SM responded with message %llu\n", receivedMessageContainer);

    return errorNo;
}


