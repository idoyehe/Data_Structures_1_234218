/***************************************************************************/
/*                                                                         */
/* 234218 Data DSs 1, Winter 2017-2018                                     */
/*                                                                         */
/* Homework : Wet 1                                                        */
/*                                                                         */
/***************************************************************************/

/***************************************************************************/
/*                                                                         */
/* File Name : main1.cpp                                                   */
/*                                                                         */
/* Holds the "int main()" function and the parser of the shell's           */
/* command line.                                                           */
/***************************************************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library1.h"
#include <iostream>
using namespace std;

#ifdef __cplusplus
extern "C" {
#endif

/* The command's strings */
typedef enum {
	NONE_CMD = -2,
	COMMENT_CMD = -1,
	INIT_CMD = 0,
	ADDTRAINER_CMD = 1,
	BUYGLADIATOR_CMD = 2,
	FREEGLADIATOR_CMD = 3,
	LEVELUP_CMD = 4,
	UPGRADE_CMD = 5,
	GETTOPGLADIATOR_CMD = 6,
	GETALLGLADIATORS_CMD = 7,
	UPDATE_CMD = 8,
	QUIT_CMD = 9
} commandType;

static const int numActions = 10;
static const char *commandStr[] = { "Init", "AddTrainer", "BuyGladiator",
		"FreeGladiator", "LevelUp", "UpgradeGladiator",
		"GetTopGladiator", "GetAllGladiatorsByLevel", "UpdateLevels", "Quit" };

static const char* ReturnValToStr(int val) {
	switch (val) {
	case SUCCESS:
		return "SUCCESS";
	case ALLOCATION_ERROR:
		return "ALLOCATION_ERROR";
	case FAILURE:
		return "FAILURE";
	case INVALID_INPUT:
		return "INVALID_INPUT";
	default:
		return "";
	}
}

/* we assume maximum string size is not longer than 256  */
#define MAX_STRING_INPUT_SIZE (255)
#define MAX_BUFFER_SIZE       (255)

#define StrCmp(Src1,Src2) ( strncmp((Src1),(Src2),strlen(Src1)) == 0 )

typedef enum {
	error_free, error
} errorType;
static errorType parser(const char* const command);

#define ValidateRead(read_parameters,required_parameters,ErrorString) \
if ( (read_parameters)!=(required_parameters) ) { printf(ErrorString); return error; }

static bool isInit = false;

///***************************************************************************/
///* main                                                                    */
///***************************************************************************/

int main(int argc, const char**argv) {
	char buffer[MAX_STRING_INPUT_SIZE];

	// Reading commands
	while (fgets(buffer, MAX_STRING_INPUT_SIZE, stdin) != NULL) {
		fflush(stdout);
		if (parser(buffer) == error)
			break;
	};
	return 0;
}
//
///***************************************************************************/
///* Command Checker                                                         */
///***************************************************************************/

static commandType CheckCommand(const char* const command,
		const char** const command_arg) {
	if (command == NULL || strlen(command) == 0 || StrCmp("\n", command))
		return (NONE_CMD);
	if (StrCmp("#", command)) {
		if (strlen(command) > 1)
			printf("%s", command);
		return (COMMENT_CMD);
	};
	for (int index = 0; index < numActions; index++) {
		if (StrCmp(commandStr[index], command)) {
			*command_arg = command + strlen(commandStr[index]) + 1;
			return ((commandType) index);
		};
	};
	return (NONE_CMD);
}

///***************************************************************************/
///* Commands Functions                                                      */
///***************************************************************************/

static errorType OnInit(void** DS, const char* const command);
static errorType OnAddTrainer(void* DS, const char* const command);
static errorType OnBuyGladiator(void* DS, const char* const command);
static errorType OnFreeGladiator(void* DS, const char* const command);
static errorType OnLevelUp(void* DS, const char* const command);
static errorType OnUpgradeGladiator(void* DS, const char* const command);
static errorType OnGetTopGladiator(void* DS, const char* const command);
static errorType OnGetAllGladiatorsByLevel(void* DS, const char* const command);
static errorType OnUpdateLevels(void* DS, const char* const command);
static errorType OnQuit(void** DS, const char* const command);

