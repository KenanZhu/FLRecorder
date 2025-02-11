#ifndef _CMFLI_H_
#define _CMFLI_H_

#include "..\FLRecorder.h"

#define LEVEL_0 0 // Message Level: Base Class
#define LEVEL_1 1 // Message Level: Inherit Class
#define LEVEL_2 2 // Message Level: Spare

/// 
/// Command Line Interface Class
/// 
namespace Cli {

/// Command Line Base Class
/// 
class CliBase
{
protected:
    int sef_Level;
private:

    // Replace Sign by Sign
    int ReplaceStr(string *Str,const char SignDes,const char SignRep);
    
    // Split String By Sign
    vector<string> SplitStr(string Str,const char Sign);

public:
    CliBase(int Level=LEVEL_2);

    // Command Section Vector
    vector<string> sef_CmdSect;

    // Put Message On Console
    void PutMessage(int Level,string Msg);

    // Decode Command
    virtual int DecodeCmd(string CMD);
};

}

#endif // !_CMFLI_H_
