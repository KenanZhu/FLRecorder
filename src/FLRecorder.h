///=====================================================///
/// 
/// \file   FLRecorder.h
/// \brief 'FastLogRecorder' Header File
/// \author KenanZhu
/// \date   2025-02-09
///-----------------------------------------------------///
/// \note
/// 
/// Copyright (c) 2025 by KenanZhu. All rights reserved.
///
/// ----------------------------------------------------///
/// \hsitory $-Date      $-Version  $-Update
///          2025-02-09  0.0.1      First Created.
///          2025-02-12  0.0.3      See Update Note.
///          2025-02-18  0.0.5      See Update Note.
///          2025-03-11  0.0.7      See Update Note.
/// 
///=====================================================///

#ifndef _FLRECORDER_H_
#define _FLRECORDER_H_

/// STDLIB_H ///

#ifdef _WIN32
#include <io.h>
#include <direct.h>

#define  SLA '\\'
#elif __APPLE__||__linux__
#include <dirent.h>
#include <unistd.h>
#include <sys/io.h>
#include <sys/stat.h>
#include <sys/types.h>

#define  SLA '/'
#endif

#include <math.h>
#include <regex>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

/// CONSTANT ///

/// -PROGRAM INFO
#define PROG_VER "0.0.5"  // Program Version

#define LEVEL_0    0      // Message Level: No Debug Message
#define LEVEL_1    1      // Message Level: Debug Message

#define SYS_LEVEL  0      // System Level
#define SYS_INFO   1      // System Info Level
#define SYS_WARN   2      // System Warning Level
#define SYS_ERROR  3      // System Error Level

/// -COMMAND CODE
#define CODE_NONE  0      // Decode : None
#define CODE_HELP  1      // Decode : Help Message
#define CODE_QUIT  2      // Decode : Quit Program
#define CODE_CLS   3      // Decode : Clear Screen
#define CODE_VER   4      // Decode : Program Version Meaasge
#define CODE_INIT  5      // Decode : Init Eorkfolder
#define CODE_NEW   6      // Decode : Init Eorkfolder
#define CODE_RM    7      // Decode : Remove Log File
#define CODE_ADD   8      // Decode : Add Log Record 
#define CODE_DEL   9      // Decode : Delete Log Record
#define CODE_SHOW 10      // Decode : Show All Logs List
#define CODE_FIND 11      // Decode : Find Log File

/// -FILE FORMAT
#define FFMT_NON   0      // (*.*)    Unknow File Format
#define FFMT_TXT   1      // (*.txt)  Txt File Format
#define FFMT_LOG   2      // (*.log)  Log File Format
#define FFMT_PLO   3      // (*.plog) Project Log File Format
#define FFMT_FLO   4      // (*.flog) Fast Log File Format

#define MAX_LOGF (int)1E3 // Max Amount of XLog File
#define MAX_LOGS (int)1E5 // Max Amount of Log Record
#define MAX_LINE (int)1E3 // Max Length of File Line
#define MIN_LINE 30       // Min Length of File Line
#define MAX_PATH 260      // Max Length of File Path

#define STDMSG(Msg)      cout<<string(Msg)<<endl

#endif // !_FLRECORDER_H_