///***************************************************************************/
///* Parser                                                                  */
///***************************************************************************/

static errorType parser(const char* const command) {
	static void *DS = NULL; /* The general data structure */
	const char* command_args = NULL;
	errorType rtn_val = error;

	commandType command_val = CheckCommand(command, &command_args);

	switch (command_val) {

	case (INIT_CMD):
		rtn_val = OnInit(&DS, command_args);
		break;
	case (ADDTRAINER_CMD):
		rtn_val = OnAddTrainer(DS, command_args);
		break;
	case (BUYGLADIATOR_CMD):
		rtn_val = OnBuyGladiator(DS, command_args);
		break;
	case (FREEGLADIATOR_CMD):
		rtn_val = OnFreeGladiator(DS, command_args);
		break;
	case (LEVELUP_CMD):
		rtn_val = OnLevelUp(DS, command_args);
		break;
	case (UPGRADE_CMD):
		rtn_val = OnUpgradeGladiator(DS, command_args);
		break;
	case (GETTOPGLADIATOR_CMD):
		rtn_val = OnGetTopGladiator(DS, command_args);
		break;
	case (GETALLGLADIATORS_CMD):
		rtn_val = OnGetAllGladiatorsByLevel(DS, command_args);
		break;
	case (UPDATE_CMD):
		rtn_val = OnUpdateLevels(DS, command_args);
		break;
	case (QUIT_CMD):
		rtn_val = OnQuit(&DS, command_args);
		break;

	case (COMMENT_CMD):
		rtn_val = error_free;
		break;
	case (NONE_CMD):
		rtn_val = error;
		break;
	default:
		assert(false);
		break;
	};
	return (rtn_val);
}
//
///***************************************************************************/
///* OnInit                                                                  */
///***************************************************************************/
static errorType OnInit(void** DS, const char* const command) {
	if (isInit) {
		printf("Init was already called.\n");
		return (error_free);
	};
	isInit = true;

	*DS = Init();
	if (*DS == NULL) {
		printf("Init failed.\n");
		return error;
	};
	printf("Init done.\n");

	return error_free;
}

///***************************************************************************/
///* OnAddTrainer                                                             */
///***************************************************************************/
static errorType OnAddTrainer(void* DS, const char* const command) {
	int trainerID;
	ValidateRead(sscanf(command, "%d", &trainerID), 1, "AddTrainer failed.\n");
	StatusType res = AddTrainer(DS, trainerID);

	if (res != SUCCESS) {
		printf("AddTrainer: %s\n", ReturnValToStr(res));
		return error_free;
	} else {
		printf("AddTrainer: %s\n", ReturnValToStr(res));
	}

	return error_free;
}

///***************************************************************************/
///* OnBuyGladiator                                                          */
///***************************************************************************/
static errorType OnBuyGladiator(void* DS, const char* const command) {
	int gladiatorID;
	int trainerID;
	int level;
	ValidateRead(
			sscanf(command, "%d %d %d", &gladiatorID, &trainerID, &level),
			3, "BuyGladiator failed.\n");
	StatusType res = BuyGladiator(DS, gladiatorID, trainerID, level);

	if (res != SUCCESS) {
		printf("BuyGladiator: %s\n", ReturnValToStr(res));
		return error_free;
	}

	printf("BuyGladiator: %s\n", ReturnValToStr(res));
	return error_free;
}

///***************************************************************************/
///* OnFreeGladiator                                                            */
///***************************************************************************/
static errorType OnFreeGladiator(void* DS, const char* const command) {
	int gladiatorID;
	ValidateRead(sscanf(command, "%d", &gladiatorID), 1,
			"FreeGladiator failed.\n");
	StatusType res = FreeGladiator(DS, gladiatorID);

	if (res != SUCCESS) {
		printf("FreeGladiator: %s\n", ReturnValToStr(res));
		return error_free;
	}

	printf("FreeGladiator: %s\n", ReturnValToStr(res));
	return error_free;
}

/***************************************************************************/
/* OnLevelUp                                                         */
/***************************************************************************/
static errorType OnLevelUp(void* DS, const char* const command) {
	int gladiatorID;
	int levelIncrease;
	ValidateRead(sscanf(command, "%d %d", &gladiatorID, &levelIncrease), 2,
			"LevelUp failed.\n");
	StatusType res = LevelUp(DS, gladiatorID, levelIncrease);

	if (res != SUCCESS) {
		printf("LevelUp: %s\n", ReturnValToStr(res));
		return error_free;
	}

	printf("LevelUp: %s\n", ReturnValToStr(res));
	return error_free;
}

/***************************************************************************/
/* OnUpgradeGladiator                                                            */
/***************************************************************************/
static errorType OnUpgradeGladiator(void* DS, const char* const command) {
	int gladiatorID;
	int upgradedID;
	ValidateRead(sscanf(command, "%d %d", &gladiatorID, &upgradedID), 2,
			"UpgradeGladiator failed.\n");
	StatusType res = UpgradeGladiator(DS, gladiatorID, upgradedID);

	if (res != SUCCESS) {
		printf("UpgradeGladiator: %s\n", ReturnValToStr(res));
		return error_free;
	}

	printf("UpgradeGladiator: %s\n", ReturnValToStr(res));
	return error_free;
}

/***************************************************************************/
/* OnGetTopGladiator                                                         */
/***************************************************************************/
static errorType OnGetTopGladiator(void* DS, const char* const command) {
	int trainerID;
	ValidateRead(sscanf(command, "%d", &trainerID), 1, "GetTopGladiator failed.\n");
	int gladiatorID;
	StatusType res = GetTopGladiator(DS, trainerID, &gladiatorID);

	if (res != SUCCESS) {
		printf("GetTopGladiator: %s\n", ReturnValToStr(res));
		return error_free;
	}
	cout << "Gladiator with highest level is: " << gladiatorID << endl;
	return error_free;
}

/***************************************************************************/
/* OnGetAllGladiatorsByLevel                                                        */
/***************************************************************************/

void PrintAll(int *gladiators, int numOfGladiators) {
	if (numOfGladiators > 0) {
		cout << "Level	||	Gladiator" << endl;
	}

	for (int i = 0; i < numOfGladiators; i++) {
		cout << i + 1 << "\t||\t" << gladiators[i] << endl;
	}
	cout << "and there are no more gladiators!" << endl;

	free (gladiators);
}

static errorType OnGetAllGladiatorsByLevel(void* DS, const char* const command) {
	int trainerID;
	ValidateRead(sscanf(command, "%d", &trainerID), 1,
			"GetAllGladiatorsByLevel failed.\n");
	int* gladiators;
	int numOfGladiators;
	StatusType res = GetAllGladiatorsByLevel(DS, trainerID, &gladiators, &numOfGladiators);

	if (res != SUCCESS) {
		printf("GetAllGladiatorsByLevel: %s\n", ReturnValToStr(res));
		return error_free;
	}

	PrintAll(gladiators, numOfGladiators);
	return error_free;
}

/***************************************************************************/
/* OnUpdateLevels                                                           */
/***************************************************************************/
static errorType OnUpdateLevels(void* DS, const char* const command) {
	int stimulantCode;
	int stimulantFactor;
	ValidateRead(sscanf(command, "%d %d", &stimulantCode, &stimulantFactor), 2,
			"UpdateLevels failed.\n");
	StatusType res = UpdateLevels(DS, stimulantCode, stimulantFactor);

	if (res != SUCCESS) {
		printf("UpdateLevels: %s\n", ReturnValToStr(res));
		return error_free;
	}

	printf("UpdateLevels: %s\n", ReturnValToStr(res));
	return error_free;
}

/***************************************************************************/
/* OnQuit                                                                  */
/***************************************************************************/
static errorType OnQuit(void** DS, const char* const command) {
	Quit(DS);
	if (*DS != NULL) {
		printf("Quit failed.\n");
		return error;
	};

	isInit = false;
	printf("Quit done.\n");

	return error_free;
}

#ifdef __cplusplus
}
#endif
