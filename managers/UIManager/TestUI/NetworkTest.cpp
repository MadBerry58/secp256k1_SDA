#include "TestUI.h"

unsigned int NetworkTestUI(char &user_input, std::string &user_long_input)
{
    std::cout << "\n"
              <<  "Select Network Operation:\n"
              ///TODO: Create default SM machines
              <<  "(@) ServerFrontend <-> ClientSM\n"
              <<  "(+) ClientHandlerSM <-> ClientSM\n"
              <<  "(-) ServerFrontend <-> SatelliteSM\n"
              <<  "(*) SatelliteHandlerSM <-> SatelliteSM\n"
              <<  "(W) ServerFrontend <-> RESTclient"
              <<  "(R) REST_Handler <-> RESTclient"
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