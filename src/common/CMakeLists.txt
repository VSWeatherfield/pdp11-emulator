project(Common)

include_directories(${PROJECT_SOURCE_DIR})

set(HEADERS
    ${PROJECT_SOURCE_DIR}/constants/ArgConstants.h
    ${PROJECT_SOURCE_DIR}/constants/EmulatorConstants.h
    ${PROJECT_SOURCE_DIR}/constants/MemConstants.h
    ${PROJECT_SOURCE_DIR}/types/ArgumentParserType.h
    ${PROJECT_SOURCE_DIR}/types/ArgumentType.h
    ${PROJECT_SOURCE_DIR}/types/CommandType.h
    ${PROJECT_SOURCE_DIR}/types/ModeType.h
    ${PROJECT_SOURCE_DIR}/types/TracerType.h)

add_library(${PROJECT_NAME} STATIC ${HEADERS})

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE C)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})