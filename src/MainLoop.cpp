///=====================================================///
/// 
/// \file   MainLoop.cpp
/// \brief 'FastLogRecorder' Main Source File
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

#include "PackAPI.h"
#include "FLRecorder.h"
#include "./CmdForge/CmdForge.h"

using namespace std;

int main(int argc,char *argv[])
{
    ForgeHwnd CLIF;
    CLICfgData Cfg;
    OptFmtData OptFmt;
    ArgFmtData ArgFmt;

    Cfg.InputSleTime=10;
    Cfg.DetectSleTime=10;
    Cfg.MaxStoredCmd=20;
    Cfg.Version="0.0.7";
    Cfg.VerMode=VER_M_ALPA;

    CLIF.SetCLICfg(Cfg);
    CLIF.SetCLIMainCmd("fast");

    CLIF.HookCmdApi("-init",PackCmdInit);
    CLIF.SetCmdBrief("-init","init the workfolder of FLRecorder.");

    CLIF.HookCmdApi("-show",PackCmdShow);
    CLIF.SetCmdBrief("-show","display the workfolder list");

    CLIF.HookCmdApi("-new",PackCmdNew);
    CLIF.SetCmdBrief("-new","create new log file.");
    OptFmt.Brief="create new log file in basic type.";
    OptFmt.Optional=true;
    OptFmt.LongFmt="-basic";
    OptFmt.ShortFmt="-b";
    OptFmt.Args.push_back(ArgFmt);
    CLIF.SetCmdOpt("-new",OptFmt);

    OptFmt.Brief="create new log file in project type";
    OptFmt.Optional=true;
    OptFmt.LongFmt="-project";
    OptFmt.ShortFmt="-p";
    CLIF.SetCmdOpt("-new",OptFmt);

    OptFmt.Brief="Create new log file in fast type";
    OptFmt.Optional=true;
    OptFmt.LongFmt="-fast";
    OptFmt.ShortFmt="-f";
    CLIF.SetCmdOpt("-new",OptFmt);

    CLIF.HookCmdApi("-remove",PackCmdRemove);
    CLIF.SetCmdBrief("-remove","remove exist file");
    CLIF.HookCmdApi("-rm",PackCmdRemove);
    OptFmt.Brief="default";
    OptFmt.Optional=true;
    OptFmt.LongFmt="-default";
    OptFmt.ShortFmt="-d";
    CLIF.SetCmdOpt("-remove",OptFmt);

    CLIF.MainLoop("> FLRecorder {ver0.0.7} :");

    return 0;
}