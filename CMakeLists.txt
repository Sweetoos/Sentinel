cmake_minimum_required(VERSION 3.29)
project(sentinel)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY "https://github.com/google/googletest.git"
  GIT_TAG "v1.14.0")
set(GTEST_INSTALL
    OFF
    CACHE BOOL "Disable gtest install target")
set(BUILD_GMOCK
    OFF
    CACHE BOOL "Disable building gmock if not needed")
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
  nlohmann_json
  GIT_REPOSITORY "https://github.com/nlohmann/json.git"
  GIT_TAG "v3.11.3")
FetchContent_MakeAvailable(nlohmann_json)

find_package(OpenSSL REQUIRED)
find_package(Boost 1.70.0 REQUIRED COMPONENTS system)

add_executable(sentinel
  src/sentinel.cpp 
  src/filemanager/filemanager.cpp 
  src/filemanager/command.cpp
  src/filemanager/jsonreader.cpp
  src/algorithms/sha256.cpp 
  src/tests/test.cpp)
target_compile_options(sentinel PRIVATE -Wall -Wextra -O2)

target_include_directories(sentinel PRIVATE "${PROJECT_SOURCE_DIR}/inc")

target_link_libraries(sentinel PRIVATE 
    Boost::system
    OpenSSL::SSL
    OpenSSL::Crypto
    nlohmann_json::nlohmann_json
    gtest_main
)

if(BUILD_TESTING AND TARGET gtest)
    include(GoogleTest)
    gtest_discover_tests(sentinel)
endif()
