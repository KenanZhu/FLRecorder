#include "CmdLI.h"

/// Command Line Base Class
/// 
///////////////////////////     PRIVATE
void Cli::CliBase::ProLaunchMsg()
{
    cout<<endl;
    cout<<" __________________________________________________________"<<endl;
    cout<<"| >FastLogRecorder Version 0.0.3                           |"<<endl;
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

void Cli::CliBase::ProHelpMsg()
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

void Cli::CliBase::ProVersionMsg()
{
    cout<<" _________________________________________________________ "<<endl;
    cout<<"| >FastLogRecorder Version 0.0.3                          |"<<endl;
    cout<<endl;

    return; 
}

void Cli::CliBase::GetAllFiles(string Dir, vector<string> *Files)
{
    intptr_t hFile=0;
    struct _finddata_t fileinfo={0};
    string p;

    this->PutMessage("Check files in directory..."+Dir);
    if((hFile=_findfirst(p.assign(Dir).append("\\*.*").c_str(),&fileinfo))!=-1) {
        do {
            if((fileinfo.attrib&_A_SUBDIR)) {
                if(strcmp(fileinfo.name,".")!=0&&strcmp(fileinfo.name,"..")!=0)
                    this->GetAllFiles(p.assign(Dir).append("\\").append(fileinfo.name),Files);
            }
            else {
                Files->push_back(p.assign(Dir).append("\\").append(fileinfo.name));
                this->PutMessage("Find file: "+Files->back());
            }
        } while (_findnext(hFile,&fileinfo)==0);
        _findclose(hFile);
    }
}

void Cli::CliBase::UpdateList()
{
    int i,j=0;
    vector<string> LogList;

    this->PutMessage("Update log list...");

    /// Check Work Folder File State
    this->GetAllFiles(WorkFolderPath,&LogList);

    /// Clear Old List
    BLogPaths.clear();
    PLogPaths.clear();
    FLogPaths.clear();

    for (i=0;i<LogList.size();i++) {
        if      (LogList[i].substr(LogList[i].size()-3)=="log") {
            BLogPaths.push_back(LogList[i]); j++;
        }
        else if (LogList[i].substr(LogList[i].size()-4)=="plog") {
            PLogPaths.push_back(LogList[i]); j++;
        }
        else if (LogList[i].substr(LogList[i].size()-4)=="flog") {
            FLogPaths.push_back(LogList[i]); j++;
        }
    }
    this->PutMessage("Find "+to_string(j)+" log files in all lists.");

    return;
}

void Cli::CliBase::ProInitMsg()
{
    int Flag;
    char Path[MAX_PATH]={0};

    if      (InitFlag) {
        this->PutMessage("Workfolder alreay been initialized!");
        return;
    }
    else if (!getcwd(Path,MAX_PATH)) {
        this->PutMessage("Get current run path failed!");
        return;
    }

    /// Set Work Folder Path
    WorkFolderPath=Path;
    WorkFolderPath+="\\log";
    this->PutMessage("Init workfolder path: "+WorkFolderPath);

    /// Detect Work Folder Path
    if (_access(WorkFolderPath.data(),0)!=-1) {
        this->PutMessage("Workfolder alreay exist!");
        this->UpdateList();
        this->PutMessage("Set as workfolder");
        InitFlag=true;
        return;
    }

#ifdef _WIN32
    Flag=_mkdir(WorkFolderPath.data());
#elif __APPLE__||__linux__
    Flag=mkdir(WorkFolderPath.data(),0777);
#endif
    if (Flag==-1) {
        this->PutMessage("Init workfolder failed!"); return;
    }
    InitFlag=true;

    return;
}

int Cli::CliBase::CreateNewLog(int Type,string Path)
{
    Log::BLog NewBLog;
    Log::PLog NewPLog;
    Log::FLog NewFLog;

    switch (Type)
    {
    case FFMT_LOG: 
        NewBLog.SetPath(Path);
        if (NewBLog.Format()!=FFMT_LOG) {
            this->PutMessage("Format not match with name!");
            return 0;
        }
        break;
    case FFMT_PLO: 
        NewPLog.SetPath(Path);
        if (NewPLog.Format()!=FFMT_PLO) {
            this->PutMessage("Format not match with name!");
            return 0;
        }
        break;
    case FFMT_FLO: 
        NewFLog.SetPath(Path);
        if (NewFLog.Format()!=FFMT_FLO) {
            this->PutMessage("Format not match with name!");
            return 0;
        }
        break;
    }
    switch (Type) {
        case FFMT_LOG: 
        NewBLog.Create();
        break;
        case FFMT_PLO: 
        NewPLog.Create();
        break;
        case FFMT_FLO: 
        NewFLog.Create();
        break;
    }
    return 1;
}
void Cli::CliBase::ProNewMsg(vector<string> CMD)
{
    int Flag=0;

    if      (!InitFlag) {
        this->PutMessage("Workfolder has not been initialized!");
    }
    else if (CMD.size()<3) {
        this->PutMessage("No '[-arg]' in command '-new'");
    }
    else {
        if      (CMD.size()==3) {
            Flag=this->CreateNewLog(FFMT_LOG,WorkFolderPath+"\\"+CMD[2]);
            if (Flag==1) {
                BLogPaths.push_back(WorkFolderPath+"\\"+CMD[2]);
                this->PutMessage("Create new file at:"+WorkFolderPath+"\\"+CMD[2]);
                return;
            }
        }
        else if (CMD.size()==4) {
            if      (CMD[2]=="b") {
                Flag=this->CreateNewLog(FFMT_LOG,WorkFolderPath+"\\"+CMD[3]);
                if (Flag==1) {
                    BLogPaths.push_back(WorkFolderPath+"\\"+CMD[3]);
                    this->PutMessage("Create new file at:"+WorkFolderPath+"\\"+CMD[3]);
                    return;
                }
            }
            else if (CMD[2]=="p") {
                Flag=this->CreateNewLog(FFMT_PLO,WorkFolderPath+"\\"+CMD[3]);
                if (Flag==1) {
                    PLogPaths.push_back(WorkFolderPath+"\\"+CMD[3]);
                    this->PutMessage("Create new file at:"+WorkFolderPath+"\\"+CMD[3]);
                    return;
                }
            }
            else if (CMD[2]=="f") {
                Flag=this->CreateNewLog(FFMT_FLO,WorkFolderPath+"\\"+CMD[3]);
                if (Flag==1) {
                    FLogPaths.push_back(WorkFolderPath+"\\"+CMD[3]);
                    this->PutMessage("Create new file at:"+WorkFolderPath+"\\"+CMD[3]);
                    return;
                }
            }
            else {
                this->PutMessage("Unknow log type '"+CMD[2]+"'!");
            }
        }
        else if (CMD.size() >4) {
            this->PutMessage("Too many '[-arg]' in command '-new'");
        }
        return;
    }
    return;
}

void Cli::CliBase::ProRemMsg(vector<string> CMD)
{
    Fhd::FileHandle RMLog;

    if (!InitFlag) {
        this->PutMessage("Workfolder has not been initialized!");
    }
    else if (CMD.size()<3) {
        this->PutMessage("No '[-arg]' in command '-rm'");
    }
    else {
        RMLog.SetPath(WorkFolderPath+"\\"+CMD[2]);
        if (!RMLog.Remove()) this->PutMessage("Not find file"+CMD[2]);
        this->PutMessage("Remove log file: "+CMD[2]);
    }
    return;
}

void Cli::CliBase::ProFindMsg(string FileName)
{
    int i;

    if (!InitFlag) {
        this->PutMessage("Workfolder has not been initialized!");
    }
    else if (FileName.empty()) {
        this->PutMessage("No '[-arg]' in command '-find'");    
    }
    else {
        for (i=0;i<BLogPaths.size();i++) {
            if (BLogPaths[i]==FileName) {
                this->PutMessage("Find log file: "+BLogPaths[i]);
                return;
            }
        }
        this->PutMessage("Can not find log file: "+FileName);
    }
    return;
}

void Cli::CliBase::ProAddMsg(vector<string> CMD)
{
    return; 
}

void Cli::CliBase::ProDelMsg(vector<string> CMD)
{
    return;
}

void Cli::CliBase::ProShowMsg(vector<string> CMD)
{
    int i;

    if      (!InitFlag) {
        this->PutMessage("Workfolder has not been initialized!");
    }
    this->UpdateList();
    this->PutMessage("All log files in workfolder:");
    this->PutMessage("  BLog:");
    for (i=0;i<BLogPaths.size();i++) {
        if (BLogPaths[i].empty()) continue;
        this->PutMessage("  |-"+BLogPaths[i]);
    } this->PutMessage("  PLog:");
    for (i=0;i<PLogPaths.size();i++) {
        if (PLogPaths[i].empty()) continue;
        this->PutMessage("  |-"+PLogPaths[i]);
    } this->PutMessage("  FLog:");
    for (i=0;i<FLogPaths.size();i++) {
        if (FLogPaths[i].empty()) continue;
        this->PutMessage("  |-"+FLogPaths[i]);
    }
    return;
}

void Cli::CliBase::ProFindMsg(vector<string> CMD)
{
    return;
}

int Cli::CliBase::ReplaceStr(string *Str,const char SignDes,const char SignRep)
{
    int i;

    for (i=0;i<Str->size();i++) if (Str->at(i)==SignDes) Str->at(i)=SignDes;
    
    return 1;
}

vector<string> Cli::CliBase::SplitStr(string Str,const char Sign)
{
    int i,j;
    vector<string> StrList;

    for (i=0;i<Str.size()-1;i++) {
        if (Str[i]==Sign) continue;
        for (j=i;j<Str.size();j++) {
            if (Str[j]!=Sign&&j+1!=Str.size()) continue;
            if      (Str[j]==Sign)    j-=1;
            else if (j+1==Str.size()) j+=0;
            StrList.push_back(Str.substr(i,j-i+1));
            i=j; break;
        }
    }
    return StrList;
}

///////////////////////////     PUBLIC
Cli::CliBase::CliBase()
{
    this->ProLaunchMsg();
}

void Cli::CliBase::PutMessage(string Msg)
{
    string LevelSign;

    LevelSign="--";

    cout<<LevelSign+Msg<<endl;

    return;
}

void Cli::CliBase::DistributeCmd(string CMD)
{
    switch (this->DecodeCmd(CMD)) {
        case CODE_NONE:
             this->PutMessage("Need help ? input command 'fast -help'");
             break;
        case CODE_HELP: this->ProHelpMsg();           break;
        case CODE_QUIT: exit(0);                      break;
        case CODE_CLS:  system("cls");                break;
        case CODE_VER:  this->ProVersionMsg();        break;
        case CODE_INIT: this->ProInitMsg();           break;
        case CODE_NEW:  this->ProNewMsg(sef_CmdSect); break;
        case CODE_RM:   this->ProRemMsg(sef_CmdSect); break;
        case CODE_ADD:  this->ProAddMsg(sef_CmdSect); break;
        case CODE_DEL:  this->ProDelMsg(sef_CmdSect); break;
        case CODE_SHOW: this->ProShowMsg(sef_CmdSect);break;
        case CODE_FIND: this->ProFindMsg(sef_CmdSect);break;
        default:        break;
     }
     return;
}

int Cli::CliBase::DecodeCmd(string CMD)
{
    int i;
    vector<string> CmdSplit;
    vector<string> CmdList{"fast" ,"-help","-quit","-cls" ,
                           "-ver" ,"-init","-new" ,"-rm"  ,"-add" ,
                           "-del" ,"-show","-find"};

    if (CMD.empty()) return 0;
    sef_CmdSect.clear();

    CmdSplit=this->SplitStr(CMD,' ');

    if (CmdSplit[0]!=CmdList[0]) {
        this->PutMessage("Invaild command, no 'fast' ");
        return 0;
    }
    if (CmdSplit.size()<2) {
        this->PutMessage("Invaild command, no '[-cmd]' ");
        return CODE_NONE;
    }
    for (i=1;i<CmdList.size();i++)
        if (CmdSplit[1]==CmdList[i]) break;
    if (i>=11) {
        this->PutMessage("Unknow command, '"+CmdSplit[1]+"'");
        return 0;
    }
    sef_CmdSect=CmdSplit;
    
    return i;
}
