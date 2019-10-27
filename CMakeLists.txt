cmake_minimum_required(VERSION 3.14)
project(Micromachines)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -pthread)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(${SDL2_INCLUDE_DIR})

include_directories(${PROJECT_SOURCE_DIR}/server)
include_directories(${PROJECT_SOURCE_DIR}/server/Game)
include_directories(${PROJECT_SOURCE_DIR}/server/Game/Box2D)
add_subdirectory(${PROJECT_SOURCE_DIR}/server/Game/Box2D)

set(SERVER_SOURCE_FILES
	server/config/Configuration.cpp
	common/Socket.cpp
	server/Talker.cpp
	common/Thread.cpp
	common/Protocol.cpp
		server/Game/entities/Entity.cpp
		server/Game/entities/RaceCar.cpp
        server/Game/GameWorld.cpp
		common/InfoBlock.cpp
		server/Game/CollisionsManager.cpp server/Game/CollisionsManager.h
		server/Game/status_effects/StatusEffect.cpp server/Game/status_effects/StatusEffect.h server/Game/status_effects/SpeedStatusEffect.cpp server/Game/status_effects/SpeedStatusEffect.h common/Stopwatch.cpp common/Stopwatch.h)

set(CLIENT_SOURCE_FILES
	common/Socket.cpp
	common/Protocol.cpp
	common/InfoBlock.cpp
	common/Thread.cpp
	common/Event.cpp
	common/SafeEventQueue.cpp
		client/SDLStarter.cpp
		client/communication/UserInput.cpp
		common/SafeEventQueue.cpp
		common/SafeEventQueue.h
		common/Event.cpp
		common/Event.h client/TextureLoader.cpp client/TextureLoader.h common/Stopwatch.cpp common/Stopwatch.h)

set(TEST_SOURCE_FILES
        tests/tests.cpp
		server/Game/CollisionsManager.cpp
		server/Game/CollisionsManager.h server/Game/status_effects/SpeedStatusEffect.cpp server/Game/status_effects/SpeedStatusEffect.h server/Game/entities/CarStats.cpp server/Game/entities/CarStats.h common/Stopwatch.cpp common/Stopwatch.h)

add_executable(Server server/main.cpp ${SERVER_SOURCE_FILES})
add_executable(Client client/main.cpp ${CLIENT_SOURCE_FILES})
add_executable(Test ${TEST_SOURCE_FILES} ${SERVER_SOURCE_FILES})

target_link_libraries(Server yaml-cpp pthread Box2D)
target_link_libraries(Client yaml-cpp pthread
		${SDL2_LIBRARY}
		${SDL2_IMAGE_LIBRARIES}
		${SDL2_TTF_LIBRARIES}
		-lSDL2_ttf)
target_link_libraries(Test yaml-cpp Box2D)
