cmake_minimum_required(VERSION 3.14)
project(Micromachines)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -std=c++0x)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2TTF REQUIRED)
find_package(SDL2_mixer REQUIRED)

include_directories(${SDL2_TTF_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(${SDL2_MIXER_INCLUDE_DIRS})
include_directories(${SDL2_INCLUDE_DIR})
include_directories(${PROJECT_BINARY_DIR})

include_directories(${PROJECT_SOURCE_DIR}/server)
include_directories(${PROJECT_SOURCE_DIR}/server/Game)
include_directories(${PROJECT_SOURCE_DIR}/server/Game/Box2D)
add_subdirectory(${PROJECT_SOURCE_DIR}/server/Game/Box2D)
include_directories(${PROJECT_SOURCE_DIR}/lua)
add_subdirectory(${PROJECT_SOURCE_DIR}/lua53)

set(SERVER_SOURCE_FILES
		server/config/Configuration.cpp
		common/infostream/Socket.cpp
		common/infostream/Protocol.cpp
		server/Game/entities/Entity.cpp
		server/Game/entities/RaceCar.cpp
		server/Game/entities/CarStats.cpp
		server/Game/GameWorld.cpp
		common/infostream/InfoBlock.cpp
		common/MapsLayer.cpp common/MapsLayer.h
		server/Game/CollisionsManager.cpp server/Game/CollisionsManager.h
		server/threads/PlayerThread.cpp
		server/Game/status_effects/StatusEffect.h
		server/Game/status_effects/SpeedStatusEffect.cpp server/Game/status_effects/SpeedStatusEffect.h
		common/Stopwatch.cpp common/Stopwatch.h
		server/threads/GameThread.cpp server/threads/GameThread.h
        server/threads/GamesManagerThread.cpp server/threads/GamesManagerThread.h
		common/conc/BaseThread.cpp common/conc/BaseThread.h
		common/conc/SenderThread.cpp common/conc/SenderThread.h
		server/Server.cpp server/Server.h
		server/Game/entities/OffRoad.cpp server/Game/entities/OffRoad.h
		server/mods/Plugin.h
		server/mods/PluginLoader.cpp server/mods/PluginLoader.h
		server/mods/PluginLibrary.cpp server/mods/PluginLibrary.h
		server/Game/status_effects/LapCooldown.h
		server/Game/entities/FinishingLine.cpp server/Game/entities/FinishingLine.h
		server/Game/entities/items/ItemBoost.cpp server/Game/entities/items/ItemBoost.h
		server/Game/entities/items/ItemHealth.cpp server/Game/entities/items/ItemHealth.h
		server/Game/entities/items/ItemRock.cpp server/Game/entities/items/ItemRock.h
		server/Game/entities/items/ItemMud.cpp server/Game/entities/items/ItemMud.h
		server/Game/entities/items/ItemCreator.cpp server/Game/entities/items/ItemCreator.h
		server/Game/status_effects/HealthEffect.cpp server/Game/status_effects/HealthEffect.h
		server/Game/status_effects/CallbackStatusEffect.cpp server/Game/status_effects/CallbackStatusEffect.h
		server/Game/entities/items/ItemMud.cpp server/Game/entities/items/ItemMud.h
		server/Game/entities/items/ItemOil.cpp server/Game/entities/items/ItemOil.h
		server/Game/status_effects/DragEffect.cpp server/Game/status_effects/DragEffect.h server/threads/ChoosingLobbyThread.cpp server/threads/ChoosingLobbyThread.h)

set(CLIENT_SOURCE_FILES
		common/infostream/Socket.cpp
		common/infostream/Protocol.cpp
		common/infostream/InfoBlock.cpp
        client/GameLoop.cpp
		client/rendering/SDLStarter.cpp
		client/Car.cpp client/Car.h
		client/communication/UserInput.cpp client/communication/UserInput.h
		client/communication/EventSender.cpp client/communication/EventSender.h
		client/communication/Receiver.cpp client/communication/Receiver.h
		client/rendering/TextureLoader.cpp client/rendering/TextureLoader.h
		client/rendering/SDLStarter.h
		common/Stopwatch.cpp
		client/rendering/LTexture.cpp client/rendering/LTexture.h
		common/conc/BaseThread.cpp common/conc/BaseThread.h
		common/conc/SenderThread.cpp common/conc/SenderThread.h
		common/MapsLayer.cpp common/MapsLayer.h
		client/tiles/Tile.cpp client/tiles/Tile.h
		client/rendering/TEXTURE_ERROR.cpp client/rendering/TEXTURE_ERROR.h
        client/GameLoop.cpp client/GameLoop.h
		client/rendering/GameRenderer.cpp client/rendering/GameRenderer.h
		client/GameMap.cpp client/GameMap.h
		client/Client.cpp
		client/tiles/TilesFactory.cpp client/tiles/TilesFactory.h
		client/rendering/interfaces/Button.cpp client/rendering/interfaces/Button.h
		client/rendering/interfaces/Menu.cpp client/rendering/interfaces/Menu.h
		client/Client.cpp client/Client.h
		client/rendering/interfaces/ConnectButton.cpp client/rendering/interfaces/ConnectButton.h
		client/rendering/interfaces/MapButton.cpp client/rendering/interfaces/MapButton.h
		client/rendering/interfaces/TextLabel.cpp client/rendering/interfaces/TextLabel.h
		client/rendering/interfaces/ButtonAnswer.cpp client/rendering/interfaces/ButtonAnswer.h
		client/rendering/interfaces/TextBox.cpp client/rendering/interfaces/TextBox.h
		client/sound_sys/SoundSystem.cpp client/sound_sys/SoundSystem.h
		client/rendering/interfaces/Explosion.cpp client/rendering/interfaces/Explosion.h
		client/rendering/interfaces/Animation.cpp client/rendering/interfaces/Animation.h
		client/rendering/interfaces/StainAnimation.cpp client/rendering/interfaces/StainAnimation.h
		client/Item.cpp client/Item.h
		client/ia/FakeClient.cpp client/ia/FakeClient.h
		client/rendering/recording/VideoRecorder.cpp client/rendering/recording/VideoRecorder.h
		client/rendering/recording/FormatContext.cpp client/rendering/recording/FormatContext.h
		client/rendering/recording/OutputFormat.cpp client/rendering/recording/OutputFormat.h
		client/rendering/recording/VideoWriter.cpp client/rendering/recording/VideoWriter.h)

#set(TEST_SOURCE_FILES
#        tests/tests.cpp
#		server/Game/CollisionsManager.cpp server/Game/CollisionsManager.h
#		server/threads/GameThread.cpp server/threads/GameThread.h
#		common/conc/BaseThread.cpp common/conc/BaseThread.h
#		server/threads/PlayerThread.cpp server/threads/PlayerThread.h
#		common/conc/SenderThread.cpp common/conc/SenderThread.h
#		)

set(LUA_SOURCE_FILES
		common/MapsLayer.cpp common/MapsLayer.h
		client/ia/lua/LuaWrapper.cpp client/ia/lua/LuaWrapper.h
        client/rendering/interfaces/LuaButton.cpp client/rendering/interfaces/LuaButton.h)

add_executable(Server server/main.cpp ${SERVER_SOURCE_FILES})
add_executable(Client client/main.cpp ${CLIENT_SOURCE_FILES} ${LUA_SOURCE_FILES})
# add_executable(LuaPlayer lua/main.cpp ${LUA_SOURCE_FILES})
#add_executable(Test ${TEST_SOURCE_FILES} ${SERVER_SOURCE_FILES})

target_link_libraries(Server yaml-cpp pthread Box2D ${CMAKE_DL_LIBS})
target_link_libraries(Client yaml-cpp pthread LuaLib
		${SDL2_LIBRARY}
		${SDL2_IMAGE_LIBRARIES}
		${SDL2TTF_LIBRARY}
		${SDL2_MIXER_LIBRARIES}
		avformat avcodec avutil swscale
		)
#target_link_libraries( LuaPlayer PUBLIC yaml-cpp LuaLib )
#target_link_libraries(Test yaml-cpp Box2D)
