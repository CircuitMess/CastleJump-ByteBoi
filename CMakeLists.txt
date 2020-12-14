cmake_minimum_required(VERSION 3.15)
project(CastleJump) # Project name - has to be same as directory name
set(PORT COM4) # Upload port
set(DEVICE cm:esp8266:nibble) # Arduino device FQBN
set(CMAKE_CXX_STANDARD 11)

set(ROOT ${CMAKE_SOURCE_DIR})
if(WIN32 OR CYGWIN)
    set(Arduino15 $ENV{APPDATA}/../Local/Arduino15)
    set(ArduinoLibs $ENV{USERPROFILE}/Documents/Arduino/libraries)

    string(REPLACE "\\" "/" Arduino15 ${Arduino15})
    string(REPLACE "\\" "/" ArduinoLibs ${ArduinoLibs})

    if(CYGWIN)
        string(REGEX REPLACE "^([A-Za-z]):" "/cygdrive/\\1" Arduino15 ${Arduino15})
        string(REGEX REPLACE "^([A-Za-z]):" "/cygdrive/\\1" ArduinoLibs ${ArduinoLibs})
        string(REGEX REPLACE "^/cygdrive/([A-Za-z])" "\\1:/" ROOT ${ROOT})
    endif()
else()
    set(Arduino15 ~/.arduino15)
    set(ArduinoLibs ~/Arduino/libraries)
endif()

include_directories(${Arduino15}/packages/cm/hardware/esp8266/1.0.0/cores/esp8266)
include_directories(${Arduino15}/packages/cm/hardware/esp8266/1.0.0/libraries/Nibble/src)
include_directories(${Arduino15}/packages/cm/hardware/esp8266/1.0.0/libraries/CircuitOS/src)
include_directories(${Arduino15}/packages/cm/hardware/esp8266/1.0.0/libraries/TFT_eSPI)
include_directories(${Arduino15}/packages/cm/hardware/esp8266/1.0.0/libraries/TFT_eSPI/Extensions)
include_directories(${Arduino15}/packages/cm/hardware/esp8266/1.0.0/libraries/FS)
include_directories(${Arduino15}/packages/cm/hardware/esp8266/1.0.0/cores/esp8266/FS)
include_directories(${Arduino15}/packages/cm/hardware/esp8266/1.0.0/libraries/LittleFS/src)



# Source directories
AUX_SOURCE_DIRECTORY(src SOURCES)

# Defines
add_definitions(-DDEBUG)
add_definitions(-DESP32)



set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(BUILD ${ROOT}/build)

SET_SOURCE_FILES_PROPERTIES(${CMAKE_PROJECT_NAME}.ino PROPERTIES LANGUAGE CXX)

add_custom_command(OUTPUT ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_PROJECT_NAME}.elf ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_PROJECT_NAME}.bin ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_PROJECT_NAME}.partitions.bin
        COMMAND arduino-cli compile --fqbn ${DEVICE} -o ${BUILD}/${CMAKE_PROJECT_NAME}.bin ${CMAKE_PROJECT_NAME}.ino
        DEPENDS ${CMAKE_PROJECT_NAME}.ino ${SOURCES}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_custom_target(CMBuild
        SOURCES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_PROJECT_NAME}.elf)

add_custom_target(CMUpload ALL
        COMMAND arduino-cli upload --fqbn ${DEVICE} -p ${PORT} -i ${BUILD}/${CMAKE_PROJECT_NAME}.bin
        DEPENDS CMBuild
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(${CMAKE_PROJECT_NAME}.bin ${CMAKE_PROJECT_NAME}.ino ${SOURCES} src/CastleJump.cpp src/CastleJump.h src/State.cpp src/State.h src/GameState.cpp src/GameState.h src/GameOverState.cpp src/GameOverState.h src/Menu.h src/Menu.cpp src/ShowHighscoreState.cpp src/ShowHighscoreState.h)

