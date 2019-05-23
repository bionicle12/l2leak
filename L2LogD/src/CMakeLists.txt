add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/config)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/data)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/network)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/threads)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ui)

set(__SOURCES
    main.cpp
)

add_library(${PROJECT_NAME}_main OBJECT ${__SOURCES} ${__HEADERS})
