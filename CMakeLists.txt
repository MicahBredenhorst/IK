cmake_minimum_required(VERSION 3.14)
project(IK_CPP)
set(CMAKE_CXX_STANDARD 11)

set(TEST_NAME Test)

# Build target main project
add_executable(${PROJECT_NAME} main.cpp)

# Build target test project
add_executable(${TEST_NAME} ./test/Test.cpp ./test/Test_IK.cpp ./test/Test_Math.cpp ./test/Test_Vector.cpp)

# Download getest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)

# Add the libraries subdirectories
add_subdirectory(IK)
add_subdirectory(Vector)
add_subdirectory(Math)
add_subdirectory(Link)

# Make directories available for the project target
target_include_directories(${PROJECT_NAME}
    PUBLIC IK
    PUBLIC Vector
    PUBLIC Math
    PUBLIC Link
)

target_include_directories(Math
  PUBLIC Vector
)

target_include_directories(Link
  PUBLIC Vector
)

target_include_directories(IK
  PUBLIC Link
  PUBLIC Vector
)

target_include_directories(Vector
  PUBLIC Math
)

# Make directories available for Test build target
target_include_directories(${TEST_NAME}
    PUBLIC IK
    PUBLIC Vector
    PUBLIC Math
    PUBLIC Link
    ./build/_deps/googletest-src/googletest/include/gtest.h
)

# Link the libraries to the build target
target_link_libraries(${PROJECT_NAME}
    IK
    Vector
    Math
    Link
)

target_link_libraries(${TEST_NAME} 
    gtest_main 
    Vector 
    Math 
    IK 
    Link
  )

enable_testing()

include(GoogleTest)

gtest_discover_tests(${TEST_NAME})
