///=====================================================///
/// 
/// \file   FLRecorder.h
/// \brief 'FastLogRecorder' Header File
/// \author KenanZhu
/// \date   2025-02-09
///-----------------------------------------------------///
/// \note
/// 
/// This is an open source software. You are free to use,
/// modify, and redistribute it. However, you must include
/// the original author's information and the original
/// source code.
///
/// This program is a fast log recording constructor.
/// It can support record simple message by BLog.
///        support record project message by PLog.
///        support recorder fast construct by FLog.
/// 
/// Copyright (c) 2025 by KenanZhu. All rights reserved.
///
/// ----------------------------------------------------///
/// \hsitory $-Date      $-Version  $-Update
///          2025-02-09  0.0.1      First Created.
/// 
///=====================================================///

#ifndef _FLRECORDER_H_
#define _FLRECORDER_H_

/// STDLIB_H ///

#include <regex>

#ifdef _WIN32
#include <io.h>
#include <direct.h>
#elif __APPLE__||__linux__
#include <dirent.h>
#include <unistd.h>
#include <sys/io.h>
#include <sys/stat.h>
#include <sys/types.h>
#endif

#include <cstdio>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

/// CONSTANT ///

/// -SOFTWARE VERSION
#define PROG_VER "0.0.1"  // Software Version

#define SYS_LEVEL  0      // System Level
#define SYS_INFO   1      // System Info Level
#define SYS_WARN   2      // System Warning Level
#define SYS_ERROR  3      // System Error Level

/// -COMMAND CODE
#define CODE_NONE  0      // Decode : None
#define CODE_HELP  1      // Decode : Help Message
#define CODE_QUIT  2      // Decode : Quit Program
#define CODE_VER   3      // Decode : Program Version Meaasge
#define CODE_INIT  4      // Decode : Init Eorkfolder
#define CODE_NEW   5      // Decode : Init Eorkfolder
#define CODE_RM    6      // Decode : Remove Log File
#define CODE_ADD   7      // Decode : Add Log Record 
#define CODE_DEL   8      // Decode : Delete Log Record
#define CODE_SHOW  9      // Decode : Show All Logs List
#define CODE_FIND 10      // Decode : Find Log File

/// -FILE FORMAT
#define FFMT_NON   0      // (*.*)    Unknow File Format
#define FFMT_TXT   1      // (*.txt)  Txt File Format
#define FFMT_LOG   2      // (*.log)  Log File Format
#define FFMT_PLO   3      // (*.plog) Project Log File Format
#define FFMT_FLO   4      // (*.flog) Fast Log File Format

#define MAX_LOGS (int)1E5 // Max Amount of Log Record
#define MAX_LINE (int)1E3 // Max Length of File Line
#define MIN_LINE 30       // Min Length of File Line
#define MAX_PATH 260      // Max Length of File Path

/// DATA STRUCT ///
typedef struct {    // Second with Fraction-Second Format
    long Second;    // Second
    double Fsecond; // Fraction-Second
} SecTime;          
                    
typedef struct {    // Time Struct in Cal Format 
    int Year;       // 
    int Month;      // 
    int Day;        // 
    int Hour;       // 
    int Minute;     // 
    int Second;     // 
    double Fsecond; // Fraction-Second
} CalTime;

/// FUNCTIONS ///
extern CalTime Sec2CalTime(SecTime Time);
extern SecTime Cal2SecTime(CalTime Time);

#endif // !_FLRECORDER_H_