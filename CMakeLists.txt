cmake_minimum_required(VERSION 3.10)
project(PZ2048 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(src/include)
include_directories(third_party/Crow/include)
include_directories(third_party/asio-1.30.2/include)

add_compile_definitions(BOOST_ASIO_STANDALONE)

add_executable(game_logic_test src/game_logic_test.cpp src/game_logic.cpp src/utils.cpp)
add_executable(user_logic_test src/user_logic_test.cpp src/user_logic.cpp src/game_logic.cpp src/utils.cpp)
add_executable(server src/server.cpp src/game_logic.cpp src/user_logic.cpp src/utils.cpp)

# 添加运行和清理目标
add_custom_target(run_server
    COMMAND server
    DEPENDS server
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_target(clean_server
    COMMAND ${CMAKE_COMMAND} -E remove -f server
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)