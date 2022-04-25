set(src_files
    headers/Constants.h
    
    Mod.cpp
    headers/Mod.h
    
    Operators.cpp
    headers/Operators.h
    
    Point.cpp
    headers/Point.h
)

add_library(srcLib  ${src_files})

target_link_libraries( srcLib
        "/usr/lib/x86_64-linux-gnu/libgmp.a"
        "/usr/lib/x86_64-linux-gnu/libgmpxx.a"
)