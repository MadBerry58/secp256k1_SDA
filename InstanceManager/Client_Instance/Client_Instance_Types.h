#ifndef CLIENT_INSTANCE_TYPE_H
#define CLIENT_INSTANCE_TYPE_H

struct ClientInstance_struct{
    unsigned int workers            = 0u;
    unsigned int workerBufferSize   = 0u;
};

enum IT_ModuleBitMasks
{
    INITIALIZED_BIT_ITERATIONMANAGER_NONE          = 0b00000000,
    INITIALIZED_BIT_ITERATIONMANAGER_COORDNO       = 0b00000010,
    INITIALIZED_BIT_ITERATIONMANAGER_ITERATORNO    = 0b00000100,
    INITIALIZED_BIT_ITERATIONMANAGER_NOTASSIGNED0  = 0b00001000,
    INITIALIZED_BIT_ITERATIONMANAGER_NOTASSIGNED1  = 0b00010000,
    INITIALIZED_BIT_ITERATIONMANAGER_NOTASSIGNED2  = 0b00100000,
    INITIALIZED_BIT_ITERATIONMANAGER_NOTASSIGNED3  = 0b01000000,
    INITIALIZED_BIT_ITERATIONMANAGER_FAULT         = 0b10000000,

    INITIALIZED_BIT_ITERATIONMANAGER_READY         = 0b00000110
};

struct  IterationManagerData //IteratorManager initializer data
{
    // Port iterationManagerRxPort;
    // Port *parentPort;
    unsigned int coordinatorNo = 0u;
    unsigned int iteratorsPerCoordinator = 0u;
    bool managerInitialized = false;
};


#endif