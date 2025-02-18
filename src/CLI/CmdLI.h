#ifndef _CMFLI_H_
#define _CMFLI_H_

#include "../FLRecorder.h"
#include "../LogTypes/LogTypes.h"
#include "../FileHandle/FileHandle.h"

/// 
/// Command Line Interface Namespace
/// 
namespace Cli {

/// Command Line Base Class
/// 
class CliBase
{
protected:
    bool InitFlag=false;
    string WorkFolderPath;
    vector<string> BLogPaths;
    vector<string> PLogPaths;
    vector<string> FLogPaths;

    // Command Section Vector
    vector<string> sef_CmdSect;

    // Command index vector
    vector<string> sef_CmdList
    {
        "fast" , // Main command list

        //    1       2       3      4            //
        "-help","-quit","-cls" ,"-ver" , "-init", // 5
        "-new" ,"-rm"  ,"-add" ,"-del" , "-show", // 10
        "-find"                                   // 15
    };

private:
    // CLI: output launch message
    void ProLaunchMsg(void);

    // CLI: output help message
    void ProHelpMsg(void);

    // CLI: output version message
    void ProVersionMsg(void);

    // CLI dependent functions
    //
    // Get all files in destination folder
    void GetAllFiles(string Dir,vector<string> *Files);

    // Create new log file in workfolder
    int CreateNewLog(int Type,string Path);

    // Update log list
    void UpdateList(void);

    // Virtual : you can modifty these functions by your
    // own logic, in other words, this just a CLI complish example
    virtual void ProInitMsg(void);
    virtual void ProNewMsg (vector<string> CMD);
    virtual void ProRemMsg (vector<string> CMD);
    virtual void ProFindMsg(vector<string> CMD);
    virtual void ProAddMsg (vector<string> CMD);
    virtual void ProDelMsg (vector<string> CMD);
    virtual void ProShowMsg(vector<string> CMD);

    // Replace char by sign
    int ReplaceStr(string *Str,const char SignDes,const char SignRep);
    
    // Split string by sign
    vector<string> SplitStr(string Str,const char Sign);

public:
    CliBase();

    // Put Message On Console
    void PutMessage(string Msg);

    // Distribute Command
    void DistributeCmd(string CMD);

    // Decode Command
    int DecodeCmd(string CMD);
};

}

#endif // !_CMFLI_H_