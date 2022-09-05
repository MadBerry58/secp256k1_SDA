#ifndef SECP251K1_SANDBOX_PORTS_H
#define SECP251K1_SANDBOX_PORTS_H
#include "../TypeDef.h"

unsigned int initPort    (Port* Port,   unsigned int bufferSize);
unsigned int sendMessage (Port* TxPort, unsigned long long  message, unsigned long long  messageData);
unsigned int readMessage (Port* RxPort, unsigned long long *message, unsigned long long *messageData, unsigned int match);

#endif /*SECP251K1_SANDBOX_PORTS_H*/