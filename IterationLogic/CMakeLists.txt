set(iteration_files
    CoordinationLogic/Coordinator_Types.h
    CoordinationLogic/Coordinator.h
    CoordinationLogic/Coordinator.cpp
    CoordinationLogic/CoordinatorSM/CoordinatorSM.h
    CoordinationLogic/CoordinatorSM/CoordinatorSM.cpp
    
    IteratorLogic/Iterator_Types.h
    IteratorLogic/Iterator.h
    IteratorLogic/Iterator.cpp
    IteratorLogic/IteratorSM/IteratorSM.h
    IteratorLogic/IteratorSM/IteratorSM.cpp

    IterationLogic.h
    IterationLogic.cpp

)
add_library(iterationLib ${iteration_files})