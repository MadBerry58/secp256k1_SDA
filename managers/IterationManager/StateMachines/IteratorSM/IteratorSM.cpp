#include "IteratorSM.h"
#include "../../../../Arithmetic/Arithmetic.h"

unsigned int init_IteratorSM(IteratorSMStruct *data)
{
    return 0;
}

unsigned int IteratorSM(IteratorSMStruct *data)
{
    bool internalTrigger = false;
    while(data->SMstate != ITERATOR_SM_STATE_SHUTDOWN)
    {
        switch (data->SMstate)
        {
            case ITERATOR_SM_STATE_UNINITIALIZED:
                /* Initialize the state machine */
                
                /* establish connection with a coordinatorSM */
                // sendMessage(ITERATOR_SM_TX_REQUEST_CONNECTION, &data->TxNotificationFlag, &data->TxFlag);
                while (false == data->RxNotificationFlag) /* wait for coordinator to process the request*/
                {
                    sleep(ITERATOR_SM_RETRY_DELAY);
                }
                if(false == data->RxNotificationFlag)
                {
                    data->errorNo = ITERATOR_SM_E_CONNECTION_TIMEOUT;
                    data->SMstate = ITERATOR_SM_STATE_FAULT;
                    break;
                }
                else if(ITERATOR_SM_RX_CONFIRM_CONNECTION_REQUEST != data->RxFlag)
                {
                    data->errorNo = ITERATOR_SM_E_CONNECTION_INVALID_RESPONSE;
                    data->SMstate = ITERATOR_SM_STATE_FAULT;
                    break;
                }
                else
                {
                    /* Communication channel has been set up successfully */
                }

                /* Initialize necessary algorithm data structures */
                switch (data->algorithm)
                // (*fun_ptr_arr[ch])(a, b);
                {
                    case ITERATOR_SM_ALGORITHM_UNDEFINED:
                        data->SMstate = ITERATOR_SM_STATE_FAULT;
                        data->errorNo = ITERATOR_SM_E_INVALID_ALGORITHM_ID;
                        break;

                    case ITERATOR_SM_ALGORITHM_CONTINUOUS_STEPS:
                        /* code */
                        break;

                    case ITERATOR_SM_ALGORITHM_SLICED_STEPS:
                        /* code */
                        break;

                    case ITERATOR_SM_ALGORITHM_CONTINUOUS_MULTIPLY:
                        /* code */
                        break;
                    
                    case ITERATOR_SM_ALGORITHM_CONTINUOUS_DOUBLING:
                        /* code */
                        break;
                    
                    case ITERATOR_SM_ALGORITHM_BTREE_SUBDIVISION:
                        /* Initiate variable containers (assuming constant data is located inside IteratorSM) */
                        break;

                    default:
                        break;
                }
                //initialize iteration variables and buffer pointers
                break;

        case ITERATOR_SM_STATE_READY:
            while (false == data->RxNotificationFlag)
            {
                if(true == data->RxNotificationFlag)
                {
                    switch (data->RxFlag)
                    {
                        case ITERATOR_SM_RX_START:
                            /* Start the iteration */
                            data->SMstate = ITERATOR_SM_STATE_RUNNING;
                            break;

                        case ITERATOR_SM_RX_SHUTDOWN:
                            /* Shutdown the state machine */
                            data->SMstate = ITERATOR_SM_STATE_SHUTDOWN;
                            break;

                        default:
                            data->SMstate = ITERATOR_SM_STATE_FAULT;
                            data->errorNo = ITERATOR_SM_E_INVALID_RX;
                            break;
                    }
                }
            }
            break;
        
        case ITERATOR_SM_STATE_RUNNING:
            /* Run chosen algorithm */

            break;

        case ITERATOR_SM_STATE_WAITING:
            /* Wait for commands from coordinator */
            while (false == data->RxNotificationFlag)
            {
                if(true == data->RxNotificationFlag)
                {
                    switch (data->RxFlag)
                    {
                        case ITERATOR_SM_RX_CONTINUE:
                            /* Start the iteration */
                            data->SMstate = ITERATOR_SM_STATE_RUNNING;
                            break;

                        case ITERATOR_SM_RX_SHUTDOWN:
                            /* Shutdown the state machine */
                            data->SMstate = ITERATOR_SM_STATE_SHUTDOWN;
                            break;

                        default:
                            data->SMstate = ITERATOR_SM_STATE_FAULT;
                            data->errorNo = ITERATOR_SM_E_INVALID_RX;
                            break;
                    }
                }
            }
            break;

        case ITERATOR_SM_STATE_FAULT:
            /* Wait for commands from coordinator */
            
            break;
        default:
            break;
        }
    }
    return 0;
}