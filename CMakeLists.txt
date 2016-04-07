cmake_minimum_required (VERSION 2.6)
project (Experiments)

set(CMAKE_CXX_STANDARD 14)


set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH}) #SFML Package doesn't tell CMAKE how to find the lib, so FindSFML.cmake is required


find_package(SFML 2 REQUIRED system window graphics)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
include_directories(${SFML_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS})



add_executable(
	Programme
	main.cpp
	easylogging++.h
	Grille.cpp
	Grille.h

)

target_link_libraries(Programme ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${SFML_LIBRARIES})