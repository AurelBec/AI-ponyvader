cmake_minimum_required(VERSION 3.3)

project(Ponynvaders)
set(EXECUTABLE_NAME "ponyvader")
set(EXECUTABLE_OUTPUT_PATH ../${CMAKE_BUILD_TYPE})
add_definitions(-std=c++0x -g -Wall -Wold-style-cast -Werror -Wfatal-errors -O2)

file(
	GLOB_RECURSE
	SRCS

	src/*.cpp
)

add_executable(
	${EXECUTABLE_NAME}
	${SRCS}
)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/" ${CMAKE_MODULE_PATH})
find_package(Threads)
find_package(SFML 2.3.2 COMPONENTS system window graphics network audio REQUIRED)
target_link_libraries(${EXECUTABLE_NAME} ${CMAKE_THREAD_LIBS_INIT} ${SFML_LIBRARIES})
