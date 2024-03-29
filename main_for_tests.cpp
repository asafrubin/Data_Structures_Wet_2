/***************************************************************************/
/*                                                                         */
/* 234218 Data DSs 1, Winter 2018-2019                                     */
/* Homework : Wet 1                                                        */
/*                                                                         */
/***************************************************************************/

/***************************************************************************/
/*                                                                         */
/* File Name : main2.cpp                                                   */
/*                                                                         */
/* Holds the "int main()" function and the parser of the shell's           */
/* command line.                                                           */
/***************************************************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include "library.h"

#ifdef __cplusplus
extern "C" {
#endif

/* The command's strings */
typedef enum {
    NONE_CMD = -2,
    COMMENT_CMD = -1,
    INIT_CMD = 0,
    ADDIMAGE_CMD = 1,
    DELETEIMAGE_CMD = 2,
    SETLABELSCORE_CMD = 3,
    RESETLABELSCORE_CMD = 4,
    GETHIGHESTSCOREDLABEL_CMD = 5,
    MERGESUPERPIXELS_CMD = 6,
    QUIT_CMD = 7
} commandType;

static const int numActions = 8;
static const char *commandStr[] = {
        "init",
        "addImage",
        "deleteImage",
        "setLabelScore",
        "resetLabelScore",
        "getHighestScoredLabel",
        "mergeSuperPixels",
        "quit" };

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

#define ValidateRead(read_parameters,required_parameters,ErrorString,ErrorParams) \
if ( (read_parameters)!=(required_parameters) ) { printf(ErrorString, ErrorParams); return error; }

static bool isInit = false;

/***************************************************************************/
/* main                                                                    */
/***************************************************************************/

FILE* wfile;
int main(int argc, const char**argv) {

    char buffer[MAX_STRING_INPUT_SIZE];
    std::string rfile_string, wfile_string;
    std::string randTest("tests/randTest");
    std::string dotIn(".in");
    std::string dotOut("Result.out");
    std::string result("test_results/randTest");
    FILE *rfile;

    int counter = 0;
    for(int i=0; i < 20; i++) {
        rfile_string = randTest + std::to_string(i) + dotIn;
        wfile_string = result + std::to_string(i) + dotOut;
        rfile = fopen(rfile_string.c_str(), "r");
        wfile = fopen(wfile_string.c_str(), "w+");
        if (rfile == nullptr || wfile == nullptr) {
            printf("error opening file\n");
            fclose(rfile);
            fclose(wfile);
            return 0;
        }

        // Reading commands
        while (fgets(buffer, MAX_STRING_INPUT_SIZE, rfile) != NULL) {
            counter++;
            fflush(stdout);
            if (parser(buffer) == error)
                break;
        };
        fclose(rfile);
        fclose(wfile);
    }
    return 0;
}

/***************************************************************************/
/* Command Checker                                                         */
/***************************************************************************/

static commandType CheckCommand(const char* const command,
                                const char** const command_arg) {
    if (command == NULL || strlen(command) == 0 || StrCmp("\n", command))
        return (NONE_CMD);
    if (StrCmp("#", command)) {
        if (strlen(command) > 1)
            fprintf(wfile, "%s", command);
        return (COMMENT_CMD);
    };
    for (int index = 0; index < numActions; index++) {
        if (StrCmp(commandStr[index], command)) {
            *command_arg = command + strlen(commandStr[index]) + 1;
            return ((commandType)index);
        };
    };
    return (NONE_CMD);
}

/***************************************************************************/
/* Commands Functions                                                      */
/***************************************************************************/

static errorType OnInit(void** DS, const char* const command);
static errorType OnAddImage(void* DS, const char* const command);
static errorType OnDeleteImage(void* DS, const char* const command);
static errorType OnSetLabelScore(void* DS, const char* const command);
static errorType OnResetLabelScore(void* DS, const char* const command);
static errorType OnGetMostCommonLabel(void* DS, const char* const command);
static errorType OnMergeSuperPixels(void* DS, const char* const command);
static errorType OnQuit(void** DS, const char* const command);

/***************************************************************************/
/* Parser                                                                  */
/***************************************************************************/

