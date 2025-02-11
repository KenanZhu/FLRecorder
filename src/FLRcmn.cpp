///
/// UNIVERSAL FUNCTIONS LIB FOR 'FastLogRecorder'
/// 

#include "FLRecorder.h"
#include ".\LogTypes\LogTypes.h"

///////////////////////////////////////////////////////////////////////////////
/// SYSTEM VARIABLES
static bool InfoFlag=false;      /// Info Flag
static bool InitFlag=false;      /// Init Flag
static string WorkFolderPath;    /// Workfolder Path
static vector<string> BLogPaths; /// BLog Paths
static vector<string> PLogPaths; /// PLog Paths
static vector<string> FLogPaths; /// FLog Paths


///////////////////////////////////////////////////////////////////////////////
/// CLI LOGIC FUNCTIONS

/// System Infomation ///////////////////////////
void SysLevel(int Level)
{
    if (Level>=0) InfoFlag=true;
    return;
}
void SysInfo(int Level,string Msg)
{
    string LevelSign;

    if (!InfoFlag&&Level!=-1) return;

    switch (Level) {
       case -1: LevelSign="";                 break;
       case  0: LevelSign="[-Sys] SysInfo :"; break;
       case  1: LevelSign="[-Sys] SysWarn :"; break;
       case  2: LevelSign="[-Sys] SysErr  :"; break;
    }
    cout<<LevelSign+Msg<<endl;

    return;
}
/// Program Launch Message //////////////////////
void ProLaunchMsg()
{
    cout<<endl;
    cout<<" __________________________________________________________"<<endl;
    cout<<"| >FastLogRecorder Version 0.0.1                           |"<<endl;
    cout<<"|                                                          |"<<endl;
    cout<<"|  Copyright (c) 2025 by KenanZhu. All rights reserved.    |"<<endl;
    cout<<"|                                                          |"<<endl;
    cout<<"| >This is an open source software. You are free to use,   |"<<endl;
    cout<<"|  modify, and redistribute it. However, you must include  |"<<endl;
    cout<<"|  the original author's information and the original      |"<<endl;
    cout<<"|  source code.                                            |"<<endl;
    cout<<"|                                                          |"<<endl;
    cout<<"| >This program is a fast log recording constructor.       |"<<endl;
    cout<<"|  It can support record simple message by BLog.           |"<<endl;
    cout<<"|         support record project message by PLog.          |"<<endl;
    cout<<"|         support recorder fast construct by FLog.         |"<<endl;
    cout<<"|                                                          |"<<endl;
    cout<<"|__________________________________________________________|"<<endl;
    cout<<"|  You can use command 'fast -help' to get usage           |"<<endl;
    cout<<"|                                                          |"<<endl;
    cout<<"|__________________________________________________________|"<<endl;
    cout<<endl;

    return; 
}
/// Process Help Message ////////////////////////
static void ProHelpMsg()
{
    cout<<endl;
    cout<<"    Commands are like:                           "<<endl;
    cout<<"      FLRecord/base> fast [-cmd] [arg]           "<<endl;
    cout<<"                                                 "<<endl;
    cout<<"      $[-cmd] $[arg]    $command                 "<<endl;
    cout<<"                                                 "<<endl;
    cout<<"       [-help]           Get help.               "<<endl;
    cout<<"       [-quit]           Exit the program.       "<<endl;
    cout<<"       [-ver]            Get program version.    "<<endl;
    cout<<"       [-init]           Init the workfolder.    "<<endl;
    cout<<"       [-new]            Add a new log file.     "<<endl;
    cout<<"          |____[int]     log type.               "<<endl;
    cout<<"          |____[str]     log file name.          "<<endl;
    cout<<"       [-rm]             Remove a log file.      "<<endl;
    cout<<"          |____[str]     log file name.          "<<endl;
    cout<<"       [-add]            Add a log record.       "<<endl;
    cout<<"          |____[str]     log file name.          "<<endl;
    cout<<"          |____[str]     new log record.         "<<endl;
    cout<<"       [-del]            Delete a log record.    "<<endl;
    cout<<"          |____[str]     log file name.          "<<endl;
    cout<<"          |____[str]     deleted log record.     "<<endl;
    cout<<"       [-show]           Show all logs list.     "<<endl;
    cout<<"          |____[str]     <optional> log file name"<<endl;
    cout<<"       [-find]           Find log file.          "<<endl;
    cout<<"          |____[str]     log file name.          "<<endl;
    cout<<endl;

    return;
}
/// Process Version Message /////////////////////
static void ProVerMsg()
{
    cout<<" _________________________________________________________ "<<endl;
    cout<<"| >FastLogRecorder Version 0.0.1                          |"<<endl;
    cout<<endl;

    return;
}
/// Process Init Message ////////////////////////
static void ProInitMsg()
{
    int flag;
    char Path[MAX_PATH];

    if (InitFlag) {
        SysInfo(1,"Workfolder has been initialized!");
        return;
    }
    if (!getcwd(Path,MAX_PATH)) {
        SysInfo(2,"Get current work folder path failed!");
        return;
    }
    /// Set Work Folder Path
    WorkFolderPath=Path;
    WorkFolderPath+="\\log";
    SysInfo(0,"Init workfolder path: "+WorkFolderPath);

    if (_access(WorkFolderPath.data(),0)!=-1) {
        SysInfo(1,"Workfolder has been initialized!");
        InitFlag=true;
        return;
    }

    #ifdef _WIN32
    flag=_mkdir(WorkFolderPath.data());
    #elif __APPLE__||__linux__
    flag=mkdir(WorkFolderPath.data(),0777);
    #endif
    if (flag==-1) {
        SysInfo(2,"Create workfolder failed!");
        return;
    }

    InitFlag=true;

    return;
}
/// Process New Message /////////////////////////
static void ProNewMsg(vector<string> CMD)
{
    Log::BLog NewBLog;
    Log::PLog NewPLog;
    Log::FLog NewFLog;

    if (!InitFlag) {
        SysInfo(2,"Workfolder has not been initialized!");
        return;
    }
    if (CMD.size()<3) {
        SysInfo(2,"No '[-arg]' in command '-new'");
        return;
    }
    if (!NewBLog.SetPath(WorkFolderPath+"\\"+CMD[2])) {
        SysInfo(2,"Create log file failed!");
        return;
    }
    if (!NewBLog.Create()) {
        SysInfo(2,"Create log file failed!");
        return;
    }
    SysInfo(0,"Create log file: "+CMD[2]);
    BLogPaths.push_back(CMD[2]);

    return;
}
/// Process Remove Message //////////////////////
static void ProRemMsg(vector<string> CMD)
{
    int i;
    Fhd::FileHandle RMLog;
    
    if (!InitFlag) {
        SysInfo(2,"Workfolder has not been initialized!");
        return;
    }
    if (CMD.size()<3) {
        SysInfo(2,"No '[-arg]' in command '-rm'");
        return;
    }
    for (i=0;i<BLogPaths.size();i++) {
        if (BLogPaths[i]==CMD[2]) {
            RMLog.SetPath(WorkFolderPath+"\\"+CMD[2]);
            RMLog.Remove();
            BLogPaths.erase(BLogPaths.begin()+i);
            SysInfo(0,"Remove log file: "+CMD[2]);
            return;
        }
    }
    return;
}
/// Process Find Message ////////////////////////
static bool ProFindMsg(string FileName)
{
    int i;

    if (!InitFlag) {
        SysInfo(2,"Workfolder has not been initialized!");
        return false;
    }
    if (FileName.empty()) {
        SysInfo(2,"No '[-arg]' in command '-find'");
        return false;
    }
    for (i=0;i<BLogPaths.size();i++) {
        if (BLogPaths[i]==FileName) {
            SysInfo(0,"Find log file: "+BLogPaths[i]);
            return true;
        }
    }
    SysInfo(2,"Can not find log file: "+FileName);
    
    return false;
}
/// Process Add Message /////////////////////////
static void ProAddMsg(vector<string> CMD)
{
   SysInfo(0,"Functions are under development");
   return; 
}
/// Process Delete Message //////////////////////
static void ProDelMsg(vector<string> CMD)
{
   SysInfo(0,"Functions are under development");
   return;
}
/// Process Show Message ////////////////////////
static void ProShowMsg(vector<string> CMD)
{
    int i;

    if (!InitFlag) {
        SysInfo(2,"Workfolder has not been initialized!");
        return;
    }
    SysInfo(-1,"All log files in workfolder:");
    SysInfo(-1," ./log/");
    SysInfo(-1,"  BLog:");
    for (i=0;i<BLogPaths.size();i++) {
        SysInfo(-1,"  |-"+BLogPaths[i]);
    }
    SysInfo(-1,"  PLog:");
    for (i=0;i<PLogPaths.size();i++) {
        SysInfo(-1,"  |-"+PLogPaths[i]);
    }
    SysInfo(-1,"  FLog:");
    for (i=0;i<FLogPaths.size();i++) {
        SysInfo(-1,"  |-"+FLogPaths[i]);
    }
    return;
}
/// Process Find Message //////////////////////////
static void ProFindMsg(vector<string> CMD)
{
    SysInfo(0,"Functions are under development");
    return; 
}
/// Distribute Function ///////////////////////////
void DistrFunc(int Code,vector<string> CMD)
{
    switch (Code) {
       case CODE_NONE:
            SysInfo(-1,"Need help ? input command 'fast -help'");
            break;
       case CODE_HELP: ProHelpMsg(); break;
       case CODE_QUIT: exit(0);      break;
       case CODE_VER:  ProVerMsg();  break;
       case CODE_INIT: ProInitMsg(); break;
       case CODE_NEW:  ProNewMsg(CMD); break;
       case CODE_RM:   ProRemMsg(CMD); break;
       case CODE_ADD:  ProAddMsg(CMD); break;
       case CODE_DEL:  ProDelMsg(CMD); break;
       case CODE_SHOW: ProShowMsg(CMD);break;
       case CODE_FIND: ProFindMsg(CMD);break;
       default: SysInfo(1,"Unknown command '"+CMD[1]+"' !"); break;
    }

    return;
}

