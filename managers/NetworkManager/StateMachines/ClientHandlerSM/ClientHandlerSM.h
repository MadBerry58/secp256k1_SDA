#ifndef SECP251K1_SANDBOX_NETWORKMANAGER_CLIENTHANDLER_SM_H
#define SECP251K1_SANDBOX_NETWORKMANAGER_CLIENTHANDLER_SM_H

#include "../../../../TypeDef.h"

void init_ClientHandlerSM(clientHandlerSMStruct *messageStruct);

//ClientHandlerSM input messages
#define HANDLER_SM_RESPONSE_CONFIRMCONNECTION "HSM_ConnectionEstablished"
#define HANDLER_SM_RESPONSE_CHALLANGEKEYS "HSM_ChallangeKeys"
#define HANDLER_SM_RESPONSE_CHALLANGEOK "HSM_ChallangePassed"

//ClientHandlerSM output messages
#define HANDLER_SM_REQUEST_REQUESTPROGRESS "HSM_RequestProgressData"

//ClientHandlerSM states
enum ClientHandlerStates
{
    CLIENT_HANDLER_SM_UNINITIALIZED,
    CLIENT_HANDLER_SM_INIT,
    CLIENT_HANDLER_SM_WAITINGCONNECTION,
    CLIENT_HANDLER_SM_RECIVED_CONNECTIONREQUEST,
    CLIENT_HANDLER_SM_CONNECTED,
    CLIENT_HANDLER_SM_RECIVED_REGISTERPROGRESS_REQUEST,
    CLIENT_HANDLER_SM_REGISTERING_PROGRESS,
    CLIENT_HANDLER_SM_DISCONNECTED,
    CLIENT_HANDLER_SM_SHUTDOWN
};

#endif