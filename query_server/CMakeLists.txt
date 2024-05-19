cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_FLAGS -pthread)
set(CMAKE_BUILD_TYPE Debug)
#add_compile_definitions(NODEBUG)
add_definitions(-std=c++17)

project(extraction)

function(px4_add_library target)
	message(STATUS "print-> ${target}")
	message(STATUS "print-> ${ARGN}")
	add_library(${target} EXCLUDE_FROM_ALL ${ARGN})

	target_compile_definitions(${target} PRIVATE MODULE_NAME="${target}")

	target_link_libraries(${target} PRIVATE prebuild_targets)

	#set_property(GLOBAL APPEND PROPERTY PX4_MODULE_PATHS ${CMAKE_CURRENT_SOURCE_DIR})
	
endfunction()

include_directories(include)

add_library(prebuild_targets INTERFACE)


add_subdirectory(lib)

FILE(GLOB EkfSrc lib/ecl_ekf/*.cpp)
FILE(GLOB WorldMagSrc lib/world_magnetic_model/*.cpp)
FILE(GLOB GeoSrc lib/geo/*.cpp)
FILE(GLOB InterfaceSrc lib/interface/*.cpp)

add_library(prebuild_dependencies STATIC
	lib/test/test.cpp
	${GeoSrc}
	${WorldMagSrc}
	${EkfSrc}
	${InterfaceSrc}
)
add_dependencies(prebuild_dependencies prebuild_targets)

message(STATUS "print-> ${PROJECT_SOURCE_DIR}")
target_include_directories(prebuild_dependencies PUBLIC ${PROJECT_SOURCE_DIR}/lib)


add_executable(extraction_bin
	main.cpp
	include/visibility.h
)
add_dependencies(extraction_bin prebuild_targets)

add_dependencies(extraction_bin prebuild_dependencies)

target_link_libraries(extraction_bin
	PRIVATE
	prebuild_targets
	prebuild_dependencies)