///////////////////////////////////////////////////////////////////////////////
/// COMMON FUNCTIONS

/// Convert Time Format From (Sec) to (Cal) /////
CalTime Sec2CalTime(SecTime Time)
{
    CalTime Time_c={0};

    int BC,N1,N2,N3,Y0;
    double JD,J0,dD;

    JD=(Time.Second+Time.Fsecond)/(3600.0*24);

    if (JD<1721423.5) BC=1; /* BC:0001-01-01 0:00 */
    else              BC=0;
 
    if (JD<2299160.5) {
        J0=floor(JD+0.5);
        dD=JD+0.5-J0;
    } else {
        N1=floor((JD-2342031.5)/36524.25/4)+1;// BC:1700-03-01 0:00
        N2=floor((JD-2378555.5)/36524.25/4)+1;// BC:1800-03-01 0:00
        N3=floor((JD-2415079.5)/36524.25/4)+1;// BC:1900-03-01 0:00
        J0=N1+N2+N3+JD+10;
        dD=J0+0.5-floor(J0+0.5);
        J0=floor(J0+0.5);
    }

    J0  =J0+32083;
    Y0  =ceil(J0/365.25)-1;
    Time_c.Year =Y0-4800;
    Time_c.Day  =J0-floor(Y0*365.25);
    Time_c.Month=floor((Time_c.Day-0.6)/30.6)+3;
    Time_c.Day -=round((Time_c.Month-3)*30.6);

    if (Time_c.Month>12) { Time_c.Month-=12; Time_c.Year+=1; }

    Time_c.Year  -=BC;
    Time_c.Second =round(dD*(3600.0*24));
    Time_c.Hour   =floor(Time_c.Second/3600.0);
    Time_c.Second-=Time_c.Hour*3600.0;
    Time_c.Minute =floor(Time_c.Second/60.0);
    Time_c.Second-=Time_c.Minute*60.0;

    return Time_c;
}
/// Convert Time Format From (Cal) to (Sec) /////
SecTime Cal2SecTime(CalTime Time)
{
    SecTime Time_c={0};
    double Hour,JD;

    if (Time.Month> 2) {
        Time.Year=Time.Year;   Time.Month=Time.Month;
    }
    if (Time.Month<=2) {
        Time.Year=Time.Year-1; Time.Month=Time.Month+12;
    }

    Hour =Time.Hour+(Time.Minute/60.0)+(Time.Second/3600.0);
    JD=(int)(365.25*Time.Year)+
        (int)(30.6001*(Time.Month+1))+
        (Time.Day)+(Hour/24.0)+1720981.5;

    JD-=2440587.5000000; // 1970-01-01-00:00:00

    Time_c.Fsecond =JD*3600.0*24;
    Time_c.Second  =(long)Time_c.Fsecond;
    Time_c.Fsecond-=Time_c.Second;

    return Time_c;
}