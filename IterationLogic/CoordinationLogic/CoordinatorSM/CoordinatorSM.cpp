#include "CoordinatorSM.h"

bool loopControl = false;
bool subLoopControl = false;

///QUESTION: should errors be returned as a flag inside the SM struct or as a return?

#define PLACEHOLDER_OK 0
#define PLACEHOLDER_ERROR 1
#define PLACEHOLDER_INITIAL_UNDEFINED 2

unsigned int CoordinatorSM_init(CoordinatorSM_struct coordinatorInstance)
{
    unsigned int retVal = PLACEHOLDER_INITIAL_UNDEFINED; ///TODO: Add proper definitions
    ///TODO: add error codes

    if( /* Check for the SM to be in the correct state */
        (COORDINATOR_SM_STATE_UNINITIALIZED == coordinatorInstance.machineState) &&
        (COORDINATOR_SM_STATE_SHUTDOWN      == coordinatorInstance.machineState)
      )
    {
        if(retVal = Coordinator_init_sm(coordinatorInstance))
        {    /* If any error occurs while initializing the components change machine state to fault */
            coordinatorInstance.machineState = COORDINATOR_SM_STATE_FAULT;
        }
        else
        {   /* Change machine state to ready */

            if(retVal = Coordinator_initWorkers(coordinatorInstance)){
                coordinatorInstance.machineState = COORDINATOR_SM_STATE_FAULT;
            }
            else
            {
                coordinatorInstance.machineState = COORDINATOR_SM_STATE_READY;
                retVal = PLACEHOLDER_OK;
            }
        }
    }
    else
    {
        retVal = PLACEHOLDER_ERROR;
    }

    return retVal;
}

unsigned int CoordinatorSM_run(CoordinatorSM_struct coordinatorInstance)
{
    unsigned int retVal = 0;
    loopControl = true;
    while(loopControl)
    {
        switch (coordinatorInstance.machineState)
        {
        case COORDINATOR_SM_STATE_UNINITIALIZED: /* If sm is in a uninitialized state, an init function must be called */
            retVal = 1; ///TODO: add error code

            coordinatorInstance.machineState = COORDINATOR_SM_STATE_UNINITIALIZED; /* do not change the machine state */
            loopControl = false; /* break out of the run loop */
            break;

        case COORDINATOR_SM_STATE_READY:
            /* Start the associated workers */
            Coordinator_startWorkers(coordinatorInstance);

            coordinatorInstance.machineState = COORDINATOR_SM_STATE_RUNNING;
            loopControl = true; /* do not break out of the run loop */
            break;
        
        case COORDINATOR_SM_STATE_RUNNING: 
            /* Check for events */

            /* Enter subloop */
            subLoopControl = true;
            while(subLoopControl)
            {
                ///TODO: add proper definitions
                retVal = Coordinator_checkForEvents(coordinatorInstance);
                if(retVal == 0u) /* Regular event handled */
                {
                    
                    coordinatorInstance.machineState = COORDINATOR_SM_STATE_RUNNING;
                    subLoopControl = true; /* do not break out of the run subloop */
                    loopControl = true;    /* allow the SM to enter running state again */
                }
                else 
                if(retVal == 1u) /* Pause requested */
                {
                    Coordinator_pauseWorkers(coordinatorInstance);
                    Coordinator_pause       (coordinatorInstance);

                    coordinatorInstance.machineState = COORDINATOR_SM_STATE_PAUSED;
                    subLoopControl = false; /* break out of the run subloop */
                    loopControl    = true;  /* allow the SM to enter paused case */
                }
                else 
                if(retVal == 2u) /* Shutdown requested */
                {
                    Coordinator_stopWorkers (coordinatorInstance);
                    Coordinator_shutdown    (coordinatorInstance);

                    coordinatorInstance.machineState = COORDINATOR_SM_STATE_SHUTDOWN;
                    subLoopControl = false; /* break out of the run subloop */
                    loopControl = true;    /* allow the SM to enter shutdown state */
                }
                else
                {
                    ///TODO: decide what happens to the workers when SM enters fault state
                    ///PROPOSAL: create error handler function
                    coordinatorInstance.machineState = COORDINATOR_SM_STATE_FAULT;
                    subLoopControl = false; /* break out of the run subloop */
                    loopControl = true;     /* allow the SM to enter fault state */
                }
            }
            break;
            
        case COORDINATOR_SM_STATE_PAUSED:
            /* Check if the pause flag is still true */
            if(coordinatorInstance.pauseFlag)
            {
                coordinatorInstance.machineState = COORDINATOR_SM_STATE_PAUSED; /* do not change the machine state */
                loopControl = false; /* break out of the run loop */
            }
            else
            {
                Coordinator_resume(coordinatorInstance);
                coordinatorInstance.machineState = COORDINATOR_SM_STATE_RUNNING;
                loopControl = true;
            }
            break;
        
        case COORDINATOR_SM_STATE_FAULT: /* If sm is in a fault state, a reset function must be called */

            coordinatorInstance.machineState = COORDINATOR_SM_STATE_FAULT; /* do not change the machine state */
            loopControl = false; /* break out of the run loop */
            break;
        
        case COORDINATOR_SM_STATE_SHUTDOWN: /* If sm is in a shutdown state, an init function must be called */

            coordinatorInstance.machineState = COORDINATOR_SM_STATE_SHUTDOWN;/* do not change the machine state */
            loopControl = false; /* break out of the run loop */
            break;
        
        default: /* Default case sends SM into fault state*/
            retVal = 1; ///TODO: add invalid machine state error code

            coordinatorInstance.machineState = COORDINATOR_SM_STATE_FAULT;
            loopControl = true; /* Allow sm to enter FAULT state */
            break;
        }
    }
    return 0;
}

unsigned int CoordinatorSM_reset(CoordinatorSM_struct coordinatorInstance)
{
    if( /* Check for the SM to be in the correct state */
        (COORDINATOR_SM_STATE_UNINITIALIZED == coordinatorInstance.machineState) &&
        (COORDINATOR_SM_STATE_SHUTDOWN      == coordinatorInstance.machineState)
      )
    ///TODO: delete all data from the SM struct
    ///TODO: stop and reset all child workers
    coordinatorInstance.machineState = COORDINATOR_SM_STATE_UNINITIALIZED;
    return 0;
}