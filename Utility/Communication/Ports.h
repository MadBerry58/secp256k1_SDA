#ifndef PORTS_H
#define PORTS_H

#include "Ports_Types.h"

unsigned int initPort    (Port &portInstance, unsigned int bufferSize);
unsigned int sendMessage (Port &TxPort, unsigned long long  message, unsigned long long  messageData);
unsigned int readMessage (Port &RxPort, unsigned long long *message, unsigned long long *messageData, unsigned int match);

#endif