cmake_minimum_required(VERSION 3.10)
project(rplidar)

set(SOURCE_FILES src/main.cpp)

add_executable(RPLidar ${SOURCE_FILES})

# Add RPLidar sdk
target_link_libraries(RPLidar ${CMAKE_SOURCE_DIR}/lib/rplidar_sdk/output/Linux/Release/libsl_lidar_sdk.a)
target_include_directories(RPLidar PUBLIC ${CMAKE_SOURCE_DIR}/lib/rplidar_sdk/sdk/include ${CMAKE_SOURCE_DIR}/include)
