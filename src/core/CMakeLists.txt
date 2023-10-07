project(Core)

include_directories(${PROJECT_SOURCE_DIR})

set(HEADERS
        ${PROJECT_SOURCE_DIR}/pdp_emulator/PdpEmulator.h
        ${PROJECT_SOURCE_DIR}/memory/Memory.h
        ${PROJECT_SOURCE_DIR}/addressing_modes/AddressingModes.h
        ${PROJECT_SOURCE_DIR}/argument_parsers/ArgumentParsers.h
        ${PROJECT_SOURCE_DIR}/commands/Commands.h
        ${PROJECT_SOURCE_DIR}/process_state/ProcessState.h
        ${PROJECT_SOURCE_DIR}/tracer/Tracer.h
        ${PROJECT_SOURCE_DIR}/configs/StartupConfig.h)

set(SOURCES
        ${PROJECT_SOURCE_DIR}/pdp_emulator/PdpEmulator.c
        ${PROJECT_SOURCE_DIR}/memory/Memory.c
        ${PROJECT_SOURCE_DIR}/addressing_modes/AddressingModes.c
        ${PROJECT_SOURCE_DIR}/argument_parsers/ArgumentParsers.c
        ${PROJECT_SOURCE_DIR}/commands/Commands.c
        ${PROJECT_SOURCE_DIR}/process_state/ProcessState.c
        ${PROJECT_SOURCE_DIR}/tracer/Tracer.c
        ${PROJECT_SOURCE_DIR}/configs/StartupConfig.c)

add_library(${PROJECT_NAME} SHARED ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC Common)