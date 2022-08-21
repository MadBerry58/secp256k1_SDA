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

typedef struct
{
    pthread_mutex_t portLock = PTHREAD_MUTEX_INITIALIZER;
    unsigned int bufferWriteIndex = 0u;
    unsigned int bufferReadIndex = 0u;
    unsigned int bufferSize = 0u;
    bool** messagePresentFlag = NULL;
    void** messageContainer = NULL;
    void** messageBuffer = NULL;
    
}Port;

unsigned int initPort(unsigned int bufferSize, Port &targetPortStruct, auto bufferDataType, auto containerDataType)
{
    targetPortStruct.bufferSize = bufferSize;
    targetPortStruct.bufferReadIndex = 0u;
    targetPortStruct.bufferWriteIndex = 0u;
    targetPortStruct.messageBuffer = malloc(sizeof(bufferDataType) * bufferSize);
    targetPortStruct.messageContainer = malloc(sizeof(containerDataType) * bufferSize);
    targetPortStruct.messagePresentFlag = malloc(sizeof(bool) * bufferSize);
}

int sendMessage(Port &TxPort, auto message, auto messageData)
{
    int retVal = -1;
    if(EBUSY != pthread_mutex_trylock(&(TxPort.portLock)))
    {
        pthread_mutex_lock(&(TxPort.portLock));
        for(retVal = 1u; ( (retVal < TxPort.bufferSize) && (*(TxPort.messagePresentFlag[((++(*TxPort.bufferWriteIndex)) %= TxPort.bufferSize)]) != false)  ); ++retVal)
        if(false == *TxPort.bufferWriteIndex)
        {
            *(TxPort.messageContainer[TxPort.bufferWriteIndex]) = message;
            *(TxPort.messageBuffer[TxPort.bufferWriteIndex]) = messageData;
            *(TxPort.messagePresentFlag[TxPort.bufferWriteIndex]) = true;
            retVal = *TxPort.bufferWriteIndex;
        }
        pthread_mutex_unlock(&(TxPort.portLock));
    }
    return retVal;
}

int readMessage(Port &RxPort, auto &message, auto &messageData)
{
    int retVal = -1;
    if(EBUSY != pthread_mutex_trylock(&(RxPort.portLock)))
    {
        pthread_mutex_lock(&(RxPort.portLock));
        for(retVal = 1u; ( (retVal < RxPort.bufferSize) && (*(RxPort.messagePresentFlag[((++(*RxPort.bufferWriteIndex)) %= RxPort.bufferSize)]) != true)  ); ++retVal)
        if(true == *RxPort.bufferWriteIndex)
        {
            *(RxPort.messageContainer[RxPort.bufferWriteIndex]) = message;
            *(RxPort.messageBuffer[RxPort.bufferWriteIndex]) = messageData;
            *(RxPort.messagePresentFlag[RxPort.bufferWriteIndex]) = true;
            retVal = *RxPort.bufferWriteIndex;
        }
        pthread_mutex_unlock(&(RxPort.portLock));
    }
    return retVal;
}


