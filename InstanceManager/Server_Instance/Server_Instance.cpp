#include "Server_Instance.h"

#include <stdio.h>

#include "../../NetworkLogic/ServerLogic/Server/Server.h"
#include "../../NetworkLogic/ServerLogic/Frontend/Frontend.h"

/* Private definitions */
static unsigned int inputData;

/* Public functions */
unsigned int Server_Instance_Init(unsigned int inputData)
{
    printf("Server Instance selected. Initializing components...\n");

    Server_init();

    Frontent_init();

    return 0;
}

