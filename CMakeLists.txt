cmake_minimum_required(VERSION 3.16.0)
project(CMake_Build VERSION 0.1.0)

include(CTest)
enable_testing()


project(secp256k1_SDA)
set(CMAKE_CXX_STANDARD 14)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
#add_executable(secp256k1_SDA main.cpp src/Point.cpp include/Point.h src/Mod.cpp include/Mod.h include/Constants.h src/Operators.cpp include/Operators.h)



#file(RELATIVE_PATH SECP256K1_SDA_SOURCE_REL_DIR
#     ${CMAKE_CURRENT_SOURCE_DIR}
#     ${SECP256K1_SDA__SOURCE_DIR}/.)

#include_directories(${SECP256K1_SDA_SOURCE_REL_DIR}/managers ${SECP256K1_SDA_SOURCE_REL_DIR}/runnables ${SECP256K1_SDA_SOURCE_REL_DIR}/src)

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

target_link_libraries(${PROJECT_NAME}
        srcLib
        runnableLib
        managerLib
)