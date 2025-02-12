#ifndef _CMFLI_H_
#define _CMFLI_H_

#include "..\FLRecorder.h"
#include "..\LogTypes\LogTypes.h"
#include "..\FileHandle\FileHandle.h"

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
private:
    // CLI: Launch Message
    void ProLaunchMsg(void);

    // CLI: Help Message
    void ProHelpMsg(void);

    // CLI: Version Message
    void ProVersionMsg(void);

    // CLI Dependent Functions
    void GetAllFiles(string Dir,vector<string> *Files);
    int CreateNewLog(int Type,string Path);
    void UpdateList(void);

    virtual void ProInitMsg(void);
    virtual void ProNewMsg (vector<string> CMD);
    virtual void ProRemMsg (vector<string> CMD);
    virtual void ProFindMsg(string FileName   );
    virtual void ProAddMsg (vector<string> CMD);
    virtual void ProDelMsg (vector<string> CMD);
    virtual void ProShowMsg(vector<string> CMD);
    virtual void ProFindMsg(vector<string> CMD);

    // Replace Sign by Sign
    int ReplaceStr(string *Str,const char SignDes,const char SignRep);
    
    // Split String By Sign
    vector<string> SplitStr(string Str,const char Sign);

public:
    CliBase();

    // Command Section Vector
    vector<string> sef_CmdSect;

    // Put Message On Console
    void PutMessage(string Msg);

    // Distribute Command
    void DistributeCmd(string CMD);

    // Decode Command
    int DecodeCmd(string CMD);
};

}

#endif // !_CMFLI_H_