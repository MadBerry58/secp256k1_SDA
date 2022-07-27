#include "TestUI.h"

unsigned int ThreadTestUI(char &user_input, std::string &user_long_input)
{
    std::cout << "\n"
              <<  "Select Thread Operation:\n"
              <<  "(+) Create Worker thread\n"
              <<  "(*) Create Foreman thread\n"
              <<  "(@) Create Client SM thread\n"
              <<  "(%) Create Client Handler SM thread\n"
              <<  "(%) Create Server FrontEnd SM thread\n"
              // <<  "($) Create Satellite SM thread\n"
              // <<  "(#) Create Satellite Handler SM thread\n"
              <<  "\n";
    while(user_input != 'T')
    {
        std::cin >> user_input;
        switch(user_input)
        {
            case '+':
                break;
            case '*':
                break;
            case '@':
                break;
            case '%':
                break;
            default:
                break;
        }
    }
    return 0;
}