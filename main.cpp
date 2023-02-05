#include "Arithmetic/Arithmetic.h"
#include "Utility/Utility.h"
#include "InstanceManager/InstanceManager.h"

int main(int argc, char **argv)
{
  unsigned int retVal = 0;
  unsigned int inputData;
  printf("Hello World!\n");
  Arithmetic_Init();

  InitDataStruct initialProgramData;
  std::string textResponseString;

  parseArguments(argc, argv, textResponseString, initialProgramData);

  switch(initialProgramData.instanceType)
  {
    case FLAG_OPERATION_NOOP:
    break;

    case FLAG_OPERATION_CLIENT:
    createClientInstance(initialProgramData.workersPerCoordinator, initialProgramData.memorySize);
    break;

    case FLAG_OPERATION_SERVER:
    createServerInstance(inputData);
    break;

    case FLAG_OPERATION_SATELLITE:
    createSatelliteInstance(inputData);
    break;

    case FLAG_OPERATION_TUNELOAD:
    ///TODO: create load tuning routine
    break;

    default:
    break;

  }

    return retVal;
}
