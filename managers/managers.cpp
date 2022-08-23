#include "managers.h"
#include "../Arithmetic.h"

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
    unsigned long errorNo = 0u;
    if ((errorNo = init_Mod()) != MOD_E_OK)
    {
        printf("Modular Arithmetic init failed with code %lu\n", errorNo);
    }

    if ((errorNo = init_Point()) != MOD_E_OK)
    {
        printf("Modular Arithmetic init failed with code %lu\n", errorNo);
    }

    long unsigned int errorNo = -1;

    if ((errorNo = init_FileManager(initData)) != INTEGRITY_E_FILE_INIT_OK)
    {
        printf("File Manager init failed with code %lu\n", errorNo);
    }

    if ((errorNo = init_NetworkManager(initData)) != NETWORK_MANAGER_E_OK)
    {
        printf("Network Manager init failed with code %lu\n", errorNo);
    }

    if ((errorNo = init_MemoryManager(initData)) != NETWORK_MANAGER_E_OK)
    {
        printf("Network Manager init failed with code %lu\n", errorNo);
    }

}


