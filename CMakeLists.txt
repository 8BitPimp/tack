cmake_minimum_required(VERSION 3.6)
project(tack)

if (NOT MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -msse -msse2 -msse3 -msse4 -mfpmath=sse")
endif()

add_subdirectory(include)
add_subdirectory(testing)
