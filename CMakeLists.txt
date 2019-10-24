cmake_minimum_required(VERSION 3.14)
project(Micromachines)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -pthread)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

#add_executable(ej1 main.cpp)
#add_subdirectory(classes)

#target_link_libraries(ej1 myclasses)

include_directories(${PROJECT_SOURCE_DIR}/server)

set(SERVER_SOURCE_FILES
	server/config/Configuration.cpp
	common/Socket.cpp
	server/Talker.cpp
	common/Protocol.cpp
)

set(CLIENT_SOURCE_FILES
	server/config/Configuration.cpp
	common/Socket.cpp
	server/Talker.cpp
	common/Protocol.cpp
)

set(TEST_SOURCE_FILES
        tests/tests.cpp)

add_executable(Server server/main.cpp ${SERVER_SOURCE_FILES} server/GameWorld.cpp server/GameWorld.h server/GameObject.cpp server/GameObject.h)
add_executable(Client client/main.cpp ${CLIENT_SOURCE_FILES})
add_executable(Test ${TEST_SOURCE_FILES} ${SERVER_SOURCE_FILES})

target_link_libraries(Server yaml-cpp)
target_link_libraries(Client yaml-cpp)
target_link_libraries(Test yaml-cpp)

#box2d
target_link_libraries (Server Box2D)
include_directories(server/Box2D)
add_subdirectory(server/Box2D)