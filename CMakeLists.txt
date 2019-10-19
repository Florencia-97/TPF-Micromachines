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
	server/configuration.cpp
)

add_executable(Server server/main.cpp ${SERVER_SOURCE_FILES})

target_link_libraries(Server yaml-cpp)
