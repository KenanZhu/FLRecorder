#include "CmdLI.h"

#ifdef _WIN32
    #define ACCESS _access
#elif __APPLE__||__linux__
    #define ACCESS access
#endif

/// Command Line Base Class
/// 
///////////////////////////     PRIVATE
void Cli::CliBase::ProLaunchMsg()
{
    cout<<endl;
    cout<<" __________________________________________________________"<<endl;
    cout<<"| >FastLogRecorder Version 0.0.5                           |"<<endl;
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
    cout<<"| >FastLogRecorder Version 0.0.5                          |"<<endl;
    cout<<endl;

    return; 
}

void Cli::CliBase::GetAllFiles(string Dir, vector<string> *Files)
{

    this->PutMessage("check files in directory..."+Dir);

#ifdef _WIN32
    intptr_t hFile=0;
    struct _finddata_t fileinfo={0};
    string p;

    if((hFile=_findfirst(p.assign(Dir).append("*.*").c_str(),&fileinfo))!=-1) {
        do {
            if((fileinfo.attrib&_A_SUBDIR)) {
                if(strcmp(fileinfo.name,".")!=0&&strcmp(fileinfo.name,"..")!=0)
                    this->GetAllFiles(p.assign(Dir).append(fileinfo.name),Files);
            }
            else {
                Files->push_back(p.assign(Dir).append(fileinfo.name));
            }
        } while (_findnext(hFile,&fileinfo)==0);
        _findclose(hFile);
    } 
#elif __APPLE__||__linux__
    DIR *dir;
    struct dirent *ptr;

    if ((dir=opendir(Dir.c_str()))!=NULL) {
        
        while ((ptr=readdir(dir))!=NULL) {
            if (ptr->d_type==DT_DIR) {
                if (strcmp(ptr->d_name,".")!=0&&strcmp(ptr->d_name,"..")!=0)
                this->GetAllFiles(Dir+ptr->d_name+SLA,Files);
            }
            else {
                Files->push_back(Dir+ptr->d_name);
            }
        }
        closedir(dir);
    }
#endif
    return;
}

void Cli::CliBase::UpdateList()
{
    int i,j=0;
    vector<string> LogList;

    this->PutMessage("update log list...");

    // Check work folder file State
    this->GetAllFiles(WorkFolderPath,&LogList);

    // Clear old list
    BLogPaths.clear();
    PLogPaths.clear();
    FLogPaths.clear();

    // Reload new list and update
    // we must check file format first or it can cause fatal
    for (i=0;i<LogList.size();i++) {
        if      (LogList[i].substr(LogList[i].size()-4)==".log") {
            BLogPaths.push_back(LogList[i]); j++;
        }
        else if (LogList[i].substr(LogList[i].size()-5)==".plog") {
            PLogPaths.push_back(LogList[i]); j++;
        }
        else if (LogList[i].substr(LogList[i].size()-5)==".flog") {
            FLogPaths.push_back(LogList[i]); j++;
        }
    }
    this->PutMessage("find "+to_string(j)+" vaild log files in all lists.");

    return;
}

void Cli::CliBase::ProInitMsg()
{
    int Flag;
    char Path[MAX_PATH]={0};

    if (InitFlag) {
        this->PutMessage("workfolder alreay been initialized!");
        return;
    }
    else if (!getcwd(Path,MAX_PATH)) {
        this->PutMessage("get current run path failed!");
        return;
    }

    // Set workfolder path
    WorkFolderPath=Path;
    WorkFolderPath+=SLA;
    WorkFolderPath+="log";
    this->PutMessage("init workfolder path: "+WorkFolderPath);

    // Detect workfolder path
    if (ACCESS(WorkFolderPath.data(),0)!=-1) {
        this->PutMessage("workfolder alreay exist!");
        this->PutMessage("try to set as workfolder");
        WorkFolderPath+=SLA;
        this->UpdateList();
        InitFlag=true;
        return;
    }

#ifdef _WIN32
    Flag=_mkdir(WorkFolderPath.data());
#elif __APPLE__||__linux__
    Flag=mkdir(WorkFolderPath.data(),0777);
#endif
    if (Flag==-1) {
        this->PutMessage("init workfolder failed!"); return;
    }
    WorkFolderPath+=SLA;
    InitFlag=true;

    return;
}

int Cli::CliBase::CreateNewLog(int Type,string Path)
{
    Fhd::FileHandle NewLog;
    // There we only regard log as universal file in ASCII
    // so no need to use LogType class, we can use format
    // to check file type

    NewLog.SetPath(Path);
    if (NewLog.Format()!=Type) {
        this->PutMessage("format not match with name!");
        return 0;
    }
    NewLog.Create();

    return 1;
}

void Cli::CliBase::ProNewMsg(vector<string> CMD)
{
    int Flag=0,Fmt=0;

    if (!InitFlag) {
        this->PutMessage("workfolder has not been initialized!");
    }
    else if (CMD.size()< 3) {
        this->PutMessage("no '[-arg]' in command '-new'");
    }
    else if (CMD.size()==3) {
        Fmt=FFMT_LOG;
        this->CreateNewLog(Fmt,WorkFolderPath+CMD[2]);
    }
    else if (CMD.size()==4) {
        if      (CMD[2]=="-b") Fmt=FFMT_LOG;
        else if (CMD[2]=="-p") Fmt=FFMT_PLO;
        else if (CMD[2]=="-f") Fmt=FFMT_FLO;
        else {
            this->PutMessage("unknow log type! only support '-b','-p','-f'");
            return;
        }
        this->CreateNewLog(Fmt,WorkFolderPath+CMD[3]);
    }
    else {
        this->PutMessage("too many '[-arg]' in command '-new'");
    }
    return;
}

void Cli::CliBase::ProRemMsg(vector<string> CMD)
{
    Fhd::FileHandle RMLog;

    if (!InitFlag) {
        this->PutMessage("workfolder has not been initialized!");
    }
    else if (CMD.size()<3) {
        this->PutMessage("no '[-arg]' in command '-rm'");
    }
    else {
        RMLog.SetPath(WorkFolderPath+CMD[2]);
        if (!RMLog.Remove()) { 
            this->PutMessage("file: "+CMD[2]+" maybe not exist!");
            return; 
        }
        this->PutMessage("remove log file: "+CMD[2]);
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

    if (!InitFlag) {
        this->PutMessage("workfolder has not been initialized!");
        return;
    }
    this->UpdateList();
    this->PutMessage("all log files in workfolder:");
    this->PutMessage(" [BLog]");
    for (i=0;i<BLogPaths.size();i++) {
        if (BLogPaths[i].empty()) continue;
        this->PutMessage("    |- "+BLogPaths[i]);
    } 
    this->PutMessage(" [PLog]");
    for (i=0;i<PLogPaths.size();i++) {
        if (PLogPaths[i].empty()) continue;
        this->PutMessage("    |- "+PLogPaths[i]);
    } 
    this->PutMessage(" [FLog]");
    for (i=0;i<FLogPaths.size();i++) {
        if (FLogPaths[i].empty()) continue;
        this->PutMessage("    |- "+FLogPaths[i]);
    }
    return;
}

void Cli::CliBase::ProFindMsg(vector<string> CMD)
{
    int i;
    string TemPath;

    if (!InitFlag) {
        this->PutMessage("workfolder has not been initialized!");
    }
    else if (CMD.size()<=2) {
        this->PutMessage("no '[-arg]' in command '-find'");
    }
    else if (CMD[2].empty()) {
        this->PutMessage("no '[-arg]' in command '-find'");
    }
    else {
        TemPath=WorkFolderPath+CMD[2];
        for (i=0;i<BLogPaths.size();i++) if (BLogPaths[i]==TemPath) {this->PutMessage("file exist"); return;}
        for (i=0;i<PLogPaths.size();i++) if (PLogPaths[i]==TemPath) {this->PutMessage("file exist"); return;}
        for (i=0;i<FLogPaths.size();i++) if (FLogPaths[i]==TemPath) {this->PutMessage("file exist"); return;}
        this->PutMessage("file is not exist");
    }
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

    LevelSign="  ";

    cout<<LevelSign+Msg<<endl;

    return;
}

void Cli::CliBase::DistributeCmd(string CMD)
{
    switch (this->DecodeCmd(CMD)) {
        case CODE_NONE:
             this->PutMessage("need help ? input command 'fast -help'");
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

    if (CMD.empty()) return 0;
    sef_CmdSect.clear();
    
    // Split command by blank, so we can distinguish different command
    // there we can know that:
    // [0] should be "fast" [1] should be "-cmd" and the rest is
    // [2]~[n] should be "-arg"
    CmdSplit=this->SplitStr(CMD,' ');

    if (CmdSplit[0]!=sef_CmdList[0]) {
        this->PutMessage("invaild command, no 'fast' ");
        return CODE_NONE;
    }
    if (CmdSplit.size()<2) {
        this->PutMessage("invaild command, no '[-cmd]' ");
        return CODE_NONE;
    }
    for (i=1;i<sef_CmdList.size();i++)
        if (CmdSplit[1]==sef_CmdList[i]) break;
    if (i>11) {
        this->PutMessage("unknow command, '"+CmdSplit[1]+"'");
        return CODE_NONE;
    }
    sef_CmdSect=CmdSplit;
    
    return i;
}
