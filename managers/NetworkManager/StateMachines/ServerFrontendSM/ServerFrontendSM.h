#ifndef SECP251K1_SANDBOX_NETWORKMANAGER_FRONTEND_SM_H
#define SECP251K1_SANDBOX_NETWORKMANAGER_FRONTEND_SM_H

#include "../../../../TypeDef.h"

void init_ServerFrontendSM(serverSMStruct *messageStruct);

//ServerFrontendSM input messages
enum HostSMCommands
{
    HOST_SM_OK,
    HOST_SM_RESTART_REINIT,
    HOST_SM_RESTART_NOINIT,
    HOST_SM_SHUTDOWN
};

//ServerFrontendSM output messages
enum ServerSMRequestTypes
{
    SERVER_UNINITIALIZED,
    SERVER_CLIENT_CONNECTION_INIT,
    SERVER_CHECK_REQUESTBUFFER,
    SERVER_SET_CLIENT_RANGE,
    SERVER_SET_CLIENT_CHECK,
    SERVER_MATCH_CLIENT_FOUND_RESULT
};

//ServerFrontendSM states
enum ServerSMFrontendStates
{
    SERVER_FRONTEND_UNITIALIZED,
    SERVER_FRONTEND_INIT,
    SERVER_FRONTEND_CHECK_REQUESTBUFFER,
    SERVER_FRONTEND_CLIENT_CONNECTION_REQUESTED
};

/// Server API Commands
#define API_SERVERFRONTENDSM_GET_TARGETS                " "

/// Server API Responses
#define API_R_CONFIRM                                   "ACTION_CONFIRMED"
#define API_R_PROGRESS_HASH_REQUESTED                   "PROGRESS_HASH_REQUESTED"
#define API_R_INVALID_SOLUTION                          "CHALLANGE_SOLUTION_INVALID"
#define API_S_GET_ACTIVESEARCHES                        "GET_ACTIVE"
#define API_S_POST_REGISTERPROGRESS                     "POST_PROGRESS"
#define API_S_POST_REGISTERPROGRESS_SOLVED              "POST_PROGRESS_SOLVED"

#endif