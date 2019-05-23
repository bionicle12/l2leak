set(RESOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/icon.ico
    ${CMAKE_CURRENT_SOURCE_DIR}/icon_16x16.ico
)

set(RC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/resources.rc)

set(__HEADERS
    ${L2AUTH_DIR}/include/l2auth/ui/CLog.h
    ${L2AUTH_DIR}/include/l2auth/ui/CReporter.h
    ${L2AUTH_DIR}/include/l2auth/ui/MainWindow.h
    ${L2AUTH_DIR}/include/l2auth/ui/resources.h
)

set(__SOURCES
    ${RESOURCES}
    ${RC_FILE}
    CLog.cpp
    CReporter.cpp
    MainWindow.cpp
)

add_library(${PROJECT_NAME}_ui OBJECT ${__SOURCES} ${__HEADERS} ${RC_FILE} ${RESOURCES})
