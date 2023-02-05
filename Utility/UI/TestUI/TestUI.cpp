#include "TestUI.h"

unsigned int TestUI(char &user_input, std::string &user_long_input)
{
    ///TODO: Create separate interactive testing interfaces
    std::cout << FUNCTIONALITY_IN_DEVELOPMENT_TAG;
    std::cout << "\n"
            << "Test mode selected\n"
            << "------------------------------------------------------------------------------------------------\n"
            << "Access to test functionality may corrupt or destroy local files. Please proceed with caution\n"
            << "If you stumbled upon this option by mistake, please input any key to return to the previous menu\n\n"
            << "------------------------------------------------------------------------------------------------\n"
            << "Input 'q' to continue to the testing menu.\n";
    std::cin >> user_input;
    if(user_input != 'q')
    {
        return 0;
    }
    while (user_input != 'R')
    {
        std::cout << "\n"
            <<  "Test mode selected. Use at your own risk!\n"
            ///TODO: implement existing file backup functionality
            <<  "(A)rithmetic Tests\n"
            <<  "(I)terator Algorithms Tests\n"
            <<  "(F)ile Management Tests\n"
            <<  "(M)emory management Tests\n"
            <<  "(N)etwork management Tests\n"
            <<  "(T)hread management Tests\n"
            <<  "(R)eturn to previous menu\n"
            <<  "\n";
        std::cin >> user_input;
        
        switch(user_input)
        {
            case 'A':
                ArithmeticTestUI(user_input, user_long_input);
                break;

            case 'I':
                AlgorithmTestUI(user_input, user_long_input);
                break;

            case 'F':
                FileTestUI(user_input, user_long_input);
                break;

            case 'M':
                MemoryTestUI(user_input, user_long_input);
                break;
            
            case 'N':
                NetworkTestUI(user_input, user_long_input);
                break;

            case 'T': /* Test thread related operations */
                ThreadTestUI(user_input, user_long_input);
                break;
        
            default:
                break;
        }
    }
    return 0;
}