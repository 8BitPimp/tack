set(SOURCE_FILES 
    testing.cpp
    testing.h
    test_float4.cpp)
add_executable(testing ${SOURCE_FILES})
target_link_libraries(testing tack)
