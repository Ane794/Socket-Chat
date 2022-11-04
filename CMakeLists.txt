cmake_minimum_required(VERSION 3.22)
project(socket-chat)

set(CMAKE_CXX_STANDARD 23)

include_directories(src)

# socket-chat-util
aux_source_directory(src/util ${PROJECT_NAME}-util_SOURCES)
add_library(${PROJECT_NAME}-util ${${PROJECT_NAME}-util_SOURCES})
target_link_libraries(${PROJECT_NAME}-util yaml-cpp)

# socket-chat-server
aux_source_directory(src/server ${PROJECT_NAME}-server_SOURCES)
add_executable(${PROJECT_NAME}-server ${${PROJECT_NAME}-server_SOURCES})
target_link_libraries(${PROJECT_NAME}-server ${PROJECT_NAME}-util)
if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    target_link_libraries(${PROJECT_NAME}-server pthread)
endif ()

# socket-chat-client
aux_source_directory(src/client ${PROJECT_NAME}-client_SOURCES)
add_executable(${PROJECT_NAME}-client ${${PROJECT_NAME}-client_SOURCES})
target_link_libraries(${PROJECT_NAME}-client ${PROJECT_NAME}-util)
if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    target_link_libraries(${PROJECT_NAME}-client pthread)
endif ()
