///
/// These are the package functions for CmdForge.
///

#ifndef _PACKAPI_H_
#define _PACKAPI_H_

#include "FLRecorder.h"
#include "./LogTypes/LogTypes.h"
#include "./FileHandle/FileHandle.h"

#ifdef _WIN32
#define ACCESS _access
#elif __APPLE__||__linux__
#define ACCESS access
#endif

static bool InitFlag = false;
static string WorkFolderPath;
static vector<string> BLogPaths;
static vector<string> PLogPaths;
static vector<string> FLogPaths;

static void GetAllDirFiles(string Dir, vector<string>* Files)
{
    STDMSG("check files in directory: " + Dir + "...");
#ifdef _WIN32
    intptr_t hFile = 0;
    struct _finddata_t fileinfo = { 0 };
    string p;

    if ((hFile = _findfirst(p.assign(Dir).append("*.*").c_str(), &fileinfo)) != -1) {
        do {
            if ((fileinfo.attrib & _A_SUBDIR)) {
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                    GetAllDirFiles(p.assign(Dir).append(fileinfo.name), Files);
            }
            else {
                Files->push_back(p.assign(Dir).append(fileinfo.name));
            }
        } while (_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }
#elif __APPLE__||__linux__
    DIR* dir;
    struct dirent* ptr;

    if ((dir = opendir(Dir.c_str())) != NULL) {

        while ((ptr = readdir(dir)) != NULL) {
            if (ptr->d_type == DT_DIR) {
                if (strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0)
                    GetAllDirFiles(Dir + ptr->d_name + SLA, Files);
            }
            else {
                Files->push_back(Dir + ptr->d_name);
            }
        }
        closedir(dir);
    }
#endif
    return;
}

static void UpdateFileList(void)
{
    int i, j = 0;
    vector<string> LogList;

    STDMSG("update log list...");

    // Check work folder file State
    GetAllDirFiles(WorkFolderPath, &LogList);

    // Clear old list
    BLogPaths.clear();
    PLogPaths.clear();
    FLogPaths.clear();

    // Reload new list and update
    // we must check file format first or it can cause fatal
    for (i = 0; i < LogList.size(); i++) {
        if (LogList[i].substr(LogList[i].size() - 4) == ".log") {
            BLogPaths.push_back(LogList[i]); j++;
        }
        else if (LogList[i].substr(LogList[i].size() - 5) == ".plog") {
            PLogPaths.push_back(LogList[i]); j++;
        }
        else if (LogList[i].substr(LogList[i].size() - 5) == ".flog") {
            FLogPaths.push_back(LogList[i]); j++;
        }
    }
    STDMSG("find " + to_string(j) + " vaild log files in all lists.");

    return;
}

static int CreateNewLog(int Type,string Path)
{
    Fhd::FileHandle NewLog;
    // There we only regard log as universal file in ASCII
    // so no need to use LogType class, we can use format
    // to check file type

    NewLog.SetPath(Path);
    if (NewLog.Format()!=Type) {
        STDMSG("format not match with name!");
        return 0;
    }
    NewLog.Create();

    return 1;  
}

static int RemoveLog(string Path)
{
    Fhd::FileHandle RMLog;

    RMLog.SetPath(Path);
    if (!RMLog.Remove()) {
        STDMSG("file maybe not exist!");
        return 0; 
    }
    return 1;
}

void PackCmdInit(vector<vector<string>> OptArgs)
{
    int Flag;
    char Path[MAX_PATH] = { 0 };

    if (InitFlag) {
        STDMSG("workfolder alreay been initialized!");
        return;
    }
    else if (!getcwd(Path, MAX_PATH)) {
        STDMSG("get current run path failed!");
        return;
    }

    // Set workfolder path
    WorkFolderPath = Path;
    WorkFolderPath += SLA;
    WorkFolderPath += "log";
    STDMSG("init workfolder path: " + WorkFolderPath);

    // Detect workfolder path
    if (ACCESS(WorkFolderPath.data(), 0) != -1) {
        STDMSG("workfolder alreay exist!");
        STDMSG("try to set as workfolder");
        WorkFolderPath += SLA;
        UpdateFileList();
        InitFlag = true;
        return;
    }

#ifdef _WIN32
    Flag = _mkdir(WorkFolderPath.data());
#elif __APPLE__||__linux__
    Flag = mkdir(WorkFolderPath.data(), 0777);
#endif
    if (Flag == -1) {
        STDMSG("init workfolder failed!"); return;
    }
    WorkFolderPath += SLA;
    InitFlag = true;

    return;
}

void PackCmdNew(vector<vector<string>> OptArgs)
{
    int i,Size,Flag=0,Fmt=0;

    if (!InitFlag) {
        STDMSG("workfolder has not been initialized!");
        return;
    }
    for (i=1;i<OptArgs.size();i++) {
        if (!OptArgs[i].size()) continue;
        CreateNewLog(i+1,WorkFolderPath+OptArgs[i][1]);
    }
    return;
}

void PackCmdRemove(vector<vector<string>> OptArgs)
{
    int i,Size;

    if (!InitFlag) {
        STDMSG("workfolder has not been initialized!");
        return;
    }
    for (i=1;i<OptArgs[1].size();i++) {
        if (!RemoveLog(WorkFolderPath+OptArgs[1][i])) continue;
        STDMSG("removed file: "+OptArgs[1][i]);
    }
    return;
}

void PackCmdShow(vector<vector<string>> OptArgs)
{
    int i;

    if (!InitFlag) {
        STDMSG("workfolder has not been initialized!");
        return;
    }
    UpdateFileList();
    STDMSG("");
    STDMSG("your FLRecorder workfolder is:\n"+WorkFolderPath);
    STDMSG("all log files in workfolder:");
    STDMSG(" [BLog]");
    for (i=0;i<BLogPaths.size();i++) {
        if (BLogPaths[i].empty()) continue;
        STDMSG("    |- "+BLogPaths[i]);
    } 
    STDMSG(" [PLog]");
    for (i=0;i<PLogPaths.size();i++) {
        if (PLogPaths[i].empty()) continue;
        STDMSG("    |- "+PLogPaths[i]);
    } 
    STDMSG(" [FLog]");
    for (i=0;i<FLogPaths.size();i++) {
        if (FLogPaths[i].empty()) continue;
        STDMSG("    |- "+FLogPaths[i]);
    }
    return;
}

#endif // !_PACKAPI_H_