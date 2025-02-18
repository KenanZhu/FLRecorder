#include "FileHandle.h"

/// File Handle Basic Class
///
///////////////////////////     PRIVATE
void Fhd::FileHandle::Init()
{
    sef_FilePath="";
    sef_FileName="";
    sef_FileState=false;
    sef_FileFormat=FFMT_NON;
    this->Close();
    return;
}

///////////////////////////     PUBLIC
Fhd::FileHandle::FileHandle()
{
    this->Init();
}

Fhd::FileHandle::~FileHandle()
{
    this->Init();
}

void Fhd::FileHandle::PutMessage(string Msg)
{
    string LevelSign;

    LevelSign="--";

    cout<<LevelSign+Msg<<endl;

    return;
}

std::string Fhd::FileHandle::Path()
{
    return sef_FilePath;
}

std::string Fhd::FileHandle::Name()
{
    return sef_FileName;
}

int Fhd::FileHandle::Format(string ExpName)
{
    // File format already be confirmed
    if (sef_FileFormat>FFMT_NON) return sef_FileFormat;

    // For file format is not be confirmed
    if      (ExpName==".txt")  return sef_FileFormat=FFMT_TXT;
    else if (ExpName==".log")  return sef_FileFormat=FFMT_LOG;
    else if (ExpName==".plog") return sef_FileFormat=FFMT_PLO;
    else if (ExpName==".flog") return sef_FileFormat=FFMT_FLO;

    return FFMT_NON;
}

int Fhd::FileHandle::SetPath(string FilePath)
{
    int p[2]={0};
    string ExpName;

    if (FilePath.empty()||FilePath.size()>MAX_PATH) return 0;
    if (!sef_FilePath.empty()) this->Init();
    sef_FilePath=FilePath;

    // Get file name (exclude expansion name)
    if      ((p[0]=sef_FilePath.rfind(SLA))!=string::npos)
        sef_FileName=sef_FilePath.substr(p[0]+1);

    // Reject misatake in file format
    p[1]=sef_FileName.rfind(".")==string::npos?0:sef_FileName.rfind(".");
    if (p[0]*p[1]==0) return 0;
    
    ExpName=sef_FileName.substr(p[1]);
    sef_FileName=sef_FileName.substr(0,p[1]);

    // Get file format by rxpansion name
    this->Format(ExpName);

    return 1;
}

bool Fhd::FileHandle::Create(void)
{
    this->PutMessage("Try to create file at:"+sef_FilePath);

    if (this->IsExist()) {
        this->PutMessage("File already exist");
        return true;
    }
    sef_FileHand.open(sef_FilePath,ios::out);
    if (!sef_FileHand.is_open()) {
       this->PutMessage("Fail to create, Check permissions and try again");
       return false;
    }
    this->PutMessage("Ok !");
    this->Close();

    return true;
}

bool Fhd::FileHandle::Remove(void)
{
    this->Close();
    if (sef_FilePath.empty()) return false;
    if (remove(sef_FilePath.data())==0) {
        this->Init();
        return true;
    }
    else return false;
}

inline bool Fhd::FileHandle::IsExist()
{
    if (this->IsOpen()) return true;
    if (sef_FilePath.empty()||sef_FilePath.size()>=MAX_PATH) return false;

    sef_FileHand.open(sef_FilePath,ios::in);
    if (!sef_FileHand.is_open()) {
        this->PutMessage("File is not exist");
        return false;
    }
    this->Close();

    return true;
}

bool Fhd::FileHandle::IsOpen()
{
    return sef_FileHand.is_open();
}

bool Fhd::FileHandle::IsEof()
{
    return sef_FileHand.eof();
}

void Fhd::FileHandle::Close()
{
    if(sef_FileHand.is_open()) sef_FileHand.close();
    return;
}