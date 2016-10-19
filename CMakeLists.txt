project(minesweeper)
cmake_minimum_required(VERSION 2.8)

include(FindPkgConfig)

if(CMAKE_COMPILER_IS_GNUCXX)
	set(GCC_COMPILER_FLAGS " -std=c++11 -Wall -Werror") 
	set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COMPILER_FLAGS}")
endif()

pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

include_directories(${PROJECT_SOURCE_DIR} ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})

file(GLOB SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})

set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}")
set(RELEASE_DIR "release")

install(TARGETS ${PROJECT_NAME} DESTINATION ${RELEASE_DIR})
install(DIRECTORY ${PROJECT_SOURCE_DIR}/resources DESTINATION ${RELEASE_DIR})
