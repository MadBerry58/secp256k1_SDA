set(src_files
    headers/Constants.h

    Mod.cpp
    headers/Mod.h
    
    headers/Iterators.h
    Iterators.cpp

    Point.cpp
    headers/Point.h

    # headers/GeneratorEnum.h
)
add_library(srcLib ${src_files})
# add_library(srcLib SHARED ${src_files})