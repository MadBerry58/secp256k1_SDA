cmake_minimum_required(VERSION 3.0.0)
project(CMake_Build VERSION 0.1.0)

include(CTest)
enable_testing()


set(CMAKE_CXX_STANDARD 14)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
add_executable(secp256k1_SDA main.cpp src/Point.cpp include/Point.h src/Mod.cpp include/Mod.h include/Constants.h src/Operators.cpp include/Operators.h)


project(secp256k1_SDA)

target_link_libraries(${PROJECT_NAME}
        "/usr/lib/x86_64-linux-gnu/libgmp.a"
        "/usr/lib/x86_64-linux-gnu/libgmpxx.a"
        )