cmake_minimum_required(VERSION 2.6)

project(extract)

include(
	FcpptCMakeUtils)

include_directories(
	${CMAKE_SOURCE_DIR}/include)

# FIND BOOST
find_package(
	Boost 1.45.0 REQUIRED
	program_options
	system
)

include_directories(
	${Boost_INCLUDE_DIR})

link_directories(
	${Boost_LIBRARY_DIRS})

# FIND FCPPT
find_package(
	Fcppt
	REQUIRED)

include_directories(
	${Fcppt_INCLUDE_DIRS})

add_definitions(
	${Fcppt_DEFINITIONS})

SET(
	EXTRACT_FILES
	src/extract/bomb_directory.cpp
	src/extract/determine_mime_type.cpp
	src/extract/environment.cpp
	src/extract/file_sequence_to_file_tree.cpp
	src/extract/full_path.cpp
	src/extract/is_runnable.cpp
	src/extract/list_files.cpp
	src/extract/main.cpp
	src/extract/plugins/base.cpp
	src/extract/plugins/rar.cpp
	src/extract/plugins/tar.cpp
	src/extract/plugins/zip.cpp
	src/extract/process/call.cpp
	src/extract/process/call_safe.cpp
	src/extract/process/exec.cpp
	src/extract/unlines.cpp
)

add_executable(
	extract
	${EXTRACT_FILES})

TARGET_LINK_LIBRARIES(
	extract
	${Fcppt_core_LIBRARIES}
	${Fcppt_filesystem_LIBRARIES}
)

IF(NOT MSVC)
	target_link_libraries(extract ${Boost_LIBRARIES})
ENDIF()

install(TARGETS extract DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/)
