//  \FILE  : CmdForge.h
//  \BRIEF : CmdForge class,functions&data types prototypes.
//
//  \AUTHOR: KenanZhu (NANOKI)
// ----------------------------------------------------------------------------
//  CmdForge <https://github.com/KenanZhu/CmdForge>
//  Copyright (C) 2025  KenanZhu (NANOKI)
// 
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Affero General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
// 
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Affero General Public License for more details.
// 
//  You should have received a copy of the GNU Affero General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
// ----------------------------------------------------------------------------
//  DATE OF FIRST EDIT: 2025-02-26
//  VERSION OF LIB    : 1.0.1
// ----------------------------------------------------------------------------

#pragma once

//////////////////// _INCLUDE_
#include <vector>
#include <sstream>
#include <iostream>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#elif __linux__
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>
#endif

//////////////////// _DEFINE_
#define _DEFAULT_M      0         // Run Mode: default mode.
#define HIGH_PFM_M      1         // Run Mode: high performance mode.
#define BALANCED_M      2         // Run Mode: balanced mode.
#define LOW_COST_M      3         // Run Mode: low cost mode.

                                  // Space.
#define S               std::string(" ")
#define DS              S+S       // Two spaces.
#define TS              S+DS      // Thress spaces.
#define FS              S+TS      // Four spaces. 

#define VER_M_DEFT      S         // Version Mode: default.
                                  // Version Mode: alpha.
#define VER_M_ALPA      std::string("alpha")
                                  // Version Mode: beta.
#define VER_M_BETA      std::string("beta")
                                  // Version Mode: stable.
#define VER_M_REL       std::string("stable")
#define VER_M_SPARE     S         // Version Mode: reserved.
                                  // Default run sign.
#define DEFT_RSIGN      std::string("> CmdForge :")

////////////////////---------------------------------------

using namespace std; /// STANDARD NAMESPACE

////////////////////---------------------------------------

class SysOut;        /// FORWARD DECLARATION
class ApiCan;
class FData;
class FBuilder;
class FParser;
class ForgeHwnd;

typedef struct {                  // Argument control data type.
    string Brief;                 // Brief description.
    string ArgType;               // Argument type.
}ArgFmtData;

typedef struct {                  // Option control data type.
    bool Optional;                // Optional or not.
    string Brief;                 // Brief description.
    string LongFmt;               // Long format option.
    string ShortFmt;              // Short format option.
    vector<ArgFmtData> Args;      // Arguments of option.
}OptFmtData;

typedef struct {                  // CLI configuration data type.
    int MaxStoredCmd;             // Maximum stored history commands.

    int InputSleTime;             // Sleep time of command input thread.
    int DetectSleTime;            // Sleep time of key detect thread.

    string VerMode;               // Version mode of CLI.
    string Version;               // Version info of CLI.
}CLICfgData;

typedef struct {                  // Shared data type between threads.
    int CursorPos;                // Cursor position of command.
    bool ExitFlag;                // Exit flag of thread.
    string CurInput;              // Current input.
}CmdSurfaceData;

#ifdef __linux__
extern bool _kbhit(void);         // Keyborad hit detect.
extern int _getch(void);          // Get keyborad input.
#endif

////////////////////---------------------------------------

/// THIS CLASS IS THE SYSTEM INFORMATION OUTPUT
///
///////////////////////////////////////////////////////////
class SysOut
{
protected:
///
/// NONE FOR THIS CLASS
///
private:
///
/// NONE FOR THIS CLASS
///
public:
    SysOut()=default;

    void Cout(string Msg,int Endl=1);

    void StdMsg(string Msg,int Level=-1);

    void Refresh(string RunSign,string CurCmd);
};
////////////////////---------------------------------------

/// THIS CLASS IS THE CAN OF API FUNCTION
///
///////////////////////////////////////////////////////////
class ApiCan:public SysOut
{
protected:
    string s_Brief;               // Brief description of api function.
    vector<string> s_Cmds;        // Command of api function.
    vector<OptFmtData> s_Opts;    // Options of api command.h
                                  // Arguments arranged by option.
    vector<vector<string>> s_OptArgs;
                                  // Api function callbacked.
    void (*s_API)(vector<vector<string>>);

    bool PreCheck(vector<string> *OptsArgs);

