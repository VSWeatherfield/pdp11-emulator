project(Log)

set(LOG_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/log/src/log.c")
set(LOG_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/log/src/log.h")

set(LOG_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/log/src/")

add_library(${PROJECT_NAME} STATIC ${LOG_SOURCES} ${LOG_HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC ${LOG_INCLUDES})