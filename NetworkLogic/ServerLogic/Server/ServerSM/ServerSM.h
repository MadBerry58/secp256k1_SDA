#ifndef SERVER_SM_H
#define SERVER_SM_H

#include "../Server.h"

unsigned int ServerSM_init (ServerSM_struct &serverInstance);
unsigned int ServerSM_run  (ServerSM_struct &serverInstance);
unsigned int ServerSM_reset(ServerSM_struct &serverInstance);

#endif