#include "Ports.h"

unsigned int initPort(Port *targetPortStruct, unsigned int bufferSize)
{
    targetPortStruct->bufferReadIndex    = 0u;
    targetPortStruct->bufferWriteIndex   = 0u;
    targetPortStruct->bufferSize         = bufferSize;
    targetPortStruct->messageBuffer      = (unsigned long long *)malloc(sizeof(unsigned long long) * bufferSize);
    targetPortStruct->messageContainer   = (unsigned int*)       malloc(sizeof(unsigned int)       * bufferSize);
    targetPortStruct->messagePresentFlag = (std::atomic_bool*)   malloc(sizeof(std::atomic_bool)   * bufferSize);
   *targetPortStruct->messagePresentFlag = {false};
    // if(0u != pthread_mutex_init(&(targetPortStruct->portLock), NULL))
    // {
    //     printf("Mutex initialization failed\n");
    // }
    // pthread_mutex_unlock(&(targetPortStruct->portLock));
    // targetPortStruct.portLock           = (pthread_mutex_t*)    malloc(sizeof(pthread_mutex_t)    * bufferSize);
    return COMM_E_OK;
}

unsigned int sendMessage(Port *TxPort, unsigned int message, unsigned long long messageData)
{
    int ret, i = 0ul;
    ret = PORT_EMPTY;
    for(i; i < TxPort->bufferSize; ++i)
    {
        if(TxPort->messagePresentFlag[TxPort->bufferWriteIndex] == false)
        {
            TxPort->messageContainer[TxPort->bufferWriteIndex]   = message;
            TxPort->messageBuffer[TxPort->bufferWriteIndex]      = messageData;
            TxPort->messagePresentFlag[TxPort->bufferWriteIndex] = true;
            ret = PORT_MESSAGE_SENT;
            break;
        }
        TxPort->bufferWriteIndex = ((TxPort->bufferWriteIndex + 1u) % TxPort->bufferSize);
    }
    return ret;
}

// unsigned int sendMessage(Port *TxPort, unsigned int message, unsigned long long messageData)
// {
//     int ret;
//     if(EBUSY == pthread_mutex_trylock(&(TxPort->portLock)))
//     {
//         ret = PORT_BUSY;
//     }
//     else
//     {
//         ret = PORT_EMPTY;
//         pthread_mutex_lock(&(TxPort->portLock));
//         for(int i = 0ul; i < TxPort->bufferSize; ++i)
//         {
//             if(TxPort->messagePresentFlag[TxPort->bufferWriteIndex])
//             {
//                 TxPort->messageContainer[TxPort->bufferWriteIndex]   = message;
//                 TxPort->messageBuffer[TxPort->bufferWriteIndex]      = messageData;
//                 TxPort->messagePresentFlag[TxPort->bufferWriteIndex] = false;
//                 ret = PORT_MESSAGE_SENT;
//                 break;
//             }
//             TxPort->bufferWriteIndex = ((TxPort->bufferWriteIndex + 1u) % TxPort->bufferSize);
//         }
//         pthread_mutex_unlock(&(TxPort->portLock));
//     }
//     return ret;
// }

/**
 * @brief Reads a message from the port's buffer
 * 
 * @param RxPort The target port containing the buffer
 * @param messageContainer The container to which the message will be copied
 * @param messageDataContainer The container to which the additional message data will be copied
 * @return int (-1)            - The port is being used by another process
 * @return int (1..bufferSize) - The data was read successfully from the buffer at the specified index
 * @return int (bufferSize)    - No readable data is present inside the buffer
 */
// unsigned int readMessage(Port *RxPort, unsigned int *messageContainer, unsigned long long *messageDataContainer)
// {
//     int ret;
//     if(EBUSY == pthread_mutex_trylock(&(RxPort->portLock)))
//     {
//         ret = PORT_BUSY;
//     }
//     else
//     {
//         pthread_mutex_lock(&(RxPort->portLock));
//         for(int i = 0ul; i < RxPort->bufferSize; ++i)
//         {
//             if(RxPort->messagePresentFlag[RxPort->bufferReadIndex] == true)
//             {
//                 *messageContainer = RxPort->messageContainer[RxPort->bufferReadIndex];
//                 *messageDataContainer = RxPort->messageBuffer[RxPort->bufferReadIndex];
//                 RxPort->messagePresentFlag[RxPort->bufferReadIndex] = true;
//                 break;
//             }
//         }
//         ret = (RxPort->messagePresentFlag[RxPort->bufferWriteIndex] * PORT_EMPTY) +
//               (RxPort->messagePresentFlag[RxPort->bufferWriteIndex] * PORT_MESSAGE_READ);
//         pthread_mutex_unlock(&(RxPort->portLock));
//     }
//     return ret;
// }

unsigned int readMessage(Port *RxPort, unsigned int *messageContainer, unsigned long long *messageDataContainer)
{
    int ret, i = 0ul;
    ret = PORT_EMPTY;
    for(i; i < RxPort->bufferSize; ++i)
    {
        if(RxPort->messagePresentFlag[RxPort->bufferReadIndex] == true)
        {
            *messageContainer       = RxPort->messageContainer[RxPort->bufferReadIndex];
            *messageDataContainer   = RxPort->messageBuffer   [RxPort->bufferReadIndex]   ;
            RxPort->messagePresentFlag[RxPort->bufferReadIndex] = false;
            ret = PORT_MESSAGE_READ;
            break;
        }
        RxPort->bufferReadIndex = ((RxPort->bufferReadIndex + 1u) % RxPort->bufferSize);
    }
    return ret;
}