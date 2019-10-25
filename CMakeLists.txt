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
include_directories(${PROJECT_SOURCE_DIR}/server/Game)
include_directories(${PROJECT_SOURCE_DIR}/server/Game/Box2D)
add_subdirectory(${PROJECT_SOURCE_DIR}/server/Game/Box2D)

set(SERVER_SOURCE_FILES
	server/config/Configuration.cpp
	common/Socket.cpp
	server/Talker.cpp
	common/Protocol.cpp
        server/Game/GameObject.cpp
        server/Game/RaceCar.cpp
        server/Game/GameWorld.cpp
		common/InfoBlock.cpp
)

set(CLIENT_SOURCE_FILES
	server/config/Configuration.cpp
	common/Socket.cpp
	server/Talker.cpp
	common/Protocol.cpp
		common/InfoBlock.cpp )

set(TEST_SOURCE_FILES
        tests/tests.cpp)

add_executable(Server server/main.cpp ${SERVER_SOURCE_FILES})
add_executable(Client client/main.cpp ${CLIENT_SOURCE_FILES})
add_executable(Test ${TEST_SOURCE_FILES} ${SERVER_SOURCE_FILES})

target_link_libraries(Server yaml-cpp)
target_link_libraries(Client yaml-cpp)
target_link_libraries(Test yaml-cpp)
target_link_libraries (Server Box2D)
target_link_libraries (Test Box2D)