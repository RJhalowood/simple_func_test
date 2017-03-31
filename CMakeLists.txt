project(func_test)

cmake_minimum_required(VERSION 2.8)

file(GLOB SRC_FILE_LIST RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "*.c")

foreach(SRC_FILE ${SRC_FILE_LIST})
	GET_FILENAME_COMPONENT(SRC_FILE_NAME ${SRC_FILE} NAME_WE)
	add_executable(${SRC_FILE_NAME} ${SRC_FILE})
endforeach(SRC_FILE)
