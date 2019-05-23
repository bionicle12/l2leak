set(RESOURCES
    Icon_1.ico
    Icon_2.ico
)

set(RC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/resources.rc)

set(__HEADERS
    ${L2LOGD_DIR}/include/l2logd/ui/MainWindow.h
    ${L2LOGD_DIR}/include/l2logd/ui/resources.h
)

set(__SOURCES
    ${RESOURCES}
    ${RC_FILE}
    MainWindow.cpp
)

add_library(${PROJECT_NAME}_ui OBJECT ${__SOURCES} ${__HEADERS} ${RC_FILE} ${RESOURCES})
