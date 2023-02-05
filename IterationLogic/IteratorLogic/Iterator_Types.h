#ifndef ITERATOR_TYPES_H
#define ITERATOR_TYPES_H

#include <thread>

enum IteratorSM_input//IteratorSM input commands
{
    ITERATOR_SM_RX_NONE,
    ITERATOR_SM_RX_START,
    ITERATOR_SM_RX_SHUTDOWN,
    ITERATOR_SM_RX_CONFIRM_CONNECTION_REQUEST,
    ITERATOR_SM_RX_CONFIRM_BUFFER_REQUEST,
    ITERATOR_SM_RX_CONTINUE
};

enum IteratorSM_output //IteratorSM output commands
{
    ITERATOR_SM_TX_NONE,
    ITERATOR_SM_TX_REQUEST_CONNECTION,
    ITERATOR_SM_TX_REQUEST_POINT_BUFFER,
    ITERATOR_SM_TX_BUFFER_SWITCHED,
    ITERATOR_SM_TX_BUFFER_OVERFLOW
};

enum IteratorSM_state //IteratorSM states
{
    ITERATOR_SM_STATE_UNINITIALIZED,
    ITERATOR_SM_STATE_READY,
    ITERATOR_SM_STATE_RUNNING,
    ITERATOR_SM_STATE_PAUSED,
    ITERATOR_SM_STATE_FAULT,
    ITERATOR_SM_STATE_SHUTDOWN
};

enum IteratorSM_algorithm //IteratorSM iteration algorithm type
{
    ITERATOR_SM_ALGORITHM_UNDEFINED,
    ITERATOR_SM_ALGORITHM_CONTINUOUS_STEPS,
    ITERATOR_SM_ALGORITHM_SLICED_STEPS,
    ITERATOR_SM_ALGORITHM_CONTINUOUS_MULTIPLY,
    ITERATOR_SM_ALGORITHM_CONTINUOUS_DOUBLING,
    ITERATOR_SM_ALGORITHM_BTREE_SUBDIVISION
};

struct IteratorSM_struct //IteratorSM structure
{
    // bool RxNotificationFlag; //flag signaling the presence of an incomming message
    // IteratorSM_input RxFlag; /* Incomming message container */
    // bool TxNotificationFlag = false; //flag signaling the presence of an outgoing message
    // IteratorSM_output TxFlag; 
    // unsigned int (*iterationAlgorithm)(void **args, unsigned int arg_no) = nullptr;

    // Point **buffer;     //pointer to a Point buffer array. The pointer is used to allow buffer swapping by the coordinator, in order to reduce downtime
    // unsigned long long errorNo; //variable holding the error code associated to the FAULT state

    unsigned int bufferSize = 0u;
    int smID = -1;
    unsigned int currentBufferIndex = 0u;
    IteratorSM_state machineState = ITERATOR_SM_STATE_UNINITIALIZED;
    IteratorSM_algorithm algorithm = ITERATOR_SM_ALGORITHM_UNDEFINED;
    bool pauseFlag = false;
    std::thread stateMachineHandle;
} ;

#endif