project(yacc CXX)
cmake_minimum_required(VERSION 3.5)

set(SOURCES
    ./src/yydefs.h
    ./src/yywcback.cpp
    ./src/yywccpya.cpp
    ./src/yywcdci.cpp
    ./src/yywcdcic.cpp
    ./src/yywcdela.cpp
    ./src/yywcdisc.cpp
    ./src/yywcdop.cpp
    ./src/yywcdpop.cpp
    ./src/yywcecho.cpp
    ./src/yywcgetc.cpp
    ./src/yywcgtok.cpp
    ./src/yywcinp.cpp
    ./src/yywclcln.cpp
    ./src/yywclcon.cpp
    ./src/yywclcre.cpp
    ./src/yywcldbg.cpp
    ./src/yywcldes.cpp
    ./src/yywclerr.cpp
    ./src/yywcless.cpp
    ./src/yywclex.cpp
    ./src/yywclexc.cpp
    ./src/yywclvts.cpp
    ./src/yywclvtv.cpp
    ./src/yywcnewa.cpp
    ./src/yywcoutp.cpp
    ./src/yywcpar.cpp
    ./src/yywcpcln.cpp
    ./src/yywcpcon.cpp
    ./src/yywcpcre.cpp
    ./src/yywcpdbg.cpp
    ./src/yywcpdes.cpp
    ./src/yywcperr.cpp
    ./src/yywcpop.cpp
    ./src/yywcpp.cpp
    ./src/yywcpush.cpp
    ./src/yywcres.cpp
    ./src/yywcserr.cpp
    ./src/yywcsin.cpp
    ./src/yywcsofw.cpp
    ./src/yywcsskp.cpp
    ./src/yywcsssz.cpp
    ./src/yywcstsz.cpp
    ./src/yywcstv.cpp
    ./src/yywcsup.cpp
    ./src/yywcsusz.cpp
    ./src/yywctofw.cpp
    ./src/yywcucin.cpp
    ./src/yywcunp.cpp
    ./src/yywcuofw.cpp
    ./src/yywcvtlv.cpp
    ./src/yywcvts.cpp
    ./src/yywcwipe.cpp
    ./src/yywcwrap.cpp
    ./src/yywcwrk.cpp
    ./src/yywcwrkc.cpp
)

set(HEADERS
    include/yybdefs.h
    include/yyglobal.h
    include/yytdefs.h
    include/yywclex.h
    include/yywcpars.h
)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME}
  PRIVATE ./include
  PRIVATE ./src)
