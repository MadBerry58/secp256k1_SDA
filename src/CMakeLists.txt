set(src_files
    headers/Constants.h
    
    Mod.cpp
    headers/Mod.h
    
    Operators.cpp
    headers/Operators.h
    
    Point.cpp
    headers/Point.h
)
add_library(srcLib SHARED ${src_files})