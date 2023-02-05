#include "CommandLine.h"

#include <getopt.h>
#include <stdint.h>
#include <fstream>

#define NOT_PROVIDED false
#define PROVIDED     true

static int  argument;
static int  argument_index = 0;
static int  verbose_flag = false;
static int  operationType_flag = 0;
static int  userInterface_flag = 0;
static bool newCheckpointFile = false;
static bool newKnownPointsFile = false;
static int  newKnownPointsFileSize = 0u;
static int  workerNumber = 0u;
static int  memorySize = 0u;

static struct option long_options[] =
{ /* Program Arguments */
    /* These options set a flag. */
  {"verbose",                 no_argument,        &verbose_flag,          1u       },
  {"brief",                   no_argument,        &verbose_flag,          0u       },
  {"UserInterface",           no_argument,        &userInterface_flag,    1u       },
  {"ClientMode",              no_argument,        &operationType_flag,    FLAG_OPERATION_CLIENT },
  {"ServerMode",              no_argument,        &operationType_flag,    FLAG_OPERATION_SERVER },
  {"SatelliteMode",           no_argument,        &operationType_flag,    FLAG_OPERATION_SATELLITE },
  {"tuneSystemLoad",          no_argument,        &operationType_flag,    FLAG_OPERATION_TUNELOAD },
  
  {"allocatedMemory",         required_argument,  0,                      'm'},

  {"serverAdress",            required_argument,  0,                      's'},
  {"serverPort",              required_argument,  0,                      'p'},
  {"checkpointFile",          required_argument,  0,                      'c'},
  {"workerNumber",            required_argument,  0,                      'w'},
  {"newCheckpointFile",       no_argument,        0,                      'n'},

  {"knownPointsFile",         required_argument,  0,                      'k'},
  {"generatePointsFile",      required_argument,  0,                      'g'},

  {"help",                    optional_argument,  0,                      'h'},
  {0, 0, 0, 0}
};

static struct providedData
{
  bool serverAdress           = NOT_PROVIDED;
  bool serverPort             = NOT_PROVIDED;
  bool checkPointFile         = NOT_PROVIDED;
  bool newCheckPointFileFlag  = NOT_PROVIDED;
  bool knownPointsFile        = NOT_PROVIDED;
  bool newKnownPointsFileSize = NOT_PROVIDED;
  bool workerNumber           = NOT_PROVIDED;
  bool memorySize             = NOT_PROVIDED;
} providedArgumentData;

uint64_t parseArguments(int argc, char **argv, std::string &returnMessage, InitDataStruct &initData)
{
  uint64_t retVal = 0u;
  if(argc < 1)
  { /* First argument is the file name */
    printf("Internal error, file name argument missing\n");
    retVal = 0xFFFF;
  }
  else
  {
    /* Parse the available arguments */
    while ((argument = getopt_long(argc, argv, "m:w:p:c:s:k:ngh", long_options, &argument_index)) != -1) // se analizeaza optiunile date de utilizator
    {
      switch (argument)
      {
        case 0: {//flag declaration
          if (long_options[argument_index].flag != 0)
          {
              printf("%s flag set\n", long_options[argument_index].name);
          }  
          if (optarg)
          {
              printf(" with arg %s \n", optarg);
          }
          break;}

        case 'h': {/* Print the program description */
          printf ("\n \
          Secp256k1-SDA - SECP256k1 elliptic curve smooth distribution attacker\n \
          This program is a proof of concept for a distributed heuristic bruteforce crowd sourced attack, targeting elliptic curve based key pairs\n \
          Implementation details can be found in the project documentation\n \
          The program can run in 3 different modes:\n \
          Server Mode - host a central database of known keys to compare client generated data against\n \
          Client Mode - calculate public keys derived from the target public key, and send the results to the central server\n \
          TBD: Satellite Mode - host an additional database of known keys to suppliment the central server known search space\n");

          return 0u; 
          }
        
        case 'k': {/* Known points file name argument */
          if(optarg)
          {
            initData.knownPointsFileName = optarg;
            providedArgumentData.knownPointsFile = true;
          }
          break;
        }

        case 'm': {/* Memory size allocated for worker buffers or point containment */
          if(optarg)
          {
            initData.memorySize = atoi(optarg);
            providedArgumentData.memorySize = PROVIDED;
          }
          else
          {
            printf("No memory size provided for program operation\n");
            return -1;
          }
          break;
        }
        
        case 'g': {/* New known points file argument */
          if(optarg)
          {
            newKnownPointsFileSize = atoi(optarg);
            providedArgumentData.newKnownPointsFileSize = PROVIDED;
          }
          else
          {
            printf("No size provided for the new known points file\n");
            return -1;
          }
          break;}
                        
        case 'w': {/* Worker number argument */
          if(optarg)
          {
            workerNumber = atoi(optarg);
            providedArgumentData.workerNumber = PROVIDED;
            initData.workersPerCoordinator = workerNumber;
            printf("Instance worker number: 4\n");
          }
          else
          {
            printf("No worker number provided\n");
            return -1;
          }
          break;}

        case 'c': {/* Checkpoint file name argument */
          if(optarg)
          {
            initData.checkpointFileName = optarg;
            providedArgumentData.checkPointFile = true;
          }
          break;}
        
        case 'n': {/* New checkpoint file argument */
            providedArgumentData.newCheckPointFileFlag = true;
          break;}

        case 's': {/* Server adress argument */
          if(optarg)
          {
            initData.serverAdress = optarg;
            providedArgumentData.serverAdress = true;
          }
          break;}

        case 'p': {/* Server Port argument */
          if(optarg)
          {
            initData.serverPort = optarg;
            providedArgumentData.serverPort = true;
          }  
          break;}

        case '?': {/* Option unknown */
          printf("Argument %s is unknown\n", (char *)(&argument));
          break;}

        default:  {/* Invalid program state */
          printf("Invalid program state");
          return -1;}
      }
    }  

    /* Check if the given arguments match the desired flag */
    initData.instanceType = (InstanceType)operationType_flag;

    switch(initData.instanceType)
    {
      case FLAG_OPERATION_NOOP:
          printf("No instance mode selected, defaulting to UI mode\n");
          userInterface_flag = 1u;
          break;

      case FLAG_OPERATION_CLIENT: { /* Instance starting as client */
        /* Check if a checkpoint file is provided */
        if(NOT_PROVIDED == providedArgumentData.checkPointFile)
        {
          /* Check if a new checkpoint file is flagged for creation */
          if(providedArgumentData.newCheckPointFileFlag)
          {
            initData.newCheckPointFile = true;
          }
          else
          {
            printf("No checkpoint file provided\n");
            ///TODO: add return code
          }
        }
        break;}

      case FLAG_OPERATION_SERVER:
          ///TODO: check for knownPointsFile
          break;
    }
  }
  return retVal;
}