set(__HEADERS
    ${L2AUTH_DIR}/include/l2auth/utils/CExceptionInit.h
    ${L2AUTH_DIR}/include/l2auth/utils/CoreDump.h
    ${L2AUTH_DIR}/include/l2auth/utils/SendMail.h
    ${L2AUTH_DIR}/include/l2auth/utils/Unused.h
    ${L2AUTH_DIR}/include/l2auth/utils/Utils.h
)

set(__SOURCES
    CExceptionInit.cpp
    CoreDump.cpp
    SendMail.cpp
    Utils.cpp
)

add_library(${PROJECT_NAME}_utils OBJECT ${__SOURCES} ${__HEADERS})
