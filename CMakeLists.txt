cmake_minimum_required(VERSION 3.8)

project(common_lib)

add_subdirectory(src/common common)
add_subdirectory(src/json json)
add_subdirectory(src/mqtt_cpp mqtt_cpp)
add_subdirectory(src/sioclog sioclog)
add_subdirectory(src/sioctimer sioctimer)
add_subdirectory(src/xpacket xpacket)
add_subdirectory(src/xthread xthread)
