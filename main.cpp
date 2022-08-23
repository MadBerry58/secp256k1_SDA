#include "TypeDef.h"
#include "Arithmetic/Arithmetic.h"
#include "managers/managers.h"

#define FLAG_OPERATION_NONE             0u
#define FLAG_OPERATION_CLIENT           1u
#define FLAG_OPERATION_SERVER           2u
#define FLAG_OPERATION_SATELLITE        3u
#define FLAG_OPERATION_TUNELOAD         4u

static int verbose_flag = false;
static int userInterface_flag = false;
static int operationType_flag = FLAG_OPERATION_NONE;
unsigned long errorNo;

std::ifstream checkpointFile;
std::ifstream knownPointsFile;

UISMStruct UIdata;

std::ifstream inputFile;

int main(int argc, char **argv)
{
    char optiune;
        if (argc < 1)
    { /* First argument is the file name */
        printf("Internal error, file name argument missing\n");
        exit(1);
    }

    static struct option long_options[] =
        {
            /* These options set a flag. */
            {"verbose",                 no_argument,        &verbose_flag,          1u       },
            {"brief",                   no_argument,        &verbose_flag,          0u       },
            {"UserInterface",           no_argument,        &userInterface_flag,    1u       },
            {"ClientMode",              no_argument,        &operationType_flag,    FLAG_OPERATION_CLIENT },
            {"ServerMode",              no_argument,        &operationType_flag,    FLAG_OPERATION_SERVER },
            {"SatelliteMode",           no_argument,        &operationType_flag,    FLAG_OPERATION_SATELLITE },
            {"tuneSystemLoad",          no_argument,        &operationType_flag,    FLAG_OPERATION_TUNELOAD },
            
            {"serverAdress",            required_argument,  0,                      's'},
            {"serverPort",              required_argument,  0,                      'p'},
            {"checkpointFile",          required_argument,  0,                      'c'},

            {"knownPointsFile",         required_argument,  0,                      'k'},

            {"help",                    optional_argument,  0,                      'h'},
            {0, 0, 0, 0}
        };

    int option_index = 0;

    while ((optiune = getopt_long(argc, argv, "c:s:h", long_options, &option_index)) != -1) // se analizeaza optiunile date de utilizator
    {

        switch (optiune)
        {
            case 0: //flag declaration
                if (long_options[option_index].flag != 0)
                {
                    gmp_printf("%s flag set \n", long_options[option_index].name);
                }
                if (optarg)
                {
                    gmp_printf(" with arg %s \n", optarg);
                }
                break;
            
            /* afiseaza descrierea programului */
            case 'h': 
                std::cout << "\n"
                          << "Secp256k1-SDA - SECP256k1 elliptic curve smooth distribution attacker\n"
                          << "This program is a proof of concept for a distributed heuristic bruteforce crowd sourced attack, targeting elliptic curve based key pairs\n"
                          << "Implementation details can be found in the project documentation\n"
                          << "The program can run in 3 different modes:\n"
                          << "Server Mode - host a central database of known keys to compare client generated data against\n"
                          << "Client Mode - calculate public keys derived from the target public key, and send the results to the central server\n"
                          << "TBD: Satellite Mode - host an additional database of known keys to suppliment the central server known search space\n"
                          << "\n";
                return 0u;

            /* Server Mode operation arguments */
            case 'k':
            if(optarg)
                {
                    UIdata.knownPointsFileName = optarg;
                }
                break;
            

            /* Client Mode operation arguments */
            case 'c':
                if(optarg)
                {
                    UIdata.checkpointFileName = optarg;
                }
                break;

            case 's':
                if(optarg)
                {
                    UIdata.serverAdress = optarg;
                }
                break;
            
            case 'p':
                if(optarg)
                {
                    UIdata.serverPort = optarg;
                }

            case '?': /* getopt returneaza '?' cand optiunea nu este cunoscuta */
                printf("Argumentul %s este eronat\n", (char *)(&optiune));
                exit(EXIT_FAILURE);
            }
    }

    switch(operationType_flag)
    {
        case FLAG_OPERATION_NONE:
            // gmp_printf("Please choose the desired operating mode: \n./secp256k1_SDA --userInterface | resumeIteration | generateKnownPoints | tuneSystemLoad\n");
            
            break;

        case FLAG_OPERATION_CLIENT:
            /* Check for local checkpoint file */
            if(UIdata.checkpointFileName.empty())
            {
                //notify the user if a new checkpoint file is desired, or if the program should look for a checkpoint file locally
                std::cout << "A checkpoint file is required for ClientMode operation.\n"
                          << "Should I create a new checkpoint file (c) or search locally for one? (s)\n";
                std::cin  >>  UIdata.user_input;
                if('c' == UIdata.user_input)
                {
                    //Mark the file name for later creation by the fileManager
                }
                else if('s' == UIdata.user_input)
                {
                    //Search local folder for *.checkpoint file and assign it to checkpointFileName
                }
                else
                {
                    std::cout << "Unknown option selected. Exiting program\n";
                    exit(1);
                }
            }
            else
            {
                //check if the provided file exists
                    //if not, ask the user if the creation of a new checkpoint file with the provided name is desired
                    //if yes, check the file integrity
                        //if yes, confirm checkpoint file loading
                        //if not, try recovering the file data or notify user of file corruption
            }

            /* Check for server connection */
            if(UIdata.serverAdress.empty())
            {
                //output fatal error: a hostname must be provided
            }
            else
            {
                //check if the provided hostname is valid
                    //if not, output fatal error: host name invalid
                    //if yes:
                if(UIdata.serverPort.empty())
                {
                    //output fatal error: a port must be provided
                }
                else
                {
                    //check if the provided port is valid
                    //if not, output fatal error: port invalid
                    //if yes:
                        //attempt connectinon to host (ping and/or UDP message to the Frontend)
                            //if successful: start clientSM and request a clientHandlerSM
                            //else: output fatal error: host not responding
                }
            }
            break;
        case FLAG_OPERATION_SERVER:
            /* Check for known points file */
            if(UIdata.knownPointsFileName.empty())
            {
                //notify the user if a known points file is desired, or if the program should look for a file locally
            }
            else
            {
                //check if the provided file exists
                    //if not, ask the user if the creation of a new known points file with the provided name is desired
                    //if yes, check the file integrity
                        //if yes, confirm known points file loading
                        //if not, try recovering the file data or notify user of file corruption
            }
            break;

        case FLAG_OPERATION_SATELLITE:
            /* Check for known points file */
            if(UIdata.knownPointsFileName.empty())
            {
                //notify the user if a known points file is desired, or if the program should look for a file locally
            }
            else
            {
                //check if the provided file exists
                    //if not, ask the user if the creation of a new known points file with the provided name is desired
                    //if yes, check the file integrity
                        //if yes, confirm known points file loading
                        //if not, try recovering the file data or notify user of file corruption
            }

            /* Check for server connection */
            if(UIdata.serverAdress.empty())
            {
                //output fatal error: a hostname must be provided
            }
            else
            {
                //check if the provided hostname is valid
                    //if not, output fatal error: host name invalid
                    //if yes:
                if(UIdata.serverPort.empty())
                {
                    //output fatal error: a port must be provided
                }
                else
                {
                    //check if the provided port is valid
                    //if not, output fatal error: port invalid
                    //if yes:
                        //attempt connectinon to host (ping and/or UDP message to the Frontend)
                            //if successful: start clientSM and request a clientHandlerSM
                            //else: output fatal error: host not responding
                }
            }
            break;

        case FLAG_OPERATION_TUNELOAD:
            break;
        default:
            break;
    }
    return 0;
}