#include "UIManager.h"
#include "Ports.h"

////TODO: Move UI functionality into a sepparate thread to allow for a main program loop running in the background

unsigned int UserInterfaceSM_Init(UISMStruct *UIdata)
{
    initPort(&UIdata->uiManagerRxPort, 5u);
    std::cout << "User interface initialized\n";
    return 0;
}

////TODO: the comm ports are getting stuck
//add IDs to the individual threads to find out who is blocking the port
//find a better sync mechanism for the ports

unsigned int UserInterfaceSM_Listen(UISMStruct *UIdata)
{
    sleep(0.4);
    printf("SM started\n");
    unsigned int errorNo = 0u;
    unsigned int receivedMessage = 0u;
    unsigned long long receivedMessageContainer = 0u;
    printf("SM entering read loop\n");
    while(PORT_MESSAGE_READ != readMessage(&(UIdata->uiManagerRxPort), &receivedMessage, &receivedMessageContainer))
    {
        sleep(0.3);
    }
    printf("SM received message %llu\n", receivedMessageContainer);
    if(ECHO == receivedMessage)
    {
        while(PORT_MESSAGE_SENT != sendMessage(UIdata->parentPort, ECHO_RESPONSE, receivedMessageContainer))
        {
            sleep(0.3);
        }
    }
    pthread_exit(0u);
    return errorNo;
}

unsigned int UserInterfaceSM_Start(UISMStruct &UIdata)
{
    while (UIdata.SMstate != UI_STOPPED)
    {
        std::cout << "\n"
                  << "Please select the operating mode: \n"
                  << "(C)lient mode\n"
                  << "(D)atabase Satellite mode\n"
                  << "(S)erver mode\n"
                  << "\n";
        std::cin  >> user_input;

        switch (user_input)
        {
            /** @brief Central Server mode User Interface
            *
            *  @details the operation mode as a central server
            *  @pre a known point database 
            *       a front end state machine
            *       at least one client handler state machine
            */
            case 'S': 
                ServerUI(user_input, user_long_input);
                break;

            /** @brief Client mode
            *
            *  @details Sets the operation mode as a client
            *  @pre a client state machine
            *       a thread manager state machine
            *       at least one iterator state machine
            */
            case 'C': 
                ClientUI(user_input, user_long_input);
                break;

            /** @brief Satellite Database mode
            *
            *  @details Sets the operation mode as a Satellite Database
            *  @pre a satellite state machine
            *       a known point database
            *       at least one iterator state machine
            */
            case 'D': 
                SatelliteUI(user_input, user_long_input);
                break;

            /** @brief Test mode
            *
            *  @details Sets the operation mode to testing
            */
            case 'T': /* Test mode */
                TestUI(user_input, user_long_input);
                break;

            case 'x': /* Exit program */
                std::cout << "\n"
                        << "Exiting program\n"
                        << "Saving files...\n";
                ///TODO: Create save file routine
                std::cout << "\n"
                        << "Files saved successfully\n"
                        << "Shutting down...\n";
                ///TODO: Check for threads and processes to be properly terminated
                break;

            default:
                std::cout << "Unknown option selected\n";
                break;
        }
    }
    return 0;
}