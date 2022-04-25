#include "src/headers/Operators.h"
#include "managers/tests/functionalityTest.h"
#include "managers/headers/filemanager.h"
#include "runnables/headers/UI_runnable.h"

int main() {
    modInit();
    fileManager_Init();
    userInterface_Init();
    userInterface_Start();
    
    return 0;
}