#include "TestUI.h"
#include "NetworkManager/NetworkManager.h"

unsigned int ThreadTestUI(char &user_input, std::string &user_long_input)
{
    std::cout << "\n"
              <<  "Select Thread Operation:\n"
              <<  "(+) Create Worker thread\n"
              <<  "(*) Create Foreman thread\n"
              <<  "(@) Create Client SM thread\n"
              <<  "(%) Create Client Handler SM thread\n"
              <<  "(%) Create Server FrontEnd SM thread\n"
              <<  "(Q) Return to previous menu\n"
              <<  "\n";
    while(user_input != 'Q')
    {
        std::cin >> user_input;
        switch(user_input)
        {
            case '+':

                break;
            
            case '*':
            
                break;
            
            case '@':
                std::cout << "Enter message to be returned:\n";
                std::cin >> user_long_input;
                startClientSM(user_long_input);
                std::cout << "ClientSM test finished\nPlease choose another option\n";
                break;
            
            case '%':
            
                break;
            
            default:
            
                break;
        }
    }
    return 0;
}