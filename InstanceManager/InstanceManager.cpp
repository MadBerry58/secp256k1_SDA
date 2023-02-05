#include "InstanceManager.h"

#include "Client_Instance/Client_Instance.h"
#include "Satellite_Instance/Satellite_Instance.h"
#include "Server_Instance/Server_Instance.h"


unsigned int createClientInstance   (unsigned int workerNumber, unsigned int workerBufferSize)
{
    ClientInstance_struct clientInstance;
    clientInstance.workers = workerNumber;
    clientInstance.workerBufferSize = workerBufferSize;

    Client_Instance_Init(clientInstance);
    
    return 0;
}

unsigned int createServerInstance(unsigned int inputData)
{
    Server_Instance_Init(inputData);
    return 0;

}

unsigned int createSatelliteInstance(unsigned int inputData)
{
    return 0;
}