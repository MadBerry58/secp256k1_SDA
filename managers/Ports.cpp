#include "Ports.h"
#include "MemoryManager/MemoryManager.h"

unsigned int initPort(Port *targetPortStruct, unsigned int bufferSize)
{
    targetPortStruct->bufferReadIndex    = 0u;
    targetPortStruct->bufferWriteIndex   = 0u;
    targetPortStruct->bufferSize         = bufferSize;
    targetPortStruct->messageBuffer      = (unsigned long long *)malloc(sizeof(unsigned long long) * bufferSize);
    targetPortStruct->messageContainer   = (unsigned int*)       malloc(sizeof(unsigned int)       * bufferSize);
    targetPortStruct->messagePresentFlag = (std::atomic_bool*)   malloc(sizeof(std::atomic_bool)   * bufferSize);
   *targetPortStruct->messagePresentFlag = {false};
    return COMM_E_OK;
}

/**
 * @brief Initialize target mpz buffer port
 * 
 * @pre Port data structure must be initialized by the caller with the buffer number data
 * @param targetPortStruct The adress of the structure holding the port data
 * @return unsigned int Error response
 */
unsigned int initPort_mpz(MpzBufferPort *targetPortStruct)
{
    unsigned int retVal = 0u;
    if(targetPortStruct->buffer_size < 2u)
    {
        retVal = PORT_E_BUFFERSIZE_INVALID;
    }
    else
    {
        /* call memory manager to initialize the buffers */
        targetPortStruct->buffers = init_mpzBuffers(targetPortStruct->buffer_size, targetPortStruct->buffer_number);
        /* initialize locks (per buffer) */
        targetPortStruct->locks = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * targetPortStruct->buffer_number);
                targetPortStruct->bufferFull = (bool*)malloc(sizeof(bool) * targetPortStruct->buffer_number);
        for(int i = 0; i < targetPortStruct->buffer_number; ++i)
        {
            /* Initialize lock */
            targetPortStruct->locks[i] = PTHREAD_MUTEX_INITIALIZER;
            /* Mark port as initialized */
            targetPortStruct->initialized = true;
        }
        retVal = PORT_E_OK;
    }
    return retVal;
}

/**
 * @brief Initialize target Point buffer port
 * 
 * @pre Port data structure must be initialized by the caller with the buffer number data
 * @param targetPortStruct The adress of the structure holding the port data
 * @return unsigned int Error response
 */
unsigned int initPort_point(PointBufferPort *targetPortStruct)
{
    unsigned int retVal = 0u;
    if(targetPortStruct->buffer_size < 2u)
    {
        retVal = PORT_E_BUFFERSIZE_INVALID;
    }
    else
    {
        /* call memory manager to initialize the buffers */
        targetPortStruct->buffers = init_PointBuffers(targetPortStruct->buffer_size, targetPortStruct->buffer_number);
        /* initialize locks (per buffer) */
        targetPortStruct->locks = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * targetPortStruct->buffer_number);
        targetPortStruct->bufferFull = (bool*)malloc(sizeof(bool) * targetPortStruct->buffer_number);
        for(int i = 0; i < targetPortStruct->buffer_number; ++i)
        {
            /* Initialize lock */
            targetPortStruct->locks[i] = PTHREAD_MUTEX_INITIALIZER;
            /* Mark port as initialized */
            targetPortStruct->initialized = true;
        }
        retVal = PORT_E_OK;
    }
    return retVal;
}

unsigned int sendMessage(Port *TxPort, unsigned long long message, unsigned long long messageData)
{
    int ret, i = 0ul;
    ret = PORT_E_EMPTY;
    for(i; i < TxPort->bufferSize; ++i)
    {
        if(TxPort->messagePresentFlag[TxPort->bufferWriteIndex] == false)
        {
            TxPort->messageContainer[TxPort->bufferWriteIndex]   = message;
            TxPort->messageBuffer[TxPort->bufferWriteIndex]      = messageData;
            TxPort->messagePresentFlag[TxPort->bufferWriteIndex] = true;
            ret = PORT_E_OK;
            break;
        }
        TxPort->bufferWriteIndex = ((TxPort->bufferWriteIndex + 1u) % TxPort->bufferSize);
    }
    return ret;
}

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

unsigned int readMessage(Port *RxPort, unsigned long long *messageContainer, unsigned long long *messageDataContainer, unsigned int match)
{
    int ret = PORT_E_EMPTY;
    int internalIndexBuffer = RxPort->bufferReadIndex;
    for(int i = 0u; i < RxPort->bufferSize; ++i)
    {
        if(
            (RxPort->messagePresentFlag[internalIndexBuffer] == true) &&
            (
                (0u == match) ||
                (RxPort->messageContainer[internalIndexBuffer] == match)
            )
          )
        {
            *messageContainer       = RxPort->messageContainer[internalIndexBuffer];
            *messageDataContainer   = RxPort->messageBuffer   [internalIndexBuffer];
            RxPort->messagePresentFlag[internalIndexBuffer] = false;
            ret = PORT_E_FOUND;
            break;
        }
        //allow the index to rotate around the buffer 
        internalIndexBuffer = ((internalIndexBuffer + 1u) % RxPort->bufferSize);
    }

    return ret;
}