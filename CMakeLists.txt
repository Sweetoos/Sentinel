cmake_minimum_required(VERSION 3.20)
project(sentinel)
set(CMAKE_CXX_STANDARD 23)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY "https://github.com/google/googletest.git"
    GIT_TAG        "v1.14.0"
)
FetchContent_MakeAvailable(googletest)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenSSL REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)

if(OPENSSL_FOUND)
  include_directories(${OPENSSL_INCLUDE_DIR})
  include_directories(${Boost_INCLUDE_DIRS})
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")
  add_executable(sentinel 
        src/sentinel.cpp 

        src/filemanager/filemanager.cpp
        src/filemanager/command.cpp

        src/algorithms/sha256.cpp

        src/tests/test.cpp
    )
  target_link_libraries(sentinel 
        ${Boost_LIBRARIES} 
        ${OPENSSL_LIBRARIES}
        gtest_main     
        gtest
    )
else()
  message(FATAL_ERROR "OpenSSL not found.")
endif()

include_directories(inc)
include(GoogleTest)
gtest_discover_tests(sentinel)
