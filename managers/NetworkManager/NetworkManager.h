#ifndef SECP251K1_SANDBOX_NETWORKMANAGER_H
#define SECP251K1_SANDBOX_NETWORKMANAGER_H

#include "ProtocolData/ProtocolData.h"
#include "StateMachines/StateMachines.h"

unsigned int init_NetworkManager(NetworkManagerData *networkManagerStruct);
unsigned int main_NetworkManager(NetworkManagerData *networkManagerStruct);
#endif // SECP251K1_SANDBOX_NETWORKMANAGER_H