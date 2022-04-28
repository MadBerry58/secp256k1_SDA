cmake_minimum_required(VERSION 3.16.0)
project(CMake_Build VERSION 0.1.0)

include(CTest)
enable_testing()

#add_compile_options(-fPIC)

project(secp256k1_SDA)
set(CMAKE_CXX_STANDARD 14)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

set(SOURCE_FILES main.cpp)

include_directories(src)
include_directories(runnables)
include_directories(managers)

link_directories(src)
link_directories(runnables)
link_directories(managers)

add_subdirectory(src)
add_subdirectory(runnables)
add_subdirectory(managers)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(srcLib
        "/usr/lib/x86_64-linux-gnu/libgmp.so"
        "/usr/lib/x86_64-linux-gnu/libgmpxx.so"
        # "/src/headers/gmp/libgmp.so"
        # "/src/headers/gmp/libgmpxx.so"
        # "/src/headers/gmp/libgmp.a"
        # "/src/headers/gmp/libgmpxx.a"
        )

target_link_libraries(${PROJECT_NAME}
        srcLib
        runnableLib
        managerLib
)