#include "Client_Instance.h"

#include <stdio.h>
#include "../../IterationLogic/CoordinationLogic/Coordinator.h"
#include "../../NetworkLogic/ClientLogic/Client/Client.h"


/* Private definitions */
static unsigned int inputData;
CoordinatorSM_struct coordinatorInstance;

/* Public functions */
unsigned int Client_Instance_Init(ClientInstance_struct inputData)
{
    printf("Client Instance selected. Initializing components...\n");

    Client_init_sm();

    coordinatorInstance.workerNumber = inputData.workers;
    coordinatorInstance.workerBufferSize = inputData.workerBufferSize / inputData.workers;
    Coordinator_init_sm(coordinatorInstance);
    Coordinator_initWorkers(coordinatorInstance);

    return 0;
}

