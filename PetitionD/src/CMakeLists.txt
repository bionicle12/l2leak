set(__SOURCES
    AuthConn.cpp
    ClientConn.cpp
    clientsocket.cpp
    Log.cpp
    md5.cpp
    petitionconn.cpp
    PetitionService.cpp
    StdAfx.cpp
    tlvsocket.cpp
    UserDB.cpp
    WorldEmu.cpp
    WorldEmuDlg.cpp
)

set(RC_FILE WorldEmu.rc)

set(RESOURCES
    res/WorldEmu.ico
)

set(__HEADERS
    ${PETITIOND_DIR}/include/petitiond/AuthConn.h
    ${PETITIOND_DIR}/include/petitiond/ClientConn.h
    ${PETITIOND_DIR}/include/petitiond/clientsocket.h
    ${PETITIOND_DIR}/include/petitiond/Log.h
    ${PETITIOND_DIR}/include/petitiond/md5.h
    ${PETITIOND_DIR}/include/petitiond/petitionconn.h
    ${PETITIOND_DIR}/include/petitiond/PetitionService.h
    ${PETITIOND_DIR}/include/petitiond/resource.h
    ${PETITIOND_DIR}/include/petitiond/stdafx.h
    ${PETITIOND_DIR}/include/petitiond/tlvsocket.h
    ${PETITIOND_DIR}/include/petitiond/UserDB.h
    ${PETITIOND_DIR}/include/petitiond/WorldEmu.h
    ${PETITIOND_DIR}/include/petitiond/WorldEmuDlg.h
)

add_library(${PROJECT_NAME}_main OBJECT ${__SOURCES} ${__HEADERS} ${RC_FILE} ${RESOURCES})
