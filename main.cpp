#include "managers/tests/functionalityTest.h"
#include "managers/headers/fileManager.h"
#include "runnables/headers/UI_runnable.h"

int main(int argc, char **argv)
{
    // for(;;)
    // {
    //     switch(getopt)
    // }
    // switch(getopt())
    std::cout << "It's alive!\n" << std::endl;
    modInit();
    fileManager_Init();
    userInterface_Init();
    // userInterface_Start();
    testFunctionality();

    return 0;
}