CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

PROJECT(extract)

SET(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS ON)

IF(${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
	message(FATAL_ERROR "In-source builds are not permitted. Make a separate folder for building:\nmkdir build; cd build; cmake ..\nBefore that, remove the files that cmake just created:\nrm -rf CMakeCache.txt CMakeFiles")
ENDIF()

INCLUDE(FindPkgConfig)

SET(CMAKE_VERBOSE_MAKEFILE ON)

SET (Boost_ADDITIONAL_VERSIONS "1.41" "1.41.0" "1.42" "1.42.0" "1.43" "1.43.0" "1.44" "1.44.0")

IF(MSVC)
	SET(Boost_USE_STATIC_LIBS ON)
ENDIF()

FIND_PACKAGE(
	Boost 1.41.0 COMPONENTS
	program_options
	system
)

INCLUDE_DIRECTORIES(SYSTEM ${Boost_INCLUDE_DIR})

LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

IF (${CMAKE_COMPILER_IS_GNUCXX})
	ADD_DEFINITIONS("-fvisibility=hidden -ansi -pedantic-errors -Wall"
	"-Wextra -Wconversion -Wfloat-equal -Wredundant-decls"
	"-Wstrict-null-sentinel -Winit-self -Woverloaded-virtual"
	"-Wold-style-cast -Wnon-virtual-dtor -Wctor-dtor-privacy -Wsign-promo"
	"-Wstrict-aliasing=1 -Wmissing-declarations -Wno-long-long")

	ADD_DEFINITIONS(-D BOOST_FILESYSTEM_NO_DEPRECATED)
ELSEIF (MSVC)
	ADD_DEFINITIONS ("/W3 /wd4512 /wd4355 /wd4800 /wd4996 /wd4714 /EHa /D_BIND_TO_CURRENT_VCLIBS_VERSION=1")
ENDIF ()

FILE(GLOB basefiles *.cpp)

FILE(GLOB_RECURSE collectionsfiles
	process/*.cpp
	plugins/*.cpp)

ADD_EXECUTABLE(extract ${basefiles} ${collectionsfiles})
TARGET_LINK_LIBRARIES(extract fcppt)

IF(NOT MSVC)
	TARGET_LINK_LIBRARIES(extract ${Boost_LIBRARIES})
ENDIF()

INSTALL(TARGETS extract DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/)
