#include "TypeDef.h"
#include "Arithmetic/Arithmetic.h"
#include "managers/managers.h"

#define FLAG_OPERATION_NONE             0u
#define FLAG_OPERATION_UI               1u
#define FLAG_OPERATION_RESUME           2u
#define FLAG_OPERATION_GENERATEPOINTS   3u
#define FLAG_OPERATION_TUNELOAD         4u

static int verbose_flag = false;
static int operation_flag = 0u;

std::ifstream inputFile;

int main(int argc, char **argv)
{
    char optiune;
        if (argc < 1)
    { // First argument is the file name
        printf("Internal error, file name argument missing\n");
        exit(1);
    }

    static struct option long_options[] =
        {
            /* These options set a flag. */
            {"verbose",                 no_argument,        &verbose_flag,          1       },
            {"brief",                   no_argument,        &verbose_flag,          0       },
            {"userInterface",           no_argument,        &operation_flag,        FLAG_OPERATION_UI },
            {"resumeIteration",         no_argument,        &operation_flag,        FLAG_OPERATION_RESUME },
            {"generateKnownPoints",     no_argument,        &operation_flag,        FLAG_OPERATION_GENERATEPOINTS },
            {"tuneSystemLoad",          no_argument,        &operation_flag,        FLAG_OPERATION_TUNELOAD },
            
            {"checkpointFile",          required_argument,  0,                      'c'},
            {"serverAdress",            required_argument,  0,                      's'},
            {"serverPort",              required_argument,  0,                      'p'},
            {"knownPointsFile",         required_argument,  0,                      'k'},

            {"help",                    optional_argument,  0,                      'h'},
            {0, 0, 0, 0}
        };

    int option_index = 0;

    while ((optiune = getopt_long(argc, argv, "c:s:h", long_options, &option_index)) != -1) // se analizeaza optiunile date de utilizator
    {

        switch (optiune)
        {
            case 0:
                if (long_options[option_index].flag != 0)
                {
                    gmp_printf("%s flag set \n", long_options[option_index].name);
                }
                if (optarg)
                {
                    gmp_printf(" with arg %s \n", optarg);
                }
                break;
                
            case 'h': // afiseaza descrierea programului
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

            /*Server Mode operation arguments*/
            case 'c':
                if(optarg)
                {
                    inputFile.open(optarg);
                    if(inputFile.is_open())
                    {
                        ///TODO: check file integrity
                    }
                    else
                    {
                        printf("Could not open specified checkpoint file\n");
                    }
                }
                else
                {
                    printf("Checkpoint file location must be provided\n");
                }
                break;
            
            case 's':
                if(optarg)
                {
                    ///TODO: check for server adress
                }
                else
                {
                    std::cout << "The server adress must be provided\n";
                }
                break;
            case 'p':
                if(optarg)
                {
                    ///TODO: check for server port
                }
                else
                {
                    std::cout << "The server adress must be provided\n";
                }
                break;

            /*Server Mode operation arguments*/
            case 'k':
            if(optarg)
                {
                    inputFile.open(optarg);
                    if(inputFile.is_open())
                    {
                        ///TODO: check file integrity                                                                                                                                           
                    }
                    else
                    {
                        printf("Could not open specified known_points file\n");
                    }
                }
                else
                {
                    std::cout << "Checkpoint file location must be provided\n";
                }
                break;
            case '?': // getopt returneaza '?' cand optiunea nu este cunoscuta
                printf("Argumentul %s este eronat\n", (char *)(&optiune));
                exit(EXIT_FAILURE);
            }
    }

    long unsigned int errorNo = -1;
    if ((errorNo = modInit()) != MOD_E_OK)
    {
        printf("modInit failed with code %lu\n", errorNo);
    }

    if ((errorNo = pointInit()) != POINT_E_OK)
    {
        printf("pointInit failed with code %lu\n", errorNo);
    }

    if ((errorNo = fileManager_Init()) != INTEGRITY_E_FILE_INIT_OK)
    {
        printf("fileManagerInit failed with code %lu\n", errorNo);
    }

    switch(operation_flag)
    {
        case FLAG_OPERATION_NONE:
            gmp_printf("Please choose the desired operating mode: \n./secp256k1_SDA --userInterface | resumeIteration | generateKnownPoints | tuneSystemLoad\n");
            break;
        case FLAG_OPERATION_UI:
            userInterface_Init();
            userInterface_Start();
            break;
        case FLAG_OPERATION_RESUME:
            /* Check for local checkpoint file */

            break;
        case FLAG_OPERATION_GENERATEPOINTS:
            /* Check for  */
            break;
        case FLAG_OPERATION_TUNELOAD:
            break;
        default:
            break;
    }
    return 0;
}