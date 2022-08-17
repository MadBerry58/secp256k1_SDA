#include "managers.h"

unsigned int init_managers(std::string initData)
{
    init_NetworkManager(initData);
    long unsigned int errorNo = -1;
    if ((errorNo = fileManager_Init()) != INTEGRITY_E_FILE_INIT_OK)
    {
        printf("fileManagerInit failed with code %lu\n", errorNo);
    }


}

unsigned int sendMessage(auto message, bool *notificationFlag, auto *messageContainer)
{
    unsigned int retVal = 0u;
    if(true == *notificationFlag)
    {
        retVal = COMM_E_NOTIFICATION_PRESENT;
    }
    else
    {
        *messageContainer = message;
        *notificationFlag = true;
    }
}