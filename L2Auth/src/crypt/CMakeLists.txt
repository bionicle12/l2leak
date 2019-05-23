set(__HEADERS
    ${L2AUTH_DIR}/include/l2auth/crypt/Blowfish.h
    ${L2AUTH_DIR}/include/l2auth/crypt/DesBackEnd.h
    ${L2AUTH_DIR}/include/l2auth/crypt/DesFrontEnd.h
    ${L2AUTH_DIR}/include/l2auth/crypt/DesNewCrypt.h
    ${L2AUTH_DIR}/include/l2auth/crypt/OldCrypt.h
    ${L2AUTH_DIR}/include/l2auth/crypt/PwdCrypt.h
)

set(__SOURCES
    Blowfish.cpp
    DesBackEnd.cpp
    DesFrontEnd_foreign.cpp
    DesNewCrypt.cpp
    OldCrypt.cpp
    PwdCrypt.cpp
)

add_library(${PROJECT_NAME}_crypt OBJECT ${__SOURCES} ${__HEADERS})
