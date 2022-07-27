#include "../NetworkManager.h"

unsigned int startClientSM(std::string message)
{
    clientSMStruct messageStruct;
    messageStruct.dummyData = message;
    std::thread ClientSMThread(init_ClientSM, messageStruct);
    ClientSMThread.join();
    std::cout << "\n\nClientSM thread stopped\n" << std::endl;
    return 0;
}

unsigned int startClientHandlerSM(/**protocol**/)
{
    return 0;
}

unsigned int startSatelliteSM(/**protocol**/)
{
    return 0;
}

unsigned int startSatelliteHandlerSM(/**protocol**/)
{
    return 0;
}

unsigned int startServerFrontendSM(/**protocol**/)
{
    return 0;
}

unsigned int startDummySM(std::string message)
{
    dummyStruct messageStruct;
    messageStruct.dummyInt = 36u;
    strcpy(messageStruct.dummyBuffer, "Test Buffer message");
    messageStruct.dummyString = message;
    std::thread dummyThread(init_dummySM, messageStruct);
    dummyThread.join();
    std::cout << "\n\nDummy thread stopped\n" << std::endl;
    return 0;
}