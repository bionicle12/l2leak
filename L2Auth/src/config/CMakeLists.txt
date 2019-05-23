set(__HEADERS
    ${L2AUTH_DIR}/include/l2auth/config/CIPList.h
    ${L2AUTH_DIR}/include/l2auth/config/Config.h
)

set(__SOURCES
    CIPList.cpp
    Config.cpp
)
add_library(${PROJECT_NAME}_config OBJECT ${__SOURCES} ${__HEADERS})
