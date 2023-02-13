cmake_minimum_required(VERSION 3.10)
PROJECT(yivo VERSION "0.1.0")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(PROJECT_IS_TOP_LEVEL)
    cmake_host_system_information(RESULT HOST QUERY HOSTNAME)
    # cmake_host_system_information(RESULT CORES QUERY NUMBER_OF_LOGICAL_CORES)
    cmake_host_system_information(RESULT OSN QUERY OS_NAME)
    cmake_host_system_information(RESULT OS_VERSION QUERY OS_RELEASE)
    cmake_host_system_information(RESULT PROC QUERY PROCESSOR_DESCRIPTION)

    message(STATUS "-------------------------------------")
    message(STATUS "  Project: ${PROJECT_NAME}")
    message(STATUS "  C++ ${CMAKE_CXX_STANDARD}")
    message(STATUS "-------------------------------------")
    message(STATUS " ${HOST}")
    message(STATUS " ${OSN}: ${OS_VERSION}")
    message(STATUS " ${PROC}")
    message(STATUS "-------------------------------------")

    set(BUILD_EXAMPLES ON)
    set(BUILD_GTESTS ON)
else()
    message(STATUS "-> ${PROJECT_NAME} is submodule")
    set(BUILD_EXAMPLES OFF)
    set(BUILD_GTESTS OFF)
endif()

add_library(${PROJECT_NAME}
    src/packet.cpp
    # src/seriallib.cpp
    # src/imu.cpp
    # src/pt.cpp
    # src/pose.cpp
    # src/twist.cpp
    # src/wrench.cpp
)
target_include_directories(${PROJECT_NAME}
    PUBLIC
        src/
)

# Examples -----------------------------------------------------------
# option(BUILD_EXAMPLES "gecko google tests" ON)
if(${BUILD_EXAMPLES})
    add_subdirectory(cmake/examples)
endif()

# Tests --------------------------------------------------------------
# option(BUILD_GTESTS "gecko google tests" ON)
if(${BUILD_GTESTS})
    add_subdirectory(cmake/gtests)
endif()
