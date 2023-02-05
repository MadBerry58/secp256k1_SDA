#ifndef INSTANCE_MANAGER_H
#define INSTANCE_MANAGER_H

unsigned int createClientInstance   (unsigned int workerNumber, unsigned int workerBufferSize);
unsigned int createServerInstance   (unsigned int inputData);
unsigned int createSatelliteInstance(unsigned int inputData);

#endif