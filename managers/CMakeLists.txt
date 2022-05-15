set(manager_files
    headers/fileManager.h
    fileManager.cpp
    
    headers/memoryManager.h
    memoryManager.cpp
    
    headers/connectionManager.h
    connectionManager.cpp
    
    headers/threadManager.h
    threadManager.cpp
)
add_library(managerLib ${manager_files})
# add_library(managerLib SHARED ${manager_files})