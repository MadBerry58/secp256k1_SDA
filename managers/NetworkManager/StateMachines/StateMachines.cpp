#include "StateMachines.h"

std::thread *startClientSM(clientSMStruct *messageStruct)
{
    init_ClientSM(messageStruct);
    std::thread clientSMThread(ClientSM, messageStruct);
    clientSMThread.detach(); /* prevent the destructor from joining the thread */
    messageStruct->stateMachineHandle = &clientSMThread;
    return messageStruct->stateMachineHandle;
}
unsigned int stopClientSM(clientSMStruct *messageStruct)
{
    messageStruct->stateMachineHandle->join();
    std::cout << "\n\nClientSM thread stopped\n" << std::endl;
    return 0;
}

std::thread *startClientHandlerSM(clientHandlerSMStruct *messageStruct)
{
    init_ClientHandlerSM(messageStruct);
    std::thread clientHandlerSMThread(ClientHandlerSM, messageStruct);
    clientHandlerSMThread.detach(); /* prevent the destructor from joining the thread */
    messageStruct->stateMachineHandle = &clientHandlerSMThread;
    return messageStruct->stateMachineHandle;
}
unsigned int stopClientHandlerSM(clientHandlerSMStruct *messageStruct)
{
    messageStruct->stateMachineHandle->join();
    std::cout << "\n\nClientHandlerSM thread stopped\n" << std::endl;
    return 0;
}

std::thread *startSatelliteSM(satelliteSMStruct *messageStruct)
{
    init_SatelliteSM(messageStruct);
    std::thread satelliteSMThread(SatelliteSM, messageStruct);
    satelliteSMThread.detach(); /* prevent the destructor from joining the thread */
    messageStruct->stateMachineHandle = &satelliteSMThread;
    return messageStruct->stateMachineHandle;
}
unsigned int stopSatelliteSM(satelliteSMStruct *messageStruct)
{
    messageStruct->stateMachineHandle->join();
    std::cout << "\n\nSatelliteSM thread stopped\n" << std::endl;
    return 0;
}

std::thread *startSatelliteHandlerSM(satelliteHandlerSMStruct *messageStruct)
{
    init_SatelliteHandlerSM(messageStruct);
    std::thread satelliteHandlerSMThread(SatelliteHandlerSM, messageStruct);
    satelliteHandlerSMThread.detach(); /* prevent the destructor from joining the thread */
    messageStruct->stateMachineHandle = &satelliteHandlerSMThread;
    return messageStruct->stateMachineHandle;
}
unsigned int stopSatelliteHandlerSM(satelliteHandlerSMStruct *messageStruct)
{
    messageStruct->stateMachineHandle->join();
    std::cout << "\n\nSatelliteHandlerSM thread stopped\n" << std::endl;
    return 0;
}

std::thread *startServerFrontendSM(ServerFrontendSMStruct *messageStruct)
{
    init_ServerFrontendSM(messageStruct);
    std::thread serverFrontendSMThread(ServerFrontendSM, messageStruct);
    serverFrontendSMThread.detach(); /* prevent the destructor from joining the thread */
    messageStruct->stateMachineHandle = &serverFrontendSMThread;
    return messageStruct->stateMachineHandle;
}
unsigned int stopServerFrontendSM(ServerFrontendSMStruct *messageStruct)
{
    /* Send stop message */
    messageStruct->stateMachineHandle->join();
    std::cout << "\n\nSatelliteHandlerSM thread stopped\n" << std::endl;
    return 0;
}