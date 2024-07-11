# cmake -DGTK_CSD=1 -DGSK_RENDERER=CAIRO -G Ninja ..
cmake_minimum_required(VERSION 3.20)

project(gtkmm4 VERSION 1.0.0.1 DESCRIPTION "Programa prueba de gtkmm4" LANGUAGES CXX)

if(NOT DEFINED GSK_RENDERER)
	set(GSK_RENDERER "CAIRO")
endif()

if(NOT DEFINED GTK_CSD)
	set(GTK_CSD "0")
endif()

message(STATUS "GSK_RENDERER: ${GSK_RENDERER}")
message(STATUS "GTK_CSD: ${GTK_CSD}")

set(BIN_NAME "${PROJECT_NAME}-${PROJECT_VERSION_MAJOR}-${PROJECT_VERSION_MINOR}")

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM4 REQUIRED gtkmm-4.0)

add_executable(${BIN_NAME})

add_subdirectory(src)
# add_subdirectory(data)

target_compile_definitions(${BIN_NAME} PRIVATE
	PROGRAM_NAME="${PROJECT_NAME}"
	PROGRAM_TITLE="${PROJECT_NAME} ${PROJECT_VERSION}"
	PROGRAM_APPID="${PROJECT_NAME}.aullidolunar.${BIN_NAME}"
	PROGRAM_GSK_RENDERER="${GSK_RENDERER}"
	PROGRAM_GTK_CSD="${GTK_CSD}"
)
target_compile_options(${BIN_NAME} PRIVATE ${GTKMM4_CFLAGS_OTHER})
target_include_directories(${BIN_NAME} PRIVATE ${GTKMM4_INCLUDE_DIRS})
target_link_directories(${BIN_NAME} PRIVATE ${GTKMM4_LIBRARY_DIRS})
target_link_libraries(${BIN_NAME} PRIVATE ${GTKMM4_LIBRARIES})

add_custom_target(run
    COMMAND ${BIN_NAME}
    DEPENDS ${BIN_NAME}
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

cmake_path(GET PROJECT_SOURCE_DIR PARENT_PATH MY_PROJECT_DIR)
cmake_path(GET PROJECT_SOURCE_DIR STEM MY_PROJECT_NAME)

add_custom_target(dist
	WORKING_DIRECTORY "${MY_PROJECT_DIR}"
	COMMAND ${CMAKE_COMMAND} -E tar cvf "${CMAKE_CURRENT_BINARY_DIR}/${BIN_NAME}.7z" --format=7zip "${MY_PROJECT_NAME}/src" "${MY_PROJECT_NAME}/CMakeLists.txt"
)

