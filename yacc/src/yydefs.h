#ifndef YYDEFS_H
#define YYDEFS_H

/************************************************************
yydefs.h
This file can be freely modified for the generation of
custom code.

Copyright (c) 1999-2003 Bumble-Bee Software Ltd.
************************************************************/

// defines
#pragma warning(push)
#pragma warning(disable: 4103)
#include <yytdefs.h>
#pragma warning(pop)

// user defines
#if defined(YYTUDEFS) || defined(YYUDEFS)
#include <yytudefs.h>
#endif

// user defines
#if defined(YYBUDEFS) || defined(YYUDEFS)
#include <yybudefs.h>
#endif

// defines
#pragma warning(push)
#pragma warning(disable: 4103)
#include <yybdefs.h>
#pragma warning(pop)

#endif
