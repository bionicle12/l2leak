set(HEADERS
    ${CACHED_DIR}/include/cached/threads/Threads.h
)

set(SOURCES
    Threads.cpp
)

add_library(${PROJECT_NAME}_threads STATIC ${SOURCES} ${HEADERS})
