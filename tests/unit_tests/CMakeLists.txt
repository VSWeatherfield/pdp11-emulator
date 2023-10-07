project(MemoryTests)

set(SOURCES Memory_tests.c)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE Common Core unity)

add_test(Test_0, "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}")