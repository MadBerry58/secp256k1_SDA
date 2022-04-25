set(manager_files
    headers/fileManager.h
    fileManager.cpp

    headers/iterationManager.h
    iterationManager.cpp
    
    headers/memoryManager.h
    memoryManager.cpp
    
    headers/networkManager.h
    networkManager.cpp
    
    headers/threadManager.h
    threadManager.cpp
)
add_library(managerLib SHARED ${manager_files})