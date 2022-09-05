#include "UIManager.h"
#include "Ports.h"

static char counterOutput[1024] = {'\0'};
static char user_input = '\0';
static std::string user_long_input = "\0";
static unsigned long long sendingMessageContainer = 0;
static unsigned long long receivedMessage = 0u;
static unsigned long long receivedMessageContainer = 0u;
static bool faultUnresolved = false;
bool internalLoopControl = false;
bool subLoopControl = false;

////TODO: Move UI functionality into a sepparate thread to allow for a main program loop running in the background

unsigned int init_UserInterfaceSM(UI_SM_struct *UIdata)
{
    initPort(&UIdata->uiManagerRxPort, 5u);
    std::cout << "User interface initialized\n";
    UIdata->SMstate = UI_SM_INITIALIZED;
    user_input = 'M';
    return 0;
}

unsigned int start_UserInterfaceSM(UI_SM_struct *UIdata)
{
    if(UI_SM_INITIALIZED != UIdata->SMstate)
    {
        printf("UI State Machine not initialized correctly\n");
        UIdata->SMstate = UI_SM_FAULT;
    }
    
    while (UI_SM_STOPPED != UIdata->SMstate)
    {
        switch (UIdata->SMstate)
        {
            case UI_SM_INITIALIZED:
                sendMessage(UIdata->parentPort, UI_SM_TX_REQUEST_CONNECTION, 0u);
                DEBUG_MSG("UI State Machine sent connection request\n");

                sendMessage(UIdata->parentPort, UI_SM_TX_REQUEST_BUFFER, 0u);
                DEBUG_MSG("UI State Machine connection request confirmed\n");

                user_input = 'M';
                UIdata->SMstate = UI_SM_RUNNING;
                break;

            case UI_SM_RUNNING:
                switch (user_input)
                {
                    case 'M':
                        std::cout << "\n"
                                << "Please select the operating mode: \n"
                                << "(C)lient mode\n"
                                << "(D)atabase Satellite mode\n"
                                << "(S)erver mode\n"
                                << "(R)un"
                                << "\n";
                        std::cin  >> user_input;
                        break;

                    /** @brief Central Server mode User Interface
                    *
                    *  @details the operation mode as a central server
                    *  @pre a known point database 
                    *       a front end state machine
                    *       at least one client handler state machine
                    */
                    case 'S': 
                        std::cout << "Server mode selected\n";
                        sendMessage(UIdata->parentPort, UI_SM_TX_USERMODE_SERVER, sendingMessageContainer);

                        internalLoopControl = true;
                        unsigned int initializedModules = 0u;
                        while(internalLoopControl)
                        {
                            if(PORT_E_FOUND == readMessage(&(UIdata->uiManagerRxPort), &receivedMessage, &receivedMessageContainer, UI_SM_RX_NETWORK_INIT_STATE))
                            {
                                std::cout << "Checking network manager init parameters...\n";
                                unsigned int networkModules = receivedMessageContainer;
                                subLoopControl = true;
                                while(subLoopControl)
                                {
                                    if(0u == (INITIALIZED_BIT_NETWORKMANAGER_MAXCLIENTNO & networkModules))
                                    {
                                        printf("Select max number of clients:\n");
                                        std::cin >> sendingMessageContainer;
                                        
                                        sendMessage(UIdata->parentPort, UI_SM_TX_INIT_NETWORKMANAGER_CLIENTNO, sendingMessageContainer);
                                        networkModules |= INITIALIZED_BIT_NETWORKMANAGER_MAXCLIENTNO;
                                    }
                                    if(0u == (INITIALIZED_BIT_NETWORKMANAGER_SERVERIP    & networkModules))
                                    {
                                        printf("Select specific adress?(Y/n):\n");
                                        std::cin >> sendingMessageContainer;
                                        if('Y' == sendingMessageContainer)
                                        {
                                            printf("Select adress:\n");
                                            std::cin >> sendingMessageContainer;
                                        }
                                        else
                                        {
                                            sendingMessageContainer = DEFAULT_SERVER_IP;
                                        }
                                        std::cin >> sendingMessageContainer;
                                        sendMessage(UIdata->parentPort, UI_SM_TX_INIT_NETWORKMANAGER_IP, sendingMessageContainer);
                                        networkModules |= INITIALIZED_BIT_NETWORKMANAGER_SERVERIP;
                                    }
                                    if(0u == (INITIALIZED_BIT_NETWORKMANAGER_SERVERPORT  & networkModules))
                                    {
                                        printf("Select Specific port?(Y/n):\n");
                                        std::cin >> sendingMessageContainer;
                                        if('Y' == sendingMessageContainer)
                                        {
                                            printf("Select port:\n");
                                            std::cin >> sendingMessageContainer;
                                        }
                                        else
                                        {
                                            sendingMessageContainer = DEFAULT_SERVER_PORT;
                                        }
                                        sendMessage(UIdata->parentPort, UI_SM_TX_INIT_NETWORKMANAGER_PORT, sendingMessageContainer);
                                        networkModules |= INITIALIZED_BIT_NETWORKMANAGER_SERVERPORT;
                                    }
                                    if(INITIALIZED_BIT_NETWORKMANAGER_SERVER_READY == networkModules)
                                    {
                                        printf("All server parameters initialized successfully\n");
                                        initializedModules |= INITIALIZED_BIT_NETWORKMANAGER;
                                        subLoopControl = false;
                                    }
                                    if(PORT_E_FOUND == readMessage(&(UIdata->uiManagerRxPort), &receivedMessage, &receivedMessageContainer, UI_SM_RX_ABORT))
                                    {
                                        printf("Server initialization aborted by system\n");
                                        UIdata->SMstate = UI_SM_FAULT;
                                        subLoopControl = false;
                                    }
                                }
                            }
                            else 
                            if(PORT_E_FOUND == readMessage(&(UIdata->uiManagerRxPort), &receivedMessage, &receivedMessageContainer, UI_SM_RX_FILE_INIT_STATE))
                            {
                                std::cout << "Checking file manager init parameters...\n";
                                unsigned int fileModules = receivedMessageContainer;
                                subLoopControl = true;
                                while(subLoopControl)
                                {
                                    if(0u == (INITIALIZED_BIT_FILEMANAGER_KNOWNPOINTS_OK & fileModules))
                                    {
                                        printf("No known points file found. Generate new file?(Y/n)\n");
                                        std::cin >> sendingMessageContainer;
                                        if('Y' == sendingMessageContainer)
                                        {
                                            printf("Select file size:\n");
                                            std::cin >> sendingMessageContainer;
                                            sendMessage(UIdata->parentPort, UI_SM_TX_INIT_FILEMANAGER_KNOWNPOINTS_NEW, sendingMessageContainer);
                                            fileModules |= INITIALIZED_BIT_FILEMANAGER_CHECKPOINT_NEW;
                                        }
                                    }
                                    if(0u == (INITIALIZED_BIT_FILEMANAGER_CONNECTION_OK & fileModules))
                                    {
                                        printf("No known points file found. Generate new file?(Y/n)\n");
                                        std::cin >> sendingMessageContainer;
                                        if('Y' == sendingMessageContainer)
                                        {
                                            printf("Select file size:\n");
                                            std::cin >> sendingMessageContainer;
                                            sendMessage(UIdata->parentPort, UI_SM_TX_INIT_FILEMANAGER_CHECKPOINT_NEW, sendingMessageContainer);
                                            fileModules |= INITIALIZED_BIT_FILEMANAGER_CONNECTION_NEW;
                                        }
                                    }
                                    if (INITIALIZED_BIT_READY == initializedModules)
                                    {
                                        subLoopControl = false;
                                        printf("All file parameters initialized successfully\n");
                                    }
                                    if (INITIALIZED_BIT_FAULT & initializedModules)
                                    {
                                        printf("An error prevented file module initialization\n");
                                        UIdata->SMstate = UI_SM_FAULT;
                                        subLoopControl = false;
                                    }
                                }
                            }
                            else
                            if(PORT_E_FOUND == readMessage(&(UIdata->uiManagerRxPort), &receivedMessage, &receivedMessageContainer, UI_SM_RX_ITERATOR_INIT_STATE))
                            {
                                std::cout << "Checking iterator manager init parameters...\n";
                                unsigned int iteratorModules = receivedMessageContainer;
                                subLoopControl = true;
                                while(subLoopControl)
                                {
                                    if(0u == (INITIALIZED_BIT_ITERATIONMANAGER_COORDNO & iteratorModules))
                                    {
                                        printf("Select coordinator number:\n");
                                        std::cin >> sendingMessageContainer;
                                        sendMessage(UIdata->parentPort, UI_SM_TX_INIT_ITERATIONMANAGER_ITERATORNO, sendingMessageContainer);
                                        iteratorModules |= INITIALIZED_BIT_ITERATIONMANAGER_ITERATORNO;
                                    }
                                    if(0u == (INITIALIZED_BIT_ITERATIONMANAGER_ITERATORNO & iteratorModules))
                                    {
                                        printf("Select iterators per coordinator number:\n");
                                        std::cin >> sendingMessageContainer;
                                        sendMessage(UIdata->parentPort, UI_SM_TX_INIT_ITERATIONMANAGER_ITERATORNO, sendingMessageContainer);
                                        iteratorModules |= INITIALIZED_BIT_ITERATIONMANAGER_ITERATORNO;
                                    }
                                    if (INITIALIZED_BIT_READY == initializedModules)
                                    {
                                        subLoopControl = false;
                                        printf("All iteration parameters initialized successfully\n");
                                    }
                                    if (INITIALIZED_BIT_FAULT & initializedModules)
                                    {
                                        printf("An error prevented iteration module initialization\n");
                                        UIdata->SMstate = UI_SM_FAULT;
                                        subLoopControl = false;
                                    }
                                }
                            }
                            else
                            if(PORT_E_FOUND == readMessage(&(UIdata->uiManagerRxPort), &receivedMessage, &receivedMessageContainer, UI_SM_RX_MEMORY_INIT_STATE))
                            {
                                std::cout << "Checking memory manager init parameters...\n";
                                unsigned int memoryModules = receivedMessageContainer;
                                subLoopControl = true;
                                while(subLoopControl)
                                {
                                    if(0u == (INITIALIZED_BIT_ITERATIONMANAGER_KNOWNPOINTS_OK & memoryModules))
                                    {
                                        printf("Select coordinator number:\n");
                                        std::cin >> sendingMessageContainer;
                                        sendMessage(UIdata->parentPort, UI_SM_TX_INIT_MEMMANAGER_KNOWNPOINTS_OK, sendingMessageContainer);
                                        memoryModules |= INITIALIZED_BIT_ITERATIONMANAGER_KNOWNPOINTS_NEW;
                                    }
                                    if(0u == (INITIALIZED_BIT_ITERATIONMANAGER_POINTPOOL_OK & memoryModules))
                                    {
                                        printf("Select iterators per coordinator number:\n");
                                        std::cin >> sendingMessageContainer;
                                        sendMessage(UIdata->parentPort, UI_SM_TX_INIT_MEMMANAGER_POINTPOOL_OK, sendingMessageContainer);
                                        memoryModules |= INITIALIZED_BIT_ITERATIONMANAGER_POINTPOOL_NEW;
                                    }
                                    if (INITIALIZED_BIT_ITERATIONMANAGER_READY == initializedModules)
                                    {
                                        subLoopControl = false;
                                        printf("All iteration parameters initialized successfully\n");
                                    }
                                    if (INITIALIZED_BIT_MEMMANAGER_FAULT & initializedModules)
                                    {
                                        printf("An error prevented iteration module initialization\n");
                                        UIdata->SMstate = UI_SM_FAULT;
                                        subLoopControl = false;
                                    }
                                }
                            }
                            else
                            if(initializedModules)
                        }
                        user_input = 'M'; /*Display the menu again*/
                        break;

                    /** @brief Client mode
                    *
                    *  @details Sets the operation mode as a client
                    *  @pre a client state machine
                    *       a thread manager state machine
                    *       at least one iterator state machine
                    */
                    case 'C': 
                        sendMessage(UIdata->parentPort, UI_SM_TX_USERMODE_CLIENT, sendingMessageContainer);
                        internalLoopControl = true;
                        while(internalLoopControl)
                        {
                            if(PORT_E_FOUND == readMessage(&(UIdata->uiManagerRxPort), &receivedMessage, &receivedMessageContainer, UI_SM_RX_NETWORK_INIT_STATE))
                            {
                                std::cout << "Client mode initialization commencing:\n";
                                unsigned int networkModules = receivedMessageContainer;
                                if(0u == (INITIALIZED_BIT_NETWORKMANAGER_SERVERIP & networkModules))
                                {
                                    printf("Select max number of clients:\n");
                                    std::cin >> sendingMessageContainer;
                                    sendMessage(UIdata->parentPort, UI_SM_TX_INIT_NETWORKMANAGER_CLIENTNO, sendingMessageContainer);
                                }
                                if(0u == (INITIALIZED_BIT_NETWORKMANAGER_SERVERPORT & networkModules))
                                {
                                    printf("Select max number of clients:\n");
                                    std::cin >> sendingMessageContainer;
                                    sendMessage(UIdata->parentPort, UI_SM_TX_INIT_NETWORKMANAGER_CLIENTNO, sendingMessageContainer);
                                }
                                if(INITIALIZED_BIT_NETWORKMANAGER_SERVER_READY == networkModules)
                                {
                                    printf("All parameters initialized successfully\n");
                                    internalLoopControl = false;
                                }
                                if(PORT_E_FOUND == readMessage(&(UIdata->uiManagerRxPort), &receivedMessage, &receivedMessageContainer, UI_SM_RX_ABORT))
                                {
                                    printf("Server initialization aborted by system\n");
                                    internalLoopControl = false;
                                }
                            }
                            else if(PORT_E_FOUND == readMessage(&(UIdata->uiManagerRxPort), &receivedMessage, &receivedMessageContainer, UI_SM_RX_FILE_INIT_STATE))
                            {
                                std::cout << "Server mode initialization commencing:\n";
                                unsigned int networkModules = receivedMessageContainer;
                                if(0u == (INITIALIZED_BIT_NETWORKMANAGER_MAXCLIENTNO & networkModules))
                                {
                                    printf("Select max number of clients:\n");
                                    std::cin >> sendingMessageContainer;
                                    sendMessage(UIdata->parentPort, UI_SM_TX_INIT_NETWORKMANAGER_CLIENTNO, sendingMessageContainer);
                                }
                                if(0u == (INITIALIZED_BIT_NETWORKMANAGER_SERVERIP & networkModules))
                                {
                                    printf("Select max number of clients:\n");
                                    std::cin >> sendingMessageContainer;
                                    sendMessage(UIdata->parentPort, UI_SM_TX_INIT_NETWORKMANAGER_CLIENTNO, sendingMessageContainer);
                                }
                                if(0u == (INITIALIZED_BIT_NETWORKMANAGER_SERVERPORT & networkModules))
                                {
                                    printf("Select max number of clients:\n");
                                    std::cin >> sendingMessageContainer;
                                    sendMessage(UIdata->parentPort, UI_SM_TX_INIT_NETWORKMANAGER_CLIENTNO, sendingMessageContainer);
                                }
                                if(INITIALIZED_BIT_NETWORKMANAGER_SERVER_READY == networkModules)
                                {
                                    printf("All parameters initialized successfully\n");
                                    internalLoopControl = false;
                                }
                                if(PORT_E_FOUND == readMessage(&(UIdata->uiManagerRxPort), &receivedMessage, &receivedMessageContainer, UI_SM_RX_ABORT))
                                {
                                    printf("Server initialization aborted by system\n");
                                    internalLoopControl = false;
                                }
                            }
                        }
                        user_input = 'M'; /*Display the menu again*/
                        break;

                    /** @brief Satellite Database mode
                    *
                    *  @details Sets the operation mode as a Satellite Database
                    *  @pre a satellite state machine
                    *       a known point database
                    *       at least one iterator state machine
                    */
                    case 'D': 
                        // SatelliteUI(user_input, user_long_input);
                        printf("Satellite Mode Selected\n");
                        sendMessage(UIdata->parentPort, UI_SM_TX_USERMODE_SATELLITE, 0u);
                        user_input = 'M'; /*Display the menu again*/
                        break;

                    /** @brief Test mode
                    *
                    *  @details Sets the operation mode to testing
                    */
                    case 'T': /* Test mode */
                        // TestUI(user_input, user_long_input);
                        printf("Test Mode Selected\n");
                        sendMessage(UIdata->parentPort, UI_SM_TX_USERMODE_TESTING, 0u);
                        user_input = 'M'; /*Display the menu again*/
                        break;

                    case 'x': /* Exit program */
                        printf("UI shutting down\n");
                        // std::cout << "\n"
                        //         << "Exiting program\n"
                        //         << "Saving files...\n";
                        ///TODO: Create save file routine
                        sendMessage(UIdata->parentPort, UI_SM_TX_USERMODE_EXIT, 0u);
                        // std::cout << "\n"
                        //         << "Files saved successfully\n"
                        //         << "Shutting down...\n";
                        ///TODO: Check for threads and processes to be properly terminated
                        UIdata->SMstate = UI_SM_STOPPED;
                        break;

                    default:
                        std::cout << "Unknown option selected\n";
                        user_input = 'M'; /*Display the menu again*/
                        break;
                }
                break;

            case UI_SM_STOPPED:
                break;

            case UI_SM_FAULT:/* constant-expression */
                sendMessage(UIdata->parentPort, UI_SM_TX_FAULT, 0u);
                faultUnresolved = true;
                while (faultUnresolved)
                {
                    if (PORT_E_FOUND == readMessage(&(UIdata->uiManagerRxPort), &receivedMessage, &receivedMessageContainer, UI_SM_RX_CONTINUE))
                        {
                            sendMessage(UIdata->parentPort, UI_SM_TX_CONTINUING, 0u);
                            UIdata->SMstate = UI_SM_INITIALIZED;
                            faultUnresolved = false;
                        }
                }
                break;

            default:
                break;
        }
        
    }
    return 0;
}