set(src_files
    ModularArithmetic/Mod.cpp
    ModularArithmetic/Mod.h
    
    PointArithmetic/Point.h
    PointArithmetic/Point.cpp

    Algorithms/Algorithms.cpp
    Algorithms/Algorithms.h    

    Arithmetic.h
    Arithmetic.cpp
)
add_library(srcLib ${src_files})