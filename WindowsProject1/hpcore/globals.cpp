// globals.cpp
// INFO: module for globals 
// *******************************************************************

// implementation file

#define _CRT_SECURE_NO_WARNINGS


//////////////////////////////////////////////////////////////////////
// Includes
//////////////////////////////////////////////////////////////////////
// precompile
#include "../project.h"
#include "globals.h"


// ===================================================================
// module body
// ===================================================================
// module globals
struct stHPFileGlobals m_stGlobals;

// This Universe Name
char m_strWastName[32];


//////////////////////////////////////////////////////////////////////
// service PROCs
//////////////////////////////////////////////////////////////////////
// cut label header from string line
BYTE GetStrTag(char * strParse, char * strOutput, char chOpenSymbol, char chCloseSymbol)
{
	// proc symbols
	// NOTE:
	// cycle proc in next modes:
	// act = 0: cycle end proc   
	// act = 1: try find Open symbol
	// act = 2: try find Close symbol
	char strTag[MAX_STR_TAG];

	BYTE k = 0;
	BYTE ucFstPos = 0;
	BYTE ucEndPos = 0;
	char c;

	BYTE act = 1;
	while (act != 0)
	{
		c = strParse[k];

		// > Check End of Cycle /EOS 
		if (c == '\0')
		{
			// [EOS]

			// define the Reason
			if (act == 1)
			{
				// [NO OPEN SYMBOL FOUND]

				act = 0;

				strcpy(strOutput, "NULL_START");
				return OP_FAILURE;
			}
			else
			{
				if (act == 2)
				{
					// [NO CLOSE SYMBOL FOUND]

					act = 0;

					strcpy(strOutput, "NULL_END");
					return OP_FAILURE;
				}
				else
				{
					// [NORMAL OPERATION]

					// NOP: Valid String returned
				}
			}
		}// > Check End of Cycle /EOS 

		 // > Proceed String
		if (act == 1)
		{
			// [proc find Open symbol]

			if (c == chOpenSymbol)
			{
				// [Open symbol Pos Found]

				// define Start Pos
				ucFstPos = k;

				// switch mode 
				act = 2;
			}
		}//then /if (act == 1)
		else
		{
			if (act == 2)
			{
				// [proc find Close symbol]

				if (c == chCloseSymbol)
				{
					// [Close symbol Pos Found]

					// define End Pos
					ucEndPos = k;

					// this was the last mode, so switch to End
					act = 0;
				}
			}//then /if (act == 2)
		}//else /if (act == 1)

		 // next symbol
		k++;

	}//while (act != 0)

	 // SafeCheck
	if (ucFstPos > ucEndPos)
	{
		strcpy(strOutput, "PARSE_ERROR");
		return OP_FAILURE;
	}

	BYTE ucTagLength = ucEndPos - ucFstPos;

	// > Form Output String /tag/
	for (BYTE kk = 0; kk <= ucTagLength - 2; kk++)			// -2 to skip start+finish delimeter
	{
		strOutput[kk] = strParse[ucFstPos + kk + 1];		// +1 to skip start delimeter
	}

	strOutput[ucTagLength - 1] = '\0';						// +1 -2 = -1


	return OP_SUCCESS;
}

// cut param value from string line upon header
BYTE GetStrParam(char* strParse, char* strHeader, char* strOutput)
{
	BYTE ucHeaderLength = strlen(strHeader);
	if (strncmp(strParse, strHeader, ucHeaderLength) == 0)
	{
		// [CORRECT]

		// get param Value									// +1 to skip delimeter
		strncpy(strOutput, strParse + ucHeaderLength + 1, strlen(strParse) - ucHeaderLength);
		
		return 0;
	}
	else
	{
		// [WRONG]

		return 1;
	}
}

// cut root header name from string
// return 0: if op success
// return 1: if op failed
// FORMAT:
// string of level0 header is: [VALUE]
BYTE GetLevel0(char* strParse, char* strOutput)
{
	// try to parse string
	char strValue[MAX_STR_TAG];
	BYTE ucStatus = GetStrTag(strParse, strValue, TAG_SYMB_OPEN, TAG_SYMB_CLOSE);

	// check result
	if (ucStatus == OP_SUCCESS)
	{
		strcpy(strOutput, strValue);

		return 0;
	}
	else if (ucStatus == OP_FAILURE) 
	{
		return 1;
	}
}

// read config file with global parameters
BYTE Read_config(stHPFileGlobals* var_stGlobals)
{
	// > Open File (config)
	// default name
	char* file_name = (char*)"res/variables.ini";

	// try open
	FILE* fs = fopen(file_name, "r");

	// check OP result
	if (fs == NULL)
	{
		// [fail to open]

		return FILE_NOFILE;
	}

	// > Read config
	var_stGlobals->cDirectoryPath[0] = '\0';

	char str_buf[MAX_STR_BUF] = "";

	// parse strings, sequential
	BYTE parseFlag = 0;
	BYTE paramFlag = 0;

	BYTE act = 1;
	while (act)
	{
		// get File String Line
		if (fgets(str_buf, MAX_STR_BUF, fs) == NULL)
		{
			// [STOP]

			act = 0;

			// check the Reason
			if (feof(fs))
			{
				// [EOF]

				// Valid case
			}
			else
			{
				if (ferror(fs))
				{
					// [ERROR]
				}
			}//NULL Read reason
		}
		else
		{
			// [PROCEED]

			// NOTE: File (config) has specific format:
			// FORMAT:
			// file has variour [label]s. 
			// Each [label] include some params.
			// Each param has some data type Value STRICTLY on the NEXT Line.
			// After Value '\n' divider may be exist.
			//
			// [PATH]		
			// char[64]
			//


			if (parseFlag == 0)
			{
				// [LEVEL 0]

				// # try to define [label]
				if (str_buf[0] == TAG_SYMB_OPEN)
				{
					// [STANDARD LABEL]

					char str_tag[MAX_STR_TAG];
					BYTE ucStatus = GetLevel0(str_buf, str_tag);

					// > Safe check
					if (ucStatus != OP_SUCCESS)
					{
						// [OP FAILED]

						// > Close File (config) 
						fclose(fs);

						// Exit PROC
						return FILE_STRUC_ERR;
					}

					// define label type
					if (strcmp(str_tag, "PATH") == 0)
					{
						// set label type
						parseFlag = 1;
					}
					else if (strcmp(str_tag, "par0") == 0)
					{
						// set label type
						parseFlag = 2;
					}
					else if (strcmp(str_tag, "par1") == 0)
					{
						// set label type
						parseFlag = 3;
					}
				}//valid tag open
			}
			else
			{
				// [LEVEL 1]

				// > Parse Label Content
				if (parseFlag == 1)				// [PATH]
				{
					char str_param[MAX_STR_PARAM];

					// parse parameters
					if (GetStrParam(str_buf, (char*)"dir", str_param) == 0)
					{
						// > Apply config Value
						strcpy(var_stGlobals->cDirectoryPath, str_param);

					}
					else if (GetStrParam(str_buf, (char*)"etc", str_param) == 0)
					{
						// set value
						// none
					}

					// reset parseFlag
					parseFlag = 0;
				}
			}
		}//else/if (fgets(str_buf, MAX_STR_BUF, fs) == "NULL")
	}//while (act)
}


void Config_Init(void)
{
	BYTE ucResult = Read_config(&m_stGlobals);
}
