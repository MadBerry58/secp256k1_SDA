set(utility_files
    CommandLine/CommandLine_Types.h
    CommandLine/CommandLine.h
    CommandLine/CommandLine.cpp
    
    Communication/Ports_Types.h
    Communication/Ports.h
    Communication/Ports.cpp

    FileUtility/FileUtility_Types.h
    FileUtility/FileUtility.h
    FileUtility/FileUtility.cpp

    GlobalData/Definitions.h
    GlobalData/ErrorCodes.h

    MemoryUtility/MemoryUtility_Types.h
    MemoryUtility/MemoryUtility.h
    MemoryUtility/MemoryUtility.cpp
)
add_library(utilityLib ${utility_files})