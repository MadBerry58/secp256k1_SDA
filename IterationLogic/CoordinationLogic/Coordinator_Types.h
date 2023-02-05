#ifndef COORDINATOR_TYPES_H
#define COORDINATOR_TYPES_H

#include "../IteratorLogic/Iterator_Types.h"

enum CoordinatorSM_state
{
    COORDINATOR_SM_STATE_UNINITIALIZED,
    COORDINATOR_SM_STATE_READY,
    COORDINATOR_SM_STATE_RUNNING,
    COORDINATOR_SM_STATE_PAUSED,
    COORDINATOR_SM_STATE_FAULT,
    COORDINATOR_SM_STATE_SHUTDOWN
};

enum CoordinatorSM_workDist
{
    COORDINATOR_SM_DISTRIBUTION_UNDEFINED,
    COORDINATOR_SM_DISTRIBUTION_VERTICAL_SYNCED,
    COORDINATOR_SM_DISTRIBUTION_HORIZONTAL_SYNCED,
    COORDINATOR_SM_DISTRIBUTION_SCATTERED
};

struct CoordinatorSM_struct //CoordinatorSM structure
{
    IteratorSM_struct *iteratorInstanceArray = nullptr;
    CoordinatorSM_state   machineState = COORDINATOR_SM_STATE_UNINITIALIZED;
    // std::thread           *stateMachineHandle;
    // Port                  *memoryManagerPort  = nullptr;
    // Port                  *networkManagerPort = nullptr;
    // Port                  *fileManagerPort    = nullptr;
    // Port                  *clientSMPort       = nullptr;
    unsigned int           workerNumber       = 0u;
    unsigned int           workerBufferSize   = 0u;
    // IteratorSM_algorithm   chosenAlgorithm    = ITERATOR_SM_ALGORITHM_UNDEFINED;
    CoordinatorSM_workDist distribution       = COORDINATOR_SM_DISTRIBUTION_UNDEFINED;
    bool                   pauseFlag          = false;
    unsigned int           errorCode          = 0u; ///TODO: Add error code
};

enum IM_ModuleBitMasks
{
    INITIALIZED_BIT_MEMORYMANAGER_NONE            = 0b00000000,
    INITIALIZED_BIT_MEMORYMANAGER_KNOWNPOINTS_OK  = 0b00000001,
    INITIALIZED_BIT_MEMORYMANAGER_KNOWNPOINTS_NEW = 0b00000010,
    INITIALIZED_BIT_MEMORYMANAGER_POINTPOOL_OK    = 0b00000100,
    INITIALIZED_BIT_MEMORYMANAGER_POINTPOOL_NEW   = 0b00001000,
    INITIALIZED_BIT_MEMORYMANAGER_UNASSIGNED0     = 0b00010000,
    INITIALIZED_BIT_MEMORYMANAGER_UNASSIGNED1     = 0b00100000,
    INITIALIZED_BIT_MEMORYMANAGER_UNASSIGNED2     = 0b01000000,
    INITIALIZED_BIT_MEMORYMANAGER_FAULT           = 0b10000000,

    INITIALIZED_BIT_MEMORYMANAGER_CLIENT_READY    = 0b00000110,
    INITIALIZED_BIT_MEMORYMANAGER_SERVER_READY    = 0b00000111,
    INITIALIZED_BIT_MEMORYMANAGER_SATELLITE_READY = 0b00000111
};

#endif