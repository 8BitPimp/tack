cmake_minimum_required(VERSION 3.0)
project(tack)

if (NOT MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -msse -msse2 -msse3 -msse4 -mfpmath=sse")
endif()

add_library(tack INTERFACE)
target_include_directories(tack INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(tack INTERFACE
  $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:-fcolor-diagnostics>
  $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_GREATER:$<CXX_COMPILER_VERSION>,4.8.5>>:-fdiagnostics-color=auto>)

add_subdirectory(testing)