    bool PostCheck(vector<vector<string>> OptArgs);

    void GenHelpInfo(void);
private:

    void Init(void);

    vector<vector<string>> SplitOpts(vector<string> OptsArgs);

    void SortOptArgs(vector<vector<string>> *OptArgs);
public:
    ApiCan();

    bool Check(void);

    void *API(void);

    void API(vector<string> CmdOptsArgs);

    void SetApi(void (*API)(vector<vector<string>>));

    void SetBrief(string Brief);

    bool ExistCmd(string Cmd);

    int  CmdIndex(string Cmd);

    void AppendCmd(string Cmd);

    bool ExistOpt(string OptName);

    int  OptIndex(string OptName);

    void AppendOpt(OptFmtData Opt);
};

////////////////////---------------------------------------

/// THIS CLASS IS THE BASE DATA OF CMDFORGE
/// 
///////////////////////////////////////////////////////////
class FData:public SysOut
{
protected:
    int s_ResCmdNum;              // Number of reserved command.
    string s_CmdIn;               // Command inputed by user.
    string s_RunSign;             // Runing sign of CmdForge.
    string s_MainCmd;             // Main command.
    vector<int> s_CmdApiTable;    // Command api table.
    vector<string> s_CmdIndex;    // Command index.
    vector<string> s_CmdOptsArgs; // Command splited by options, arguments.
    vector<ApiCan> s_ApiCanPool;  // Api can pool.

    void SetCmdIn(string CmdIn);

    void SetMainCmd(string MainCmd);

    void SetCmdOptArgs(vector<string> CmdOptArgs);

    vector<string> SplitCmd(string CmdIn);

    bool ExistCmd(string Cmd);

    int  CmdIndex(string Cmd);

    void AppendCmd(string Cmd);

    bool ExistApiCan(ApiCan ApiCan);

    int  ApiCanIndex(ApiCan ApiCan);

    void AppendApiCan(ApiCan ApiCan);
private:

    void Init(void);
public:
    FData();
};

////////////////////---------------------------------------

/// THIS CLASS IS THE BUILDER OF CMDFORGE
/// 
///////////////////////////////////////////////////////////
class FBuilder:virtual public FData
{
protected:

    void HookApi(string Cmd,void (*API)(vector<vector<string>>));

    bool CheckHooks(void);
private:
///
/// NONE FOR THIS CLASS
///
public:
    FBuilder()=default;
};

////////////////////---------------------------------------

/// THIS CLASS IS THE PARSER OF CMDFORGE
/// 
///////////////////////////////////////////////////////////
class FParser:virtual public FData
{
protected:

    void CmdParser(string CmdIn);

    void SendOSCmd(string Cmd);

    void ForkApi(string Cmd);

    virtual void ForkReserved(int Index);
private:
///
/// NONE FOR THIS CLASS
///
public:
    FParser()=default;
};

////////////////////---------------------------------------

/// THIS CLASS IS THE CONTROLLER OF CMDFORGE
/// 
///////////////////////////////////////////////////////////
class ForgeHwnd:public FParser,public FBuilder
{
protected:
    CLICfgData s_Cfg;             // CLI configuration data.
    int s_CurCmdPos=0;            // Current position of history commands.
    vector<string> s_HistoryCmd;  // History command stored.
#ifdef __linux__
    struct termios s_Original;    // Original setting of linux terminal
#endif
    void CmdAutoComplete(string *CurCmd);

    void InputCmdTask(CmdSurfaceData *Data);

    void DetecKeyTask(CmdSurfaceData *Data);
private:

    bool Check(void);

    void StoreCmd(string CurCmd);

    void GetLastCmd(string *CurCmd);

    void GetNextCmd(string *CurCmd);
#ifdef __linux__
    void TerminalSet();

    void TerminalReset();
#endif
    void GenHelpInfo(void);

    void GenVersionInfo(void);

    void ForkReserved(int Index);
public:
    ForgeHwnd();

    void SetCLICfg(CLICfgData Cfg);

    void SetCLIMainCmd(string MainCmd);

    void HookCmdApi(string Cmd,void (*API)(vector<vector<string>>));

    void SetCmdBrief(string Cmd,string Brief);

    void SetCmdOpt(string Cmd,OptFmtData OptFmt);

    int  MainLoop(string RunSign=DEFT_RSIGN);
};