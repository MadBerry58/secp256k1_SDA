cmake_minimum_required(VERSION 3.16)
project(secp256k1_SDA)

set(CMAKE_CXX_STANDARD 14)

add_executable(secp256k1_SDA main.cpp src/Point.cpp include/Point.h src/Mod.cpp include/Mod.h include/Constants.h src/Operators.cpp include/Operators.h)

target_link_libraries(${PROJECT_NAME}
        "/usr/lib/x86_64-linux-gnu/libgmp.a"
        "/usr/lib/x86_64-linux-gnu/libgmpxx.a"
        )