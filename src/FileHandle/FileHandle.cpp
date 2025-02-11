#include "FileHandle.h"

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

inline bool Fhd::FileHandle::IsExist()
{
    if (this->IsOpen()) return true;
    if (sef_FilePath.empty()||sef_FilePath.size()>=MAX_PATH) return false;

    sef_FileHand.open(sef_FilePath,ios::in);
    if (!sef_FileHand.is_open()) {
        return false;
    }
    this->Close();

    return true;
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

void Fhd::FileHandle::PutMessage(int Level,string Msg)
{
    std::string LevelSign;

    if (Level<LEVEL_1) CliBase::PutMessage(LEVEL_0,Msg);
    if (Level>LEVEL_1) return;

    LevelSign="[-Inh] FileHandle ";
    CliBase::PutMessage(LEVEL_0,LevelSign+Msg);

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
    // File Format Already Be Confirmed
    if (sef_FileFormat>FFMT_NON) return sef_FileFormat;

    // For File Format is Not Be Confirmed
    if      (ExpName==".txt")  return sef_FileFormat=FFMT_TXT;
    else if (ExpName==".log")  return sef_FileFormat=FFMT_LOG;
    else if (ExpName==".plog") return sef_FileFormat=FFMT_PLO;
    else if (ExpName==".flog") return sef_FileFormat=FFMT_FLO;

    return FFMT_NON;
}

int Fhd::FileHandle::SetPath(string FilePath)
{
    if (FilePath.empty()||FilePath.size()>MAX_PATH) return 0;
    if (!sef_FilePath.empty()) this->Init();
    sef_FilePath=FilePath;

    return 1;
}

bool Fhd::FileHandle::Open()
{
    int p[2];
    string ExpName;

    // File Already Be Open
    if (this->IsOpen()) return sef_FileState=true;

    // Detect File
    if (!this->IsExist()) {
        this->PutMessage(1,"Open-> File is not exist");
        return sef_FileState=false;
    }
    sef_FileHand.open(sef_FilePath);

    // Get File Name (exclude expansion name)
    if      ((p[0]=sef_FilePath.rfind("\\"))!=string::npos) 
        sef_FileName=sef_FilePath.substr(p[0]+1);
    else if ((p[0]=sef_FilePath.rfind("/" ))!=string::npos)
        sef_FileName=sef_FilePath.substr(p[0]+1);

    p[1]=sef_FileName.rfind(".");
    ExpName =sef_FileName.substr(p[1]);
    sef_FileName=sef_FileName.substr(0,p[1]);

    // Get File Format by Expansion Name
    this->Format(ExpName);

    return sef_FileState=true;
}

bool Fhd::FileHandle::Create(void)
{
    this->PutMessage(1,"Create-> Try to create file at:"+sef_FilePath);

    sef_FileHand.open(sef_FilePath,ios::out);
    if (!sef_FileHand.is_open()) {
       this->PutMessage(1,"Create-> Fail to create, Check permissions and try again");
       return false;
    }
    this->PutMessage(1,"Create-> Ok !");
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