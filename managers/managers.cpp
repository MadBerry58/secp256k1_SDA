#include "managers.h"

/* Manager initialization:
 * Each manager holds specific functionality, data structures and state machine control
 * Static components (do not use dedicated threads) are initialized by allocating all the required data
 * Runtime components (thread state machines) are initialized by allocating the initial data structures,
 * testing the communication ports to the other components and bringing the state machine into a ready state
 * 
 * After all the components are initialized, the iteration can be started.
 */
unsigned int init_managers(std::string initData)
{
    init_NetworkManager(initData);
    long unsigned int errorNo = -1;
    if ((errorNo = fileManager_Init()) != INTEGRITY_E_FILE_INIT_OK)
    {
        printf("fileManagerInit failed with code %lu\n", errorNo);
    }
}


