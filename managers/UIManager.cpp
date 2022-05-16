#include "headers/UIManager.h"

int userInterface_Init()
{
    std::cout << "Initialize user interface\n"
              << UNIMPLEMENTED_FUNCTIONALITY_TAG << "\n";
    return 0;
}

int userInterface_Start()
{
    while (user_input != 'x')
    {
        std::cout << "\n\nPlease select an option: \n(G)enerate cardinal LSB file\n(L)oad cardinal point file\n(N)ew point search\n(R)esume point search\n(I)terate\nE(x)it program\n\n";
        std::cin >> user_input;

        switch (user_input)
        {
        case 'G': //////Generate cardinal points
            // TODO: Generate points function
            std::cout << "Generate known points file\n"
                      << UNIMPLEMENTED_FUNCTIONALITY_TAG << "\n";
            break;

        case 'L': /////Load cardinal points
            // TODO: Load points function
            std::cout << "Load known points file\n"
                      << UNIMPLEMENTED_FUNCTIONALITY_TAG << "\n";
            break;

        case 'R': /////Resume search
            /// TODO: Resume search/ Load resume file
            std::cout << "Resume search\n"
                      << UNIMPLEMENTED_FUNCTIONALITY_TAG << "\n";
            break;

        case 'N': /// Prepare new point
            /// TODO: New target select function
            std::cout << "Prepare new search\n"
                      << UNIMPLEMENTED_FUNCTIONALITY_TAG << "\n";
            break;

        case 'I':
            /// TODO: Start iteration function
            std::cout << "Start iteration\n"
                      << UNIMPLEMENTED_FUNCTIONALITY_TAG << "\n";
            break;

        case 'E': /////Generate explicit cardinal points file
            /// TODO: Generate explicit points
            std::cout << "Generate known points file\n"
                      << UNIMPLEMENTED_FUNCTIONALITY_TAG << "\n";
            break;

        case 'K': /////Extract key from a known association
            /// TODO: Extract key from association
            std::cout << "Generate known points file\n"
                      << UNIMPLEMENTED_FUNCTIONALITY_TAG << "\n";
            break;

        case 'C': /////Connect to a central database server
            /*
            Bypass the known point list dependencies
            Create
            */
            std::cout << "Generate known points file\n"
                      << UNIMPLEMENTED_FUNCTIONALITY_TAG << "\n";
            break;

        case 'T': /////Activate test mode
            /// TODO: Enter test mode
            std::cout << "Test program functionality\n"
                      << FUNCTIONALITY_IN_DEVELOPMENT_TAG << "\n";
            while (user_input != 'b')
            {
                std::cout << "\n\nPlease select an option: \n(T)est basic functionality\n";
                std::cin >> user_input;
                switch(user_input)
                {
                    case 'T':
                        testFunctionality();
                        break;
                }
            }
            break;

        default:
            std::cout << "Unknown option selected\n";
            break;
        }
    }
    return 0;
}