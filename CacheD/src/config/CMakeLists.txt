set(HEADERS
    ${CACHED_DIR}/include/cached/config/Config.h
)

set(SOURCES
    Config.cpp
)

add_library(${PROJECT_NAME}_config STATIC ${SOURCES} ${HEADERS})
