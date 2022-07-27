#ifndef SECP251K1_SANDBOX_FILETEST_C
#define SECP251K1_SANDBOX_FILETEST_C

#include "TestUI.h"

unsigned int FileTestUI(char &user_input, std::string &user_long_input)
{
    std::cout << "\n"
              <<  "Select File Operation:\n"
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
#endif