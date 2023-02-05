#ifndef PORTS_TYPE_H
#define PORTS_TYPE_H

struct Port
{
    // pthread_mutex_t      portLock            = PTHREAD_MUTEX_INITIALIZER;
    unsigned int         bufferWriteIndex    = 0u;
    unsigned int         bufferReadIndex     = 0u;
    unsigned int         bufferSize          = 0u;
    // pthread_mutex_t*     portLock            = nullptr;
    // std::atomic_bool*    messagePresentFlag;
    unsigned int*        messageContainer    = nullptr;
    unsigned long long*  messageBuffer       = nullptr;
    
};

struct MpzBufferPort //ports used for internally transfering keys and hashes
{
    bool initialized;
    // unsigned long ownerID;
    unsigned int buffer_size = 0u;
    unsigned int buffer_number = 2u; /* The port requires at least two buffers to allow concurrent operation */
    // pthread_mutex_t *locks = nullptr; /* Locks are initialized inside the port software component */
    bool *bufferFull = nullptr;
    // mpz_t*** buffers;
};

struct PointBufferPort
{
    bool initialized;
    // unsigned long ownerID;
    unsigned int buffer_size = 0;
    unsigned int buffer_number = 2u; /* The port requires at least two buffers to allow concurrent operation */
    // pthread_mutex_t *locks = nullptr; /* Locks are initialized inside the port software component */
    bool *bufferFull = nullptr;
    // Point*** buffers;
};

#endif