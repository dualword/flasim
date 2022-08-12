# cmake for tes, ottona, 2022-03-09


cmake_minimum_required(VERSION 3.10)

set(FS_TARGET flasim)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/bin")
set(LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
set(FS_EXT_DIR "${CMAKE_CURRENT_LIST_DIR}/ext")

set(FS_SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/src")

#caudio stuff
option(CAUDIO_STATIC on)
set(CAUDIO_TARGET cAudio)
set(CAUDIO_DIR ${FS_EXT_DIR}/cAudio)
set(CAUDIO_INC_DIR ${FS_EXT_DIR}/cAudio/cAudio/include)
add_subdirectory(${CAUDIO_DIR} EXCLUDE_FROM_ALL)


#irrlicht stuff
set(IRRLICHT_INC_DIR /usr/include/irrlicht)
set(IRRLICHT_TARGET Irrlicht)

project(${FS_TARGET})

add_executable(flasim
    ${FS_SRC_DIR}/Aircraft.cpp
    ${FS_SRC_DIR}/Aircraft.hpp
    ${FS_SRC_DIR}/Dispatcher.cpp
    ${FS_SRC_DIR}/Dispatcher.hpp
    ${FS_SRC_DIR}/FireUnit.cpp
    ${FS_SRC_DIR}/FireUnit.hpp
    ${FS_SRC_DIR}/FlaSimApp.cpp
    ${FS_SRC_DIR}/FlaSimApp.hpp
    ${FS_SRC_DIR}/Globals.cpp
    ${FS_SRC_DIR}/Globals.hpp
    ${FS_SRC_DIR}/main.cpp
    ${FS_SRC_DIR}/TurretCamAnimator.cpp
    ${FS_SRC_DIR}/TurretCamAnimator.hpp
    )

target_include_directories(${FS_TARGET} PRIVATE ${IRRLICHT_INC_DIR} ${CAUDIO_INC_DIR} ${CMAKE_BINARY_DIR}/include) #last is needed for caudio

if(UNIX)    # relocatable linking for unixoids
    set_target_properties(flasim PROPERTIES LINK_FLAGS "-Wl,-rpath,$ORIGIN/")
endif()

target_link_libraries(${FS_TARGET} ${CAUDIO_TARGET} ${IRRLICHT_TARGET})

