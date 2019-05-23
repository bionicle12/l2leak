project(Lineage2 CXX)

cmake_minimum_required(VERSION 3.5)

###############################################################################
# Turn ON ability to organize projects into folders/filters (for MSVC, xCode)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(USE_HTML "Include html files" OFF)
option(TESTS "Enable testing sub-projects" OFF)

add_subdirectory(yacc)
add_subdirectory(L2Core)
add_subdirectory(L2Auth)
add_subdirectory(L2LogD)
add_subdirectory(L2NPC)
add_subdirectory(CacheD)
add_subdirectory(DBScript)
add_subdirectory(CachedScript)
add_subdirectory(PetitionD)

if(USE_HTML)
    message(STATUS "USE_HTML set to ${USE_HTML}. Project generation might take some time")
    add_subdirectory(html)
else()
    message(STATUS "USE_HTML unset. To have it included in project, use -DUSE_HTML=ON during cmake")
endif()

if(TESTS)
    message(STATUS "TESTS set to ${TESTS}. Unit tests will be generated")
    add_subdirectory(tests)
else()
    message(STATUS "TESTS unset. To have it included in project, use -DTESTS=ON during cmake")
endif()

