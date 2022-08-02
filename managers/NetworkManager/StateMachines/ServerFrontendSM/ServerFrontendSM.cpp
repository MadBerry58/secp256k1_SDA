#include "ServerFrontendSM.h"

///// PURPLE CIRCLE /////

void init_ServerFrontendSM(serverSMStruct *messageStruct)
{
    
}

void mainLogic()
{   
    ServerSMFrontendStates serverFrontendState = SERVER_FRONTEND_UNITIALIZED;
    int messageBuffer;

    for( ;; )
    {
        switch (serverFrontendState)
        {
            case SERVER_FRONTEND_INIT:
                // init_requestListener();
                //check received message for the proper request structure

                break;

            case SERVER_FRONTEND_CHECK_REQUESTBUFFER:
                // if(checkRequestBuffer())
                // {
                //     // pop buffer message
                //     // check request validity
                //     // if request valid
                //         serverFrontendState = SERVER_FRONTEND_CLIENT_CONNECTION_REQUESTED;
                //     // else
                        
                // }

                break;

            case SERVER_FRONTEND_CLIENT_CONNECTION_REQUESTED:
                // build request structure
                // copy structure to main process buffer
                // noitify main process of new client
                
                // ret = handle_ConnectionRequest();
                // // initialize handlerSM

                // messageBuffer = connect_Client();
                // give clientFrontend the handler description (socket + accessToken)

                //disconnectClient
                ///TODO: implement security checks against overflow attacks

                break;

            default:
                if(SERVER_FRONTEND_UNITIALIZED == serverFrontendState)
                {
                    // Go into INTO state
                    serverFrontendState = SERVER_FRONTEND_INIT;
                }
                else
                {
                    // We treat this case as an error
                }
                break;
        }
    }
    

    // return OK;
}