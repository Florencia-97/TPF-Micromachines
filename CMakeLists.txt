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
		common/infostream/Socket.cpp
		common/infostream/Protocol.cpp
		server/Game/entities/Entity.cpp
		server/Game/entities/RaceCar.cpp
		server/Game/entities/CarStats.cpp
		server/Game/GameWorld.cpp
		common/infostream/InfoBlock.cpp
		server/Game/CollisionsManager.cpp server/Game/CollisionsManager.h
		server/threads/PlayerThread.cpp
		server/Game/status_effects/StatusEffect.cpp server/Game/status_effects/StatusEffect.h
		server/Game/status_effects/SpeedStatusEffect.cpp server/Game/status_effects/SpeedStatusEffect.h
		common/Stopwatch.cpp common/Stopwatch.h
		server/threads/GameThread.cpp server/threads/GameThread.h
        server/threads/GamesManagerThread.cpp server/threads/GamesManagerThread.h
		common/conc/BaseThread.cpp common/conc/BaseThread.h
		common/conc/SenderThread.cpp common/conc/SenderThread.h
		common/conc/ReceiverThread.cpp common/conc/ReceiverThread.h
		server/Server.cpp server/Server.h
		)

set(CLIENT_SOURCE_FILES
		common/infostream/Socket.cpp
		common/infostream/Protocol.cpp
		common/infostream/InfoBlock.cpp
		common/Event.cpp
		client/RenderThread.cpp
		client/rendering/SDLStarter.cpp
		client/Car.cpp client/Car.h
		client/communication/UserInput.cpp client/communication/UserInput.h
		client/communication/EventSender.cpp client/communication/EventSender.h
		client/communication/Receiver.cpp client/communication/Receiver.h
		client/rendering/TextureLoader.cpp client/rendering/TextureLoader.h
		client/rendering/SDLStarter.h
		client/rendering/LTexture.cpp client/rendering/LTexture.h
		common/conc/BaseThread.cpp common/conc/BaseThread.h
		common/conc/SenderThread.cpp common/conc/SenderThread.h
		common/conc/ReceiverThread.cpp common/conc/ReceiverThread.h
		client/tiles/Tile.cpp client/tiles/Tile.h
		client/rendering/TEXTURE_ERROR.cpp client/rendering/TEXTURE_ERROR.h
		client/RenderThread.cpp client/RenderThread.h
		client/rendering/GameRenderer.cpp client/rendering/GameRenderer.h
		client/GameMap.cpp client/GameMap.h
		client/Client.cpp
		client/tiles/TilesFactory.cpp client/tiles/TilesFactory.h
		client/rendering/interfaces/Button.cpp client/rendering/interfaces/Button.h
		client/rendering/interfaces/Menu.cpp client/rendering/interfaces/Menu.h client/Client.cpp client/Client.h client/rendering/interfaces/ConnectButton.cpp client/rendering/interfaces/ConnectButton.h client/rendering/interfaces/CarButton.cpp client/rendering/interfaces/CarButton.h)

set(TEST_SOURCE_FILES
        tests/tests.cpp
		server/Game/CollisionsManager.cpp server/Game/CollisionsManager.h
		server/threads/GameThread.cpp server/threads/GameThread.h
		common/conc/BaseThread.cpp common/conc/BaseThread.h
		server/threads/PlayerThread.cpp server/threads/PlayerThread.h
		common/conc/SenderThread.cpp common/conc/SenderThread.h
		common/conc/ReceiverThread.cpp common/conc/ReceiverThread.h)

add_executable(Server server/main.cpp ${SERVER_SOURCE_FILES})
add_executable(Client client/main.cpp ${CLIENT_SOURCE_FILES})
add_executable(Test ${TEST_SOURCE_FILES} ${SERVER_SOURCE_FILES})

target_link_libraries(Server yaml-cpp pthread Box2D)
target_link_libraries(Client yaml-cpp pthread
		${SDL2_LIBRARY}
		${SDL2_IMAGE_LIBRARIES}
		${SDL2_TTF_LIBRARIES}
		)
target_link_libraries(Test yaml-cpp Box2D)
