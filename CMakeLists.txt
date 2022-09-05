cmake_minimum_required(VERSION 3.16.0)
project(CMake_Build VERSION 0.1.0)

project(secp256k1-SDA)
set(CMAKE_CXX_STANDARD 14)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
find_package(Boost ${BOOST_MIN_VERSION} REQUIRED)

set(SOURCE_FILES main.cpp Constants.h TypeDef.h)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(Arithmetic)
include_directories(managers)

link_directories(${Boost_INCLUDE_DIRS})
link_directories(Arithmetic)
link_directories(managers)

add_subdirectory(Arithmetic)
add_subdirectory(managers)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} #library linking order goes from high level to low level
managerLib
srcLib
${Boost_LIBRARIES}
pthread
gmp
)
