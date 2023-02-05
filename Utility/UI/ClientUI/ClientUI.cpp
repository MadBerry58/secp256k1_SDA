#include "ClientUI.h"

//message buffer[] - required to send init data in message bursts

unsigned int ClientUI(UI_SM_struct *UIdata)
{
    // std::cout << "Client mode selected\n";
    //Build file manager init data
        //if init file was provided
            //if file is valid
                //load checkpoints
            //else if file is invalid
                //warn the user
                //offer to recover file or create a new file
        //else if file was not provided
            //offer to search for a file or create a new one
    //if new file needs to be created
        //create new file
    //send burst of ionit data to general manager

    //initialize memory manager
        //if init file was provided
            //if file is valid
                //load checkpoints
            //else if file is invalid
                //warn the user
                //offer to recover file or create a new file
        //else
            //ask user about buffer size relating to:
                //iterator point buffers
                //iterator processed data buffers
                    //data is dependent on process time/internet speed
                    //optimal ratio is for iteration/data processing/data sending to be performed in parallel, with no idling (min 3 equal buffers)
                
    //initialize network manager
        //initialize clientSM
    return 0;
}