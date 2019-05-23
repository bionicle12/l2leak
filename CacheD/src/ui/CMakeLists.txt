set(HEADERS
    ${CACHED_DIR}/include/cached/ui/MainWindow.h
    ${CACHED_DIR}/include/cached/ui/resources.h
)

set(SOURCES
    ${RESOURCES}
    ${RC_FILE}
    MainWindow.cpp
)

add_library(${PROJECT_NAME}_ui STATIC ${SOURCES} ${HEADERS})
