#include "Ports.h"
#include "../Arithmetic/ModularArithmetic/Mod.h"
#include "../Arithmetic/PointArithmetic/Point.h"
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

unsigned long long messageIndex;
Port managerReportPort;

IterationManagerData    iterationManagerStruct;
NetworkManagerData      networkManagerStruct;
MemoryManagerData       memoryManagerStruct;
FileManagerData         fileManagerStruct;
UI_SM_struct            uiManagerStruct;


unsigned int init_Managers(InitDataStruct initData)
{
    gmp_printf("Initial Testing Checkpoint 2: managers.cpp\n");
    unsigned long errorNo = 0u;
    unsigned int managerStatus = 0l;

    /* Initialize manager report port */
    if((errorNo = initPort(&managerReportPort, MANAGER_REPORT_PORT_BUFFER_SIZE)) != COMM_E_OK)
    {
        printf("Manager port initialization failed with error code %lu\n", errorNo);
    }

    /* Bind comm ports */
    uiManagerStruct.parentPort          = &managerReportPort;
    iterationManagerStruct.parentPort   = &managerReportPort;
    networkManagerStruct.parentPort     = &managerReportPort;
    memoryManagerStruct.parentPort      = &managerReportPort;
    fileManagerStruct.parentPort        = &managerReportPort;

    /* Test comm ports */
    init_UserInterfaceSM(&uiManagerStruct);
    std::thread uiManagerSMThread(start_UserInterfaceSM, &uiManagerStruct);
    // uiManagerSMThread.detach(); /* prevent the destructor from joining the thread. !! thread variables are a pain to reuse. make sure threads don't have to be reinitialized */
    uiManagerStruct.stateMachineHandle = &uiManagerSMThread;

    unsigned long long receivedMessage = 0u;
    unsigned long long receivedMessageContainer = 0u;

    while (UI_SM_TX_USERMODE_EXIT != receivedMessage)
    {
        bool internalLoopControl = false;
        if(PORT_E_FOUND == readMessage(&(managerReportPort), &receivedMessage, &receivedMessageContainer, 0u))
        {
            switch(receivedMessage)
            {
                case UI_SM_TX_USERMODE_SERVER:
                    networkManagerStruct.functionMode = NM_MODE_SERVER;
                    
                    sendMessage(&(uiManagerStruct.uiManagerRxPort), UI_SM_RX_NETWORK_INIT_STATE, networkManagerStruct.initializedMembers);
                    internalLoopControl = true;
                    while(internalLoopControl)
                    {
                        if  ((0u == (INITIALIZED_BIT_NETWORKMANAGER_MAXCLIENTNO & networkManagerStruct.initializedMembers)) &&
                                (PORT_E_FOUND == readMessage(&(managerReportPort), &receivedMessage, &receivedMessageContainer, UI_SM_TX_INIT_NETWORKMANAGER_CLIENTNO)))
                        {
                            networkManagerStruct.maxClients = receivedMessageContainer;
                            printf("%lld max clients selected\n", receivedMessageContainer);
                            networkManagerStruct.initializedMembers |= INITIALIZED_BIT_NETWORKMANAGER_MAXCLIENTNO;
                        }
                        else if((0u == (INITIALIZED_BIT_NETWORKMANAGER_SERVERIP & networkManagerStruct.initializedMembers)) &&
                                (PORT_E_FOUND == readMessage(&(managerReportPort), &receivedMessage, &receivedMessageContainer, UI_SM_TX_INIT_NETWORKMANAGER_IP)))
                        {
                            networkManagerStruct.workersPerCoordinator = receivedMessageContainer;
                            networkManagerStruct.initializedMembers |= INITIALIZED_BIT_NETWORKMANAGER_SERVERIP;
                        }
                        else if((0u == (INITIALIZED_BIT_NETWORKMANAGER_SERVERPORT & networkManagerStruct.initializedMembers)) &&
                                (PORT_E_FOUND == readMessage(&(managerReportPort), &receivedMessage, &receivedMessageContainer, UI_SM_TX_INIT_NETWORKMANAGER_PORT)))
                        {
                            networkManagerStruct.workersPerCoordinator = receivedMessageContainer;
                            networkManagerStruct.initializedMembers |= INITIALIZED_BIT_NETWORKMANAGER_SERVERPORT;
                        }
                        else if (INITIALIZED_BIT_NETWORKMANAGER_SERVER_READY == networkManagerStruct.initializedMembers)
                        {
                            internalLoopControl = false;
                            managerStatus |= INITIALIZED_BIT_NETWORKMANAGER;
                        }
                        else if (INITIALIZED_BIT_NETWORKMANAGER_FAULT & networkManagerStruct.initializedMembers)
                        {
                            internalLoopControl = false;
                            managerStatus |= INITIALIZED_BIT_FAULT;
                            printf("An error was encountered during network manager initialization\n");
                        }
                    }

                    sendMessage(&(uiManagerStruct.uiManagerRxPort), UI_SM_RX_FILE_INIT_STATE, networkManagerStruct.initializedMembers);
                    internalLoopControl = true;
                    while(internalLoopControl)
                    {
                        // if  ((0u == (INITIALIZED_BIT_NETWORKMANAGER_MAXCLIENTNO & networkManagerStruct.initializedMembers)) &&
                        //         (PORT_E_FOUND == readMessage(&(managerReportPort), &receivedMessage, &receivedMessageContainer, UI_SM_TX_INIT_NETWORKMANAGER_CLIENTNO)))
                        // {
                        //     networkManagerStruct.maxClients = receivedMessageContainer;
                        //     printf("%lld max clients selected\n", receivedMessageContainer);
                        //     networkManagerStruct.initializedMembers |= INITIALIZED_BIT_NETWORKMANAGER_MAXCLIENTNO;
                        // }
                        // else if((0u == (INITIALIZED_BIT_NETWORKMANAGER_SERVERIP & networkManagerStruct.initializedMembers)) &&
                        //         (PORT_E_FOUND == readMessage(&(managerReportPort), &receivedMessage, &receivedMessageContainer, UI_SM_TX_INIT_NETWORKMANAGER_IP)))
                        // {
                        //     networkManagerStruct.workersPerCoordinator = receivedMessageContainer;
                        //     networkManagerStruct.initializedMembers |= INITIALIZED_BIT_NETWORKMANAGER_SERVERIP;
                        // }
                        // else if((0u == (INITIALIZED_BIT_NETWORKMANAGER_SERVERPORT & networkManagerStruct.initializedMembers)) &&
                        //         (PORT_E_FOUND == readMessage(&(managerReportPort), &receivedMessage, &receivedMessageContainer, UI_SM_TX_INIT_NETWORKMANAGER_PORT)))
                        // {
                        //     networkManagerStruct.workersPerCoordinator = receivedMessageContainer;
                        //     networkManagerStruct.initializedMembers |= INITIALIZED_BIT_NETWORKMANAGER_SERVERPORT;
                        // }
                        // else if (INITIALIZED_BIT_NETWORKMANAGER_SERVER_READY == networkManagerStruct.initializedMembers)
                        // {
                        //     internalLoopControl = false;
                        //     managerStatus |= INITIALIZED_BIT_NETWORKMANAGER;
                        // }
                        // else if (INITIALIZED_BIT_NETWORKMANAGER_FAULT & networkManagerStruct.initializedMembers)
                        // {
                        //     internalLoopControl = false;
                        //     managerStatus |= INITIALIZED_BIT_FAULT;
                        //     printf("An error was encountered during network manager initialization\n");
                        // }
                    }
                    
                    //file manager
                    //memory manager
                    break;

                case UI_SM_TX_USERMODE_CLIENT:
                    networkManagerStruct.functionMode = NM_MODE_CLIENT;
                    //file manager
                        //if no file is found, allow for manual introduction 
                    break;

                case UI_SM_TX_USERMODE_SATELLITE:
                    networkManagerStruct.maxClients = receivedMessageContainer;
                    networkManagerStruct.functionMode = NM_MODE_SATELLITE;
                    
                    break;

                case UI_SM_TX_USERMODE_TESTING:
                    
                    networkManagerStruct.functionMode = NM_MODE_TEST;
                    
                    break;
                
                case UI_SM_TX_USERMODE_EXIT:
                    

                    break;

                case UI_SM_TX_USERREQUEST_START:

                    /* Initialize manager functionality */
                    if(0b1111 != initData.initializedModules)
                    {
                        if((INITIALIZED_BIT_NETWORKMANAGER & initData.initializedModules) == 0)
                        {printf("Network manager data not provided\n");}
                        if((INITIALIZED_BIT_NETWORKMANAGER & initData.initializedModules) == 0)
                        {printf("File manager data not provided\n");}
                        if((INITIALIZED_BIT_NETWORKMANAGER & initData.initializedModules) == 0)
                        {printf("Memory manager data not provided\n");}
                        if((INITIALIZED_BIT_NETWORKMANAGER & initData.initializedModules) == 0)
                        {printf("Iteration manager data not provided\n");}
                        if((INITIALIZED_BIT_NETWORKMANAGER & initData.initializedModules) == 0)
                        {printf("An error prevented the initial data aquisition\n");}
                    }
                    else if((errorNo = init_FileManager(&fileManagerStruct)) != INTEGRITY_E_FILE_INIT_OK)
                    {
                        printf("File Manager init failed with code %lu\n", errorNo);
                    }
                    else if ((errorNo = init_NetworkManager(&networkManagerStruct)) != NETWORK_MANAGER_E_OK)
                    {
                        printf("Network Manager init failed with code %lu\n", errorNo);
                    }
                    else if ((errorNo = init_MemoryManager(&memoryManagerStruct)) != MEMORY_MANAGER_E_OK)
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
                    break;

                case UI_SM_TX_FAULT:
                    
                    break;
                default:
                    break;
            }
        }
        sleep(UI_SM_CYCLE);
        /* code */
    }

    return errorNo;
}


