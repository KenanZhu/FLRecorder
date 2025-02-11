#include "CmdLI.h"

///////////////////////////     PRIVATE
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
Cli::CliBase::CliBase(int Level)
{
    sef_Level=Level;
}

void Cli::CliBase::PutMessage(int Level,string Msg)
{
    string LevelSign;

    if (Level>sef_Level) return;
    LevelSign="[-Bas] CliBase ";

    cout<<LevelSign+Msg<<endl;

    return;
}

int Cli::CliBase::DecodeCmd(string CMD)
{
    int i;
    vector<string> CmdSplit;
    vector<string> CmdList{"fast" ,"-help","-quit","-ver" ,
                           "-init","-new" ,"-rm"  ,"-add" ,
                           "-del" ,"-show","-find"};

    if (CMD.empty()) return 0;
    sef_CmdSect.clear();

    CmdSplit=this->SplitStr(CMD,' ');

    if (CmdSplit[0]!=CmdList[0]) {
        this->PutMessage(0,"DecodeCmd-> Invaild command, no 'fast' ");
        return 0;
    }
    if (CmdSplit.size()<2) {
        this->PutMessage(0,"DecodeCmd-> Invaild command, no '[-cmd]' ");
        return CODE_NONE;
    }
    for (i=1;i<CmdList.size();i++)
        if (CmdSplit[1]==CmdList[i]) break;
    if (i>=11) {
        this->PutMessage(0,"DecodeCmd-> Unknow command, '"+CmdSplit[1]+"'");
        return 0;
    }
    sef_CmdSect=CmdSplit;
    
    return i;
}
