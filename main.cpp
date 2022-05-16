#include "managers/tests/functionalityTest.h"
#include "managers/headers/fileManager.h"
#include "managers/headers/UIManager.h"
#include <getopt.h>

#define FLAG_OPERATION_UI 0
#define FLAG_OPERATION_RESUME 1
#define FLAG_OPERATION_GENERATEPOINTS 2
#define FLAG_OPERATION_TUNELOAD 3

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
            {"verbose",                 no_argument,        &verbose_flag,           1       },
            {"brief",                   no_argument,        &verbose_flag,           0       },
            {"userInterface",           no_argument,        &operation_flag,         FLAG_OPERATION_UI },
            {"resumeIteration",         no_argument,        &operation_flag,         FLAG_OPERATION_RESUME },
            {"generateKnownPoints",     no_argument,        &operation_flag,         FLAG_OPERATION_GENERATEPOINTS },
            {"tuneSystemLoad",          no_argument,        &operation_flag,         FLAG_OPERATION_TUNELOAD },
            
            {"checkpointFile",          required_argument,  0,                      'c'},
            {"serverAdress",            required_argument,  0,                      's'},
            {"knownPointsFile",         required_argument,  0,                      'k'},
            {"loadProfileFile",         required_argument,  0,                      'f'},

            {"help",                    optional_argument,  0,                      'h'},
            {0, 0, 0, 0}
        };

    int option_index = 0;

    while ((optiune = getopt_long(argc, argv, "c:s:k:f:", long_options, &option_index)) != -1) // se analizeaza optiunile date de utilizator
    {

        switch (optiune)
        {
            case 0:
                if (long_options[option_index].flag != 0)
                {
                    DEBUG_MSG("Flag %s set", long_options[option_index].name)
                }

            case 'h': // afiseaza descrierea programului
                printf("Secp256k1-SDA - Run a token through a chain of processes, returning their process IDs\n\n Arguments: \n-t --threads=THREAD_NO\n     specify number of threads used\n-m --message=MESSAGE\n      specify the message being sent\n-d --debug\n    run with debug prompts\n");
                return 0u;

            case 'c':
                if(optarg)
                {
                    inputFile.open(optarg);
                    if(inputFile.is_open())
                    {
                        /// check file integrity
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

            case '?': // getopt returneaza '?' cand optiunea nu este cunoscuta
                printf("Argumentul %s este eronat", (char *)(&optiune));
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

    if (operation_flag == FLAG_OPERATION_UI)
    {
        userInterface_Init();
        userInterface_Start();
    }


    return 0;
}