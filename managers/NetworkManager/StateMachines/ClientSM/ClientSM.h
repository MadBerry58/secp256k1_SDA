#ifndef SECP251K1_SANDBOX_NETWORKMANAGER_CLIENT_SM_H
#define SECP251K1_SANDBOX_NETWORKMANAGER_CLIENT_SM_H

#include "../../../../TypeDef.h"

unsigned int init_ClientSM(clientSMStruct *message);
unsigned int ClientSM(clientSMStruct *message);

#endif