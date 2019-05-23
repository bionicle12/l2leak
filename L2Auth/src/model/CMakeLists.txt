set(__HEADERS
    ${L2AUTH_DIR}/include/l2auth/model/AccountDB.h
    ${L2AUTH_DIR}/include/l2auth/model/CIPAccessLimit.h
    ${L2AUTH_DIR}/include/l2auth/model/CServerKickList.h
    ${L2AUTH_DIR}/include/l2auth/model/CServerList.h
    ${L2AUTH_DIR}/include/l2auth/model/FrameType.h
    ${L2AUTH_DIR}/include/l2auth/model/LoginFailReason.h
    ${L2AUTH_DIR}/include/l2auth/model/LoginState.h
    ${L2AUTH_DIR}/include/l2auth/model/LoginUser.h
    ${L2AUTH_DIR}/include/l2auth/model/PlayFail.h
    ${L2AUTH_DIR}/include/l2auth/model/ServerKind.h
    ${L2AUTH_DIR}/include/l2auth/model/ServerPacketList.h
    ${L2AUTH_DIR}/include/l2auth/model/ServersProvider.h
    ${L2AUTH_DIR}/include/l2auth/model/SexAndCentury.h
    ${L2AUTH_DIR}/include/l2auth/model/WorldServer.h
)

set(__SOURCES
    AccountDB.cpp
    CIPAccessLimit.cpp
    CServerKickList.cpp
    CServerList.cpp
    LoginFailReason.cpp
    LoginState.cpp
    LoginUser.cpp
    PlayFail.cpp
    ServerKind.cpp
    ServerPacketList.cpp
    ServersProvider.cpp
    SexAndCentury.cpp
    WorldServer.cpp
)

add_library(${PROJECT_NAME}_model OBJECT ${__SOURCES} ${__HEADERS})
