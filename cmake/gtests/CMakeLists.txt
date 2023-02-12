
include(FetchContent)

# GTest -----------------
FetchContent_Declare(gtest
  GIT_REPOSITORY "https://github.com/google/googletest"
  GIT_TAG "origin/main"
  SOURCE_DIR "${CMAKE_BINARY_DIR}/_deps/gtest"
)
# set(EXAMPLES OFF CACHE INTERNAL "Dont build examples")
FetchContent_MakeAvailable(gtest)
if(gtest_POPULATED)
    message(STATUS "=> Found gtest")
else()
    message(STATUS "*** Didn't find gtest")
endif()

#----------------------------
enable_testing()

list(APPEND yivo-gtests
    msgs-gtest
)

message(STATUS "yivo::gTests ----------------------")
foreach(name ${yivo-gtests})
    # get_filename_component(name ${src} NAME_WE)
    message(STATUS " -> ${name}")
    # message(STATUS ">> ${ALL_LIBS}")
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name}
        GTest::gtest_main
        ${PROJECT_NAME})
    add_test(NAME ${name} COMMAND ${name})
endforeach()

include(GoogleTest)
gtest_discover_tests(${yivo-gtests})

