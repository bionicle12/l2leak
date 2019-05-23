project(CachedScript)

cmake_minimum_required(VERSION 3.5)

set(LINEAGE_2_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)

set(SCRIPTS
    Itemdata.txt
    skilldata.txt
    npcdata.txt
    gmskilldata-e.txt
    itemcache-e.txt
    Itemname-e.txt
    npccache-e.txt
    npcname-e.txt
    questcomp-e.txt
    QuestName-e.txt
    skillname-e.txt
    watch_list.txt
)

add_custom_target(${PROJECT_NAME} SOURCES  ${SCRIPTS})

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "CachedScript")

install(DIRECTORY "./" DESTINATION "${CMAKE_BINARY_DIR}/install/CachedScript")
