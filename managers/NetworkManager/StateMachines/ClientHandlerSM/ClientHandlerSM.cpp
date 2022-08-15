#include "ClientHandlerSM.h"

unsigned int ClientHandlerSM(clientHandlerSMStruct *messageStruct)
{
    while(messageStruct->SMstate != CLIENT_HANDLER_SM_SHUTDOWN_REQUESTED)
        switch(messageStruct->SMstate)
        {
            case CLIENT_HANDLER_SM_UNINITIALIZED:
                messageStruct->SMstate = CLIENT_HANDLER_SM_INITIALIZING;
                ////initialize client handler
                //initialize data containers
                //confirm connection with the memory manager component
                messageStruct->SMstate = CLIENT_HANDLER_SM_INITIALIZED;
                ////confirm connection with client SM
                //
                break;
            case CLIENT_HANDLER_SM_INITIALIZED:


            default:
                break;
        }
    return 0;
}