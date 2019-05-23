set(HEADERS
    ${L2CORE_DIR}/include/l2core/geometry/Math.h
    ${L2CORE_DIR}/include/l2core/geometry/FVector.h
    ${L2CORE_DIR}/include/l2core/geometry/CTerritory.h
    ${L2CORE_DIR}/include/l2core/geometry/SpawnPos.h
    ${L2CORE_DIR}/include/l2core/geometry/SpawnPositions.h
    ${L2CORE_DIR}/include/l2core/geometry/WayPoints.h
)

set(SOURCES
    Math.cpp
    FVector.cpp
    CTerritory.cpp
    SpawnPos.cpp
)

add_library(l2npc_${PROJECT_NAME}_geometry STATIC ${SOURCES} ${HEADERS})
target_compile_definitions(l2npc_${PROJECT_NAME}_geometry PRIVATE -DL2NPC)
