project(DBScript)

cmake_minimum_required(VERSION 3.5)

set(LINEAGE_2_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)

set(SCRIPTS
    lin2log.sql #2004_4_16_lin2log.sql
    lin2report.sql #2004_4_16_lin2report.sql
    lin2comm.sql #lin2comm_new.sql
    lin2db_update.sql
    lin2user.sql
    lin2world.sql #lin2world_20040609_all.sql
    ReleaseAuthDBSchema.sql
)

add_custom_target(${PROJECT_NAME} SOURCES  ${SCRIPTS})

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "DBScript")

install(FILES ${SCRIPTS} DESTINATION "${CMAKE_BINARY_DIR}/install/DBScript")
