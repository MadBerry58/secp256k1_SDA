#include "ServerSM.h"

#include <stdio.h>

unsigned int ServerSM_init (ServerSM_struct &serverInstance)
{
    printf("ServerSM initialized\n");
    return 0u;
}

unsigned int ServerSM_run  (ServerSM_struct &serverInstance);
unsigned int ServerSM_reset(ServerSM_struct &serverInstance);