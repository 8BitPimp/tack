cmake_minimum_required(VERSION 3.0)
project(tack)

if (NOT MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -msse -msse2 -msse3 -msse4 -mfpmath=sse")
endif()

add_library(tack INTERFACE)
target_include_directories(tack INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(testing)
