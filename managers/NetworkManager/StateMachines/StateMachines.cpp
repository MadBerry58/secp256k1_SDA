#include "StateMachines.h"

unsigned int startClientSM(std::string message)
{
    clientSMStruct messageStruct;
    messageStruct.dummyData = message;
    std::thread clientSMThread(init_ClientSM, &messageStruct);
    clientSMThread.join();
    std::cout << "\n\nClientSM thread stopped\n" << std::endl;
    return 0;
}

unsigned int startClientHandlerSM(std::string message)
{
    clientHandlerSMStruct messageStruct;
    messageStruct.dummyData = message;
    std::thread clientHandlerSMThread(ClientHandlerSM, &messageStruct);
    clientHandlerSMThread.join();
    std::cout << "\n\nClientHandlerSM thread stopped\n" << std::endl;
    return 0;
}

unsigned int startSatelliteSM(std::string message)
{
    satelliteSMStruct messageStruct;
    messageStruct.dummyData = message;
    std::thread satelliteSMThread(init_SatelliteSM, &messageStruct);
    satelliteSMThread.join();
    std::cout << "\n\nSatelliteSM thread stopped\n" << std::endl;
    return 0;
}

unsigned int startSatelliteHandlerSM(std::string message)
{
    satelliteHandlerSMStruct messageStruct;
    messageStruct.dummyData = message;
    std::thread satelliteHandlerSMThread(init_SatelliteHandlerSM, &messageStruct);
    satelliteHandlerSMThread.join();
    std::cout << "\n\nSatelliteHandlerSM thread stopped\n" << std::endl;
    return 0;
}

std::thread *startServerFrontendSM(ServerFrontendSMStruct messageStruct)
{
    std::thread serverFrontendSMThread(ServerFrontendSM, &messageStruct);
    messageStruct.ownerThreadAdress = &serverFrontendSMThread;
    return &serverFrontendSMThread;
}