#ifndef SECP251K1_SANDBOX_NETWORKMANAGER_PROTOCOLDATA_H
#define SECP251K1_SANDBOX_NETWORKMANAGER_PROTOCOLDATA_H

#define SM_RETRY_COUNT 3u

//// ClientSM protocol data

//ClientSM input messages
//ClientSM output messages
#define CLIENT_SM_REQUEST_HANDLER               "CSM_RequestHandler"
#define CLIENT_SM_REQUEST_REGISTERCHALLANGE     "CSM_RequestRegisterChallange"
#define CLIENT_SM_REQUEST_REGISTERPROGRESS      "CSM_RequestRegisterProgress"
#define CLIENT_SM_REQUEST_PROGRESSDATASPACE     "CSM_RequestProgressDataStorageSpace"

//// ClientHandlerSM protocol data

//ClientHandlerSM input messages
#define HANDLER_SM_RESPONSE_CONFIRMCONNECTION   "HSM_ConnectionEstablished"
#define HANDLER_SM_RESPONSE_CHALLANGEKEYS       "HSM_ChallangeKeys"
#define HANDLER_SM_RESPONSE_CHALLANGEOK         "HSM_ChallangePassed"

//ClientHandlerSM output messages
#define HANDLER_SM_REQUEST_REQUESTPROGRESS      "HSM_RequestProgressData"

/// Server API Commands
#define API_SERVERFRONTENDSM_GET_TARGETS                " "

/// Server API Responses
#define API_R_CONFIRM                           "ACTION_CONFIRMED"
#define API_R_PROGRESS_HASH_REQUESTED           "PROGRESS_HASH_REQUESTED"
#define API_R_INVALID_SOLUTION                  "CHALLANGE_SOLUTION_INVALID"
#define API_S_GET_ACTIVESEARCHES                "GET_ACTIVE"
#define API_S_POST_REGISTERPROGRESS             "POST_PROGRESS"
#define API_S_POST_REGISTERPROGRESS_SOLVED      "POST_PROGRESS_SOLVED"


#endif