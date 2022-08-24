#include "TestUI.h"

unsigned int AlgorithmTestUI(char &user_input, std::string &user_long_input)
{
    std::cout << "\n"
                <<  "Select Algorithm Operation:\n"
                <<  "(@) Point Generation\n"
                <<  "(+) Point Addition\n"
                <<  "(-) Point Subtraction\n"
                <<  "(*) Point Multiplication\n"
                <<  "(T) Back to Top\n"
                <<  "\n";
    while(user_input != 'T')
    {
        std::cin >> user_input;
        switch(user_input)
        {
            case '@':
            case '+':
            case '-':
            case '*':
                break;
        }
    }
    return 0;
}