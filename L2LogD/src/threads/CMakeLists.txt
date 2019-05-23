set(__HEADERS
    ${L2LOGD_DIR}/include/l2logd/threads/Threads.h
)

set(__SOURCES
    Threads.cpp
)

add_library(${PROJECT_NAME}_threads OBJECT ${__SOURCES} ${__HEADERS})
