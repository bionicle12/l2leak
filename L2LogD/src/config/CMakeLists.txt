set(__HEADERS
    ${L2LOGD_DIR}/include/l2logd/config/Config.h
)

set(__SOURCES
    Config.cpp
)

add_library(${PROJECT_NAME}_config OBJECT ${__SOURCES} ${__HEADERS})
