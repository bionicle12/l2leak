set(__HEADERS
    ${L2LOGD_DIR}/include/l2logd/data/CReadFile.h
)

set(__SOURCES
    CReadFile.cpp
)

add_library(${PROJECT_NAME}_data OBJECT ${__SOURCES} ${__HEADERS})
