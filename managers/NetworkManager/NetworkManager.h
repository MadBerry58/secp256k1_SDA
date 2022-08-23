#ifndef SECP251K1_SANDBOX_NETWORKMANAGER_H
#define SECP251K1_SANDBOX_NETWORKMANAGER_H

#include "ProtocolData/ProtocolData.h"
#include "StateMachines/StateMachines.h"

unsigned int init_NetworkManager(std::string message);
unsigned int main_NetworkManager();
#endif // SECP251K1_SANDBOX_NETWORKMANAGER_H