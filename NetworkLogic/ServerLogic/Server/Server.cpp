#include "Server.h"

#include "ServerSM/ServerSM.h"
#include <stdio.h>
ServerSM_struct serverStateMachineInstance;
unsigned int Server_init()
{
    printf("Server initializing\n");
    ServerSM_init(serverStateMachineInstance);
    return 0u;
}