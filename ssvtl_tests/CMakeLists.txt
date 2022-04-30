add_executable(${PROJECT_NAME}_test main.cpp)

set(GTEST_DIR lib/gtest-1.11.0)

add_subdirectory(${GTEST_DIR})


include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME}_test gtest gtest_main)


set_target_properties(${PROJECT_NAME}_test
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin/debug"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin/release"
        RUNTIME_OUTPUT_NAME_DEBUG "${PROJECT_NAME}_test_debug"
        )
