#include "src/headers/Mod.h"
#include "managers/tests/functionalityTest.h"
#include "managers/headers/fileManager.h"
#include "runnables/headers/UI_runnable.h"

int main() {

    std::cout << "It's alive!\n" << std::endl;
    modInit();
    fileManager_Init();
    userInterface_Init();
    userInterface_Start();
    /*
    */
    return 0;
}