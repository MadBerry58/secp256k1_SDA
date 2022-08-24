#include "../TypeDef.h"
#ifndef SECP251K1_SANDBOX_PORTS_H
#define SECP251K1_SANDBOX_PORTS_H

unsigned int initPort    (Port* Port,   unsigned int bufferSize);
unsigned int sendMessage (Port* TxPort, unsigned int message, unsigned long long messageData);
unsigned int readMessage (Port* RxPort, unsigned int *message, unsigned long long *messageData);

#endif /*SECP251K1_SANDBOX_PORTS_H*/