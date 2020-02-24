// globals.h
// \ INFO
// INFO: module for globals 
// *******************************************************************

// interface file


#pragma once

//////////////////////////////////////////////////////////////////////
// Includes
//////////////////////////////////////////////////////////////////////

#include <stdio.h>		// printf, fgets
#include <string.h>		// strcmp, strlen
#include <stdlib.h>		// atoi
#include <time.h>		// localtime

#include "HPTypeDefs.h"


//////////////////////////////////////////////////////////////////////
// define
//////////////////////////////////////////////////////////////////////
#define OP_SUCCESS				0x00
#define OP_FAILURE				0x01

#define FILE_NOFILE				0x10
#define FILE_CORRUPT			0x11
#define FILE_STRUC_ERR			0x12

#define MAX_STR_BUF				256
#define MAX_STR_TAG				32			// tag name: [name]
#define MAX_STR_PARAM			32			// par val: par=val
#define MAX_STR_LINE			64


#define TAG_SYMB_OPEN			'['
#define TAG_SYMB_CLOSE			']'


//////////////////////////////////////////////////////////////////////
// extern
//////////////////////////////////////////////////////////////////////
extern struct stHPFileGlobals m_stGlobals;
extern char m_strWastName[32];

// functions
BYTE GetStrTag(char * strParse, char * strOutput, char chOpenSymbol, char chCloseSymbol);
BYTE Read_config(stHPFileGlobals * var_stGlobals);