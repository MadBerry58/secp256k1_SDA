#include "../TypeDef.h"
#ifndef SECP251K1_SANDBOX_PORTS_CPP
#define SECP251K1_SANDBOX_PORTS_CPP

unsigned int initPort(unsigned int bufferSize, Port &targetPortStruct)
{
    targetPortStruct.bufferReadIndex    = 0u;
    targetPortStruct.bufferWriteIndex   = 0u;
    targetPortStruct.bufferSize         = bufferSize;
    targetPortStruct.messageBuffer      = (unsigned long long *)malloc(sizeof(unsigned long long) * bufferSize);
    targetPortStruct.messageContainer   = (unsigned int*)       malloc(sizeof(unsigned int)       * bufferSize);
    targetPortStruct.messagePresentFlag = (bool*)               malloc(sizeof(bool)               * bufferSize);
    return 0;
}

int sendMessage(Port &TxPort, unsigned int message, unsigned long long messageData)
{
    int retVal = -1;
    if(EBUSY != pthread_mutex_trylock(&(TxPort.portLock)))
    {
        pthread_mutex_lock(&(TxPort.portLock));
        for(retVal = 1u; ((retVal <  TxPort.bufferSize) && (false  != ( TxPort.messagePresentFlag[((++(TxPort.bufferWriteIndex)) %= TxPort.bufferSize)]) ) ); ++retVal)
        if(false == TxPort.bufferWriteIndex)
        {
            TxPort.messageContainer[TxPort.bufferWriteIndex] = message;
            TxPort.messageBuffer[TxPort.bufferWriteIndex] = messageData;
            TxPort.messagePresentFlag[TxPort.bufferWriteIndex] = true;
            retVal = TxPort.bufferWriteIndex;
        }
        pthread_mutex_unlock(&(TxPort.portLock));
    }
    return retVal;
}

int readMessage(Port &RxPort, unsigned int &message, unsigned long long messageData)
{
    int retVal = -1;
    if(EBUSY != pthread_mutex_trylock(&(RxPort.portLock)))
    {
        pthread_mutex_lock(&(RxPort.portLock));
        for(retVal = 1u; ( (retVal < RxPort.bufferSize) && (RxPort.messagePresentFlag[((++(RxPort.bufferWriteIndex)) %= RxPort.bufferSize)] != true) ); ++retVal)
        if(true == RxPort.bufferWriteIndex)
        {
            RxPort.messageContainer[RxPort.bufferWriteIndex] = message;
            RxPort.messageBuffer[RxPort.bufferWriteIndex] = messageData;
            RxPort.messagePresentFlag[RxPort.bufferWriteIndex] = true;
            retVal = RxPort.bufferWriteIndex;
        }
        pthread_mutex_unlock(&(RxPort.portLock));
    }
    return retVal;
}
#endif /*SECP251K1_SANDBOX_PORTS_CPP*/