set(manager_files


Ports.cpp
Ports.h
managers.h
managers.cpp

    FileManager/FileManager.h
    FileManager/FileManager.cpp


    IterationManager/IterationManager.h
    IterationManager/IterationManager.cpp

        IterationManager/StateMachines/StateMachines.h
        IterationManager/StateMachines/StateMachines.cpp

        IterationManager/StateMachines/CoordinatorSM/CoordinatorSM.h
        IterationManager/StateMachines/CoordinatorSM/CoordinatorSM.cpp
        
        IterationManager/StateMachines/IteratorSM/IteratorSM.h
        IterationManager/StateMachines/IteratorSM/IteratorSM.cpp

    MemoryManager/MemoryManager.h
    MemoryManager/MemoryManager.cpp

    NetworkManager/NetworkManager.h
    NetworkManager/NetworkManager.cpp

        NetworkManager/StateMachines/StateMachines.h
        NetworkManager/StateMachines/StateMachines.cpp

        NetworkManager/StateMachines/ClientSM/ClientSM.h
        NetworkManager/StateMachines/ClientSM/ClientSM.cpp

        NetworkManager/StateMachines/ClientHandlerSM/ClientHandlerSM.h
        NetworkManager/StateMachines/ClientHandlerSM/ClientHandlerSM.cpp

        NetworkManager/StateMachines/SatelliteSM/SatelliteSM.h
        NetworkManager/StateMachines/SatelliteSM/SatelliteSM.cpp

        NetworkManager/StateMachines/SatelliteHandlerSM/SatelliteHandlerSM.h
        NetworkManager/StateMachines/SatelliteHandlerSM/SatelliteHandlerSM.cpp

        NetworkManager/StateMachines/ServerFrontendSM/ServerFrontendSM.h
        NetworkManager/StateMachines/ServerFrontendSM/ServerFrontendSM.cpp

    UIManager/UIManager.h
    UIManager/UIManager.cpp

        UIManager/ServerUI/ServerUI.h
        UIManager/ServerUI/ServerUI.cpp

        UIManager/ClientUI/ClientUI.h
        UIManager/ClientUI/ClientUI.cpp

        UIManager/SatelliteUI/SatelliteUI.h
        UIManager/SatelliteUI/SatelliteUI.cpp

        UIManager/TestUI/TestUI.h
        UIManager/TestUI/TestUI.cpp
            UIManager/TestUI/ArithmeticTest.cpp
            UIManager/TestUI/AlgorithmTest.cpp
            UIManager/TestUI/ThreadTest.cpp
            UIManager/TestUI/FileTest.cpp
            UIManager/TestUI/NetworkTest.cpp
            UIManager/TestUI/MemoryTest.cpp
)
add_library(managerLib ${manager_files})