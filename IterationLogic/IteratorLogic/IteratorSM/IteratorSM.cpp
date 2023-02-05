#include "IteratorSM.h"

#include <stdio.h>

#define PLACEHOLDER_OK 0
#define PLACEHOLDER_ERROR 1
#define PLACEHOLDER_INITIAL_UNDEFINED 2

bool loopControl = false;
bool subLoopControl = false;

///TODO: Create a default connection request function
// sendMessage(ITERATOR_SM_TX_REQUEST_CONNECTION, &iteratorInstance.TxNotificationFlag, &iteratorInstance.TxFlag);

unsigned int IteratorSM_init (IteratorSM_struct iteratorInstance)
{
    printf("Iterator SM initialized\n");
    ///TODO: Initialize sm
    /* Initialize the state machine */
    /* establish connection with a coordinatorSM */
    //initialize iteration variables and buffer pointers
    return 0u;
}

unsigned int IteratorSM_run  (IteratorSM_struct iteratorInstance)
{
    unsigned int retVal = 0;
    loopControl = true;
    while(loopControl)
    {
        switch (iteratorInstance.machineState)
        {
            case ITERATOR_SM_STATE_UNINITIALIZED:
                retVal = 1; ///TODO: add error code

                iteratorInstance.machineState = ITERATOR_SM_STATE_UNINITIALIZED; /* do not change the machine state */
                loopControl = false; /* break out of the run loop */
                break;

        case ITERATOR_SM_STATE_READY:

            iteratorInstance.machineState = ITERATOR_SM_STATE_RUNNING; /* do not change the machine state */
            loopControl = true; /* do not break out of the run loop */
            break;
        
        case ITERATOR_SM_STATE_RUNNING:
            /* Enter subloop */
            subLoopControl = true;
            while(subLoopControl)
            {
                retVal = Iterator_checkForEvents(iteratorInstance);
                if(retVal == 0u) /* Regular event handled */
                {
                    ///QUESTION: is runtime algorithm change worthwile, or is it more efficient to create separate SM cases for each?
                    /* Run chosen algorithm for a set amount of steps*/
                    retVal = Iterator_run_Algorithm(iteratorInstance);
                    if(retVal == 0) /* algorithm run was successful */
                    {
                        iteratorInstance.machineState = ITERATOR_SM_STATE_RUNNING;
                        subLoopControl = true; /* do not break out of the run subloop */
                        loopControl = true;    /* allow the SM to enter running state again */
                    }
                    else 
                    if(retVal == 1) /* buffer switched */
                    {
                        Iterator_notifyHandler(iteratorInstance, ITERATOR_SM_TX_BUFFER_SWITCHED);

                        iteratorInstance.machineState = ITERATOR_SM_STATE_RUNNING;
                        subLoopControl = true; /* do not break out of the run subloop */
                        loopControl = true;    /* allow the SM to enter running state again */
                    }
                    else
                    if(retVal == 2) /* no free buffers available, buffer overflowed */
                    {
                        Iterator_notifyHandler(iteratorInstance, ITERATOR_SM_TX_BUFFER_OVERFLOW);
                        Iterator_pause(iteratorInstance);

                        iteratorInstance.machineState = ITERATOR_SM_STATE_PAUSED;
                        subLoopControl = false; /* break out of the run subloop */
                        loopControl = true;    /* allow the SM to enter running state again */
                    }
                }
                else
                if(retVal == 1u) /* Pause requested */
                {
                    Iterator_pause(iteratorInstance);

                    iteratorInstance.machineState = ITERATOR_SM_STATE_PAUSED;
                    subLoopControl = false; /* break out of the run subloop */
                    loopControl    = true;  /* allow the SM to enter paused case */
                }
                else 
                if(retVal == 2u) /* Shutdown requested */
                {
                    Iterator_shutdown(iteratorInstance);

                    iteratorInstance.machineState = ITERATOR_SM_STATE_SHUTDOWN;
                    subLoopControl = false; /* break out of the run subloop */
                    loopControl = true;    /* allow the SM to enter shutdown state */
                }
                else
                {
                    ///PROPOSAL: create error handler function
                    iteratorInstance.machineState = ITERATOR_SM_STATE_SHUTDOWN;
                    subLoopControl = false; /* break out of the run subloop */
                    loopControl = true;     /* allow the SM to enter fault state */
                }
            break;

        case ITERATOR_SM_STATE_PAUSED:
            /* Check if the pause flag is still active */
            if(iteratorInstance.pauseFlag)
            {
                iteratorInstance.machineState = ITERATOR_SM_STATE_PAUSED; /* do not change the machine state */
                loopControl = false; /* break out of the run loop */
            }
            else
            {
                Iterator_resume(iteratorInstance);
                iteratorInstance.machineState = ITERATOR_SM_STATE_RUNNING;
                loopControl = true; /* do not break out of the run loop */
            }
            break;

        case ITERATOR_SM_STATE_FAULT: /* If sm is in a fault state, a reset function must be called */

            iteratorInstance.machineState = ITERATOR_SM_STATE_FAULT; /* do not change the machine state */
            loopControl = false; /* break out of the run loop */
            break;
        
        case ITERATOR_SM_STATE_SHUTDOWN: /* If sm is in a shutdown state, an init function must be called */

            iteratorInstance.machineState = ITERATOR_SM_STATE_SHUTDOWN;/* do not change the machine state */
            loopControl = false; /* break out of the run loop */
            break;
        
        default: /* Default case sends SM into fault state*/
            retVal = 1; ///TODO: add invalid machine state error code

            iteratorInstance.machineState = ITERATOR_SM_STATE_FAULT;
            loopControl = true; /* Allow sm to enter FAULT state */
            break;
        }
    }
    }
    return 0;
}
unsigned int IteratorSM_reset(IteratorSM_struct iteratorInstance);