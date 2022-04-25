set(manager_files
    headers/fileManager.h
    fileManager.cpp

    headers/functionality.h
    functionality.cpp
    
    headers/memoryManager.h
    memoryManager.cpp
    
    headers/networkManager.h
    networkManager.cpp
    
    headers/threadManager.h
    threadManager.cpp
)

add_library(managerLib ${manager_files})

target_link_libraries(managerLib srcLib)