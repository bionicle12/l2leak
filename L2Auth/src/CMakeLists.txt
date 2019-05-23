add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/config)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/crypt)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/db)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/logger)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/model)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/network)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/threads)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ui)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/utils)

set(__HEADERS
    ${L2AUTH_DIR}/include/l2auth/AppInstance.h
    ${L2AUTH_DIR}/include/l2auth/CIOObject.h
)

set(__SOURCES
    CIOObject.cpp
    main.cpp
)

add_library(${PROJECT_NAME}_main OBJECT ${__SOURCES} ${__HEADERS})