static errorType parser(const char* const command) {
    static void *DS = NULL; /* The general data structure */
    const char* command_args = NULL;
    errorType rtn_val = error;

    commandType command_val = CheckCommand(command, &command_args);

    switch (command_val) {

        case (INIT_CMD):
            rtn_val = OnInit(&DS, command_args);
            break;
        case (ADDIMAGE_CMD):
            rtn_val = OnAddImage(DS, command_args);
            break;
        case (DELETEIMAGE_CMD):
            rtn_val = OnDeleteImage(DS, command_args);
            break;
        case (SETLABELSCORE_CMD):
            rtn_val = OnSetLabelScore(DS, command_args);
            break;
        case (RESETLABELSCORE_CMD):
            rtn_val = OnResetLabelScore(DS, command_args);
            break;
        case (GETHIGHESTSCOREDLABEL_CMD):
            rtn_val = OnGetMostCommonLabel(DS, command_args);
            break;
        case (MERGESUPERPIXELS_CMD):
            rtn_val = OnMergeSuperPixels(DS, command_args);
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

/***************************************************************************/
/* OnInit                                                                  */
/***************************************************************************/
static errorType OnInit(void** DS, const char* const command) {
    if (isInit) {
        fprintf(wfile, "init was already called.\n");
        return (error_free);
    };
    isInit = true;

    int pixels;
    ValidateRead(sscanf(command, "%d", &pixels), 1, "%s failed.\n", commandStr[INIT_CMD]);
    *DS = Init(pixels);

    if (*DS == NULL) {
        fprintf(wfile, "init failed.\n");
        return error;
    };

    fprintf(wfile, "init done.\n");
    return error_free;
}


/***************************************************************************/
/* OnAddImage                                                               */
/***************************************************************************/
static errorType OnAddImage(void* DS, const char* const command) {
    int imageID;
    ValidateRead(sscanf(command, "%d", &imageID), 1, "%s failed.\n", commandStr[ADDIMAGE_CMD]);
    StatusType res = AddImage(DS, imageID);

    if (res != SUCCESS) {
        fprintf(wfile, "%s: %s\n", commandStr[ADDIMAGE_CMD], ReturnValToStr(res));
        return error_free;
    }

    fprintf(wfile, "%s: %s\n", commandStr[ADDIMAGE_CMD], ReturnValToStr(res));
    return error_free;
}

/***************************************************************************/
/* OnDeleteImage                                                            */
/***************************************************************************/
static errorType OnDeleteImage(void* DS, const char* const command) {
    int imageID;
    ValidateRead(sscanf(command, "%d", &imageID), 1, "%s failed.\n", commandStr[DELETEIMAGE_CMD]);
    StatusType res = DeleteImage(DS, imageID);

    if (res != SUCCESS) {
        fprintf(wfile, "%s: %s\n", commandStr[DELETEIMAGE_CMD], ReturnValToStr(res));
        return error_free;
    }

    fprintf(wfile, "%s: %s\n", commandStr[DELETEIMAGE_CMD], ReturnValToStr(res));
    return error_free;
}

/***************************************************************************/
/* OnSetLabelScore                                                         */
/***************************************************************************/
static errorType OnSetLabelScore(void* DS, const char* const command) {
    int imageID, pixel, label, score;
    ValidateRead(sscanf(command, "%d %d %d %d", &imageID, &pixel, &label, &score), 4, "%s failed.\n", commandStr[SETLABELSCORE_CMD]);
    StatusType res = SetLabelScore(DS, imageID, pixel, label, score);

    if (res != SUCCESS) {
        fprintf(wfile, "%s: %s\n", commandStr[SETLABELSCORE_CMD], ReturnValToStr(res));
        return error_free;
    }

    fprintf(wfile, "%s: %s\n", commandStr[SETLABELSCORE_CMD], ReturnValToStr(res));
    return error_free;
}

/***************************************************************************/
/* OnResetLabelScore                                                       */
/***************************************************************************/
static errorType OnResetLabelScore(void* DS, const char* const command) {
    int imageID, pixel, label;
    ValidateRead(sscanf(command, "%d %d %d", &imageID, &pixel, &label), 3, "%s failed.\n", commandStr[RESETLABELSCORE_CMD]);
    StatusType res = ResetLabelScore(DS, imageID, pixel, label);

    if (res != SUCCESS) {
        fprintf(wfile, "%s: %s\n", commandStr[RESETLABELSCORE_CMD], ReturnValToStr(res));
        return error_free;
    }

    fprintf(wfile, "%s: %s\n", commandStr[RESETLABELSCORE_CMD], ReturnValToStr(res));
    return error_free;
}

int CompareInt(const void* a, const void* b)
{
    if (*(int*)a == *(int*)b) return 0;
    return *(int*)a < *(int*)b ? -1 : 1;
}

/***************************************************************************/
/* OnGetMostCommonLabel                                                    */
/***************************************************************************/
static errorType OnGetMostCommonLabel(void* DS, const char* const command) {
    int imageID, pixel, label;
    ValidateRead(sscanf(command, "%d %d", &imageID, &pixel), 2, "%s failed.\n", commandStr[GETHIGHESTSCOREDLABEL_CMD]);
    StatusType res = GetHighestScoredLabel(DS, imageID, pixel, &label);

    if (res != SUCCESS) {
        fprintf(wfile, "%s: %s\n", commandStr[GETHIGHESTSCOREDLABEL_CMD], ReturnValToStr(res));
        return error_free;
    }

    fprintf(wfile, "%s: %d\n", commandStr[GETHIGHESTSCOREDLABEL_CMD], label);
    return error_free;
}

/***************************************************************************/
/* OnMergeSuperPixels                                                      */
/***************************************************************************/
static errorType OnMergeSuperPixels(void* DS, const char* const command) {
    int imageID, pixel1, pixel2;
    ValidateRead(sscanf(command, "%d %d %d", &imageID, &pixel1, &pixel2), 3, "%s failed.\n", commandStr[MERGESUPERPIXELS_CMD]);
    StatusType res = MergeSuperPixels(DS, imageID, pixel1, pixel2);

    if (res != SUCCESS) {
        fprintf(wfile, "%s: %s\n", commandStr[MERGESUPERPIXELS_CMD], ReturnValToStr(res));
        return error_free;
    }

    fprintf(wfile, "%s: %s\n", commandStr[MERGESUPERPIXELS_CMD], ReturnValToStr(res));
    return error_free;
}

/***************************************************************************/
/* OnQuit                                                                  */
/***************************************************************************/
static errorType OnQuit(void** DS, const char* const command) {
    Quit(DS);
    if (*DS != NULL) {
        fprintf(wfile, "quit failed.\n");
        return error;
    };

    isInit = false;
    fprintf(wfile, "quit done.\n");
    return error_free;
}

#ifdef __cplusplus
}
#endif