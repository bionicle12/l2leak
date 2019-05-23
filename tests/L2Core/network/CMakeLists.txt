set(HEADERS
)

set(SOURCES
    main.cpp
    PacketUtilsTests.cpp
)

add_executable(
    ${PROJECT_NAME}_network
    ${SOURCES} ${HEADERS}
    )

target_link_libraries(${PROJECT_NAME}_network
    User32.lib
    Gdi32.lib    # Painting
    Ws2_32.lib   # Sockets
    Advapi32.lib # Regestry
    odbc32.lib   # SQL
    Mswsock.lib  # GetAcceptExSockaddrs
    Dbghelp.lib  # Debug symbol options
    pdh.lib      # Performance
    Psapi.lib    # Process Status API (GetProcessMemoryInfo)

    gtest
    gmock
    L2NPC_config
    L2Core_crypt
    l2npc_L2Core
    l2npc_L2Core_utils
    l2npc_L2Core_utils_dbg
    l2npc_L2Core_threads
    l2npc_L2Core_network
    l2npc_L2Core_network_packets
    l2npc_L2Core_logger
    l2npc_L2Core_memory
    )
