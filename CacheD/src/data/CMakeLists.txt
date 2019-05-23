set(HEADERS
    ${CACHED_DIR}/include/cached/data/CReadFile.h
    ${CACHED_DIR}/include/cached/data/CReadItemData.h
    ${CACHED_DIR}/include/cached/data/CWatchList.h
    ${CACHED_DIR}/include/cached/data/CWatchObject.h
    ${CACHED_DIR}/include/cached/data/WatchType.h
    ${CACHED_DIR}/include/cached/data/CAddData.h
)

set(SOURCES
    CReadFile.cpp
    CReadItemData.cpp
    CWatchList.cpp
    CWatchObject.cpp
    CAddData.cpp
)

add_library(${PROJECT_NAME}_data STATIC ${SOURCES} ${HEADERS})
