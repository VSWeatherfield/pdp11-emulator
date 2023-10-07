project(PdpEmulatorTests)

set(SOURCES PdpEmulator_tests.c)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE Common Core)

add_test(Test_1, "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}")