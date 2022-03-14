PROJECT(CppCleaner)
cmake_minimum_required(VERSION 3.22)
set (CMAKE_CXX_STANDARD 17)

#.cpp files
SET(cpp_SRCS main.cpp)

#packages
find_package(Boost 1.78.0 COMPONENTS regex REQUIRED)

#linking .cpp to executable
ADD_EXECUTABLE(CppCleaner ${cpp_SRCS})

#linking libraries
target_link_libraries(CppCleaner Boost::regex)