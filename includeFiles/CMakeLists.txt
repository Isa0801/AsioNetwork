
add_library(Network communication/communication.cpp tcp_connection/tcp_connection.cpp tcp_server/tcp_server.cpp IOFile/IOFile.cpp)

target_include_directories(Network PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/tcp_server" "${CMAKE_CURRENT_SOURCE_DIR}/tcp_connection" "${CMAKE_CURRENT_SOURCE_DIR}/communication" "${CMAKE_CURRENT_SOURCE_DIR}/IOFile")