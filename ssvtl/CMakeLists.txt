set(HEADERS
        ${CMAKE_CURRENT_LIST_DIR}/include/stack.hpp
        )

set (SOURCES
        ${CMAKE_CURRENT_LIST_DIR}/src/stack.cpp
        )

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC "include")

set_target_properties(${PROJECT_NAME}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin/debug"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin/release"
        RUNTIME_OUTPUT_NAME_DEBUG "${PROJECT_NAME}_debug"

        )

