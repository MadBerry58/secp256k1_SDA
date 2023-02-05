#include "Iterator.h"

#include "IteratorSM/IteratorSM.h"
#include <stdio.h>

unsigned int Iterator_create (IteratorSM_struct &iteratorInstance)
{
    printf("Iterator SM with id %d with buffer size %d data structure created\n", iteratorInstance.smID, iteratorInstance.bufferSize);
    return 0u;
}

unsigned int Iterator_init (IteratorSM_struct &iteratorInstance)
{
    
    return 0;
}

unsigned int IteratorSM_run  (IteratorSM_struct &iteratorInstance)
{
    return 0;
}

unsigned int IteratorSM_reset(IteratorSM_struct &iteratorInstance)
{
    return 0;
}

/* Internal functionality */
unsigned int switchBuffer    (IteratorSM_struct &iteratorInstance)
{
    return 0;
}

/* Salvaged code:

while (false == iteratorInstance.RxNotificationFlag) // wait for coordinator to process the request
                {
                    sleep(ITERATOR_SM_RETRY_DELAY);
                }
                if(false == iteratorInstance.RxNotificationFlag)
                {
                    iteratorInstance.errorNo = ITERATOR_SM_E_CONNECTION_TIMEOUT;
                    iteratorInstance.machineState = ITERATOR_SM_STATE_FAULT;
                    break;
                }
                else if(ITERATOR_SM_RX_CONFIRM_CONNECTION_REQUEST != iteratorInstance.RxFlag)
                {
                    iteratorInstance.errorNo = ITERATOR_SM_E_CONNECTION_INVALID_RESPONSE;
                    iteratorInstance.machineState = ITERATOR_SM_STATE_FAULT;
                    break;
                }
                else
                {
                    //Communication channel has been set up successfully
                }


    //Initialize necessary algorithm iteratorInstance structures
                switch (iteratorInstance.algorithm)
                // (*fun_ptr_arr[ch])(a, b);
                {
                    case ITERATOR_SM_ALGORITHM_UNDEFINED:
                        iteratorInstance.machineState = ITERATOR_SM_STATE_FAULT;
                        iteratorInstance.errorNo = ITERATOR_SM_E_INVALID_ALGORITHM_ID;
                        break;

                    case ITERATOR_SM_ALGORITHM_CONTINUOUS_STEPS:
                        
                        break;

                    case ITERATOR_SM_ALGORITHM_SLICED_STEPS:
                        
                        break;

                    case ITERATOR_SM_ALGORITHM_CONTINUOUS_MULTIPLY:
                        
                        break;
                    
                    case ITERATOR_SM_ALGORITHM_CONTINUOUS_DOUBLING:
                        
                        break;
                    
                    case ITERATOR_SM_ALGORITHM_BTREE_SUBDIVISION:
                        // Initiate variable containers (assuming constant iteratorInstance is located inside IteratorSM)
                        break;

                    default:
                        break;
                }

                while (false == iteratorInstance.RxNotificationFlag)
            {
                if(true == iteratorInstance.RxNotificationFlag)
                {
                    switch (iteratorInstance.RxFlag)
                    {
                        case ITERATOR_SM_RX_START:
                            //Start the iteration
                            iteratorInstance.machineState = ITERATOR_SM_STATE_RUNNING;
                            break;

                        case ITERATOR_SM_RX_SHUTDOWN:
                            //Shutdown the state machine
                            iteratorInstance.machineState = ITERATOR_SM_STATE_SHUTDOWN;
                            break;

                        default:
                            iteratorInstance.machineState = ITERATOR_SM_STATE_FAULT;
                            iteratorInstance.errorNo = ITERATOR_SM_E_INVALID_RX;
                            break;
                    }
                }
            }
                // Wait for commands from coordinator
            while (false == iteratorInstance.RxNotificationFlag)
            {
                if(true == iteratorInstance.RxNotificationFlag)
                {
                    switch (iteratorInstance.RxFlag)
                    {
                        case ITERATOR_SM_RX_CONTINUE:
                            // Start the iteration 
                            iteratorInstance.machineState = ITERATOR_SM_STATE_RUNNING;
                            break;

                        case ITERATOR_SM_RX_SHUTDOWN:
                            // Shutdown the state machine 
                            iteratorInstance.machineState = ITERATOR_SM_STATE_SHUTDOWN;
                            break;

                        default:
                            iteratorInstance.machineState = ITERATOR_SM_STATE_FAULT;
                            iteratorInstance.errorNo = ITERATOR_SM_E_INVALID_RX;
                            break;
                    }
                }
            }
 */