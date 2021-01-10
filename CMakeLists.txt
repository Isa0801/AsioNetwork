cmake_minimum_required(VERSION 3.10)

project(Networking)

# change to this your boost location
add_library(filesystem  
            C:/dev/boost_1_73_0/libs/filesystem/src/windows_file_codecvt.cpp
            C:/dev/boost_1_73_0/libs/filesystem/src/utf8_codecvt_facet.cpp
            C:/dev/boost_1_73_0/libs/filesystem/src/unique_path.cpp
            C:/dev/boost_1_73_0/libs/filesystem/src/portability.cpp
            C:/dev/boost_1_73_0/libs/filesystem/src/path_traits.cpp
            C:/dev/boost_1_73_0/libs/filesystem/src/path.cpp
            C:/dev/boost_1_73_0/libs/filesystem/src/operations.cpp
            C:/dev/boost_1_73_0/libs/filesystem/src/exception.cpp
            C:/dev/boost_1_73_0/libs/filesystem/src/directory.cpp
            C:/dev/boost_1_73_0/libs/filesystem/src/codecvt_error_category.cpp
            )



add_subdirectory(includeFiles)
#add_library(COMM communication.h communication.cpp)
#add_library(CONN tcp_connection.h tcp_connection.cpp)
#add_library(TCP_SER tcp_server.h tcp_server.cpp)
#add_library(header header.hpp header.cpp)
#add_library(header chat_message.hpp)

#add_library(header STATIC IMPORTED)
#set_property(TARGET header PROPERTY IMPORTED_LOCATION "../header.o")


add_library(WS2 STATIC IMPORTED)
set_property(TARGET WS2 PROPERTY IMPORTED_LOCATION "../SDK/WS2_32.lib")
add_library(WS2S STATIC IMPORTED)
set_property(TARGET WS2S PROPERTY IMPORTED_LOCATION "../SDK/WSock32.Lib")

add_executable(client client.cpp)
add_executable(server server.cpp)

target_link_libraries(client WS2 Network filesystem WS2S)
target_link_libraries(server Network filesystem WS2 WS2S)