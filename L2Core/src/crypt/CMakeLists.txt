set(__HEADERS
    ${L2CORE_DIR}/include/l2core/crypt/DummyCrypt.h
	${L2CORE_DIR}/include/l2core/crypt/XorCrypt.h
)

set(__SOURCES
	DummyCrypt.cpp
    XorCrypt.cpp
)

add_library(${PROJECT_NAME}_crypt STATIC ${__SOURCES} ${__HEADERS})
