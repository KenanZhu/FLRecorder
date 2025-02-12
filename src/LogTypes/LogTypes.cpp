#include "LogTypes.h"

///////////////////////////     PRIVATE
void Log::BLog::Init(int MaxLogs)
{
    sef_MaxLogs=MaxLogs;
    sef_LogAmount=0;
    sef_LogState=sef_FileState;
    return;
}

CalTime Log::BLog::String2Date(string StringDate)
{
    int Sign=1;
    CalTime Date={0};

    try {Date.Year  =stoi(StringDate.substr( 0,4),0,10);}
    catch (invalid_argument) { Sign=0;}
    try {Date.Month =stoi(StringDate.substr( 5,2),0,10);}
    catch (invalid_argument) { Sign=0;}
    try {Date.Day   =stoi(StringDate.substr( 8,2),0,10);}
    catch (invalid_argument) { Sign=0;}
    try {Date.Hour  =stoi(StringDate.substr(11,2),0,10);}
    catch (invalid_argument) { Sign=0;}
    try {Date.Minute=stoi(StringDate.substr(14,2),0,10);}
    catch (invalid_argument) { Sign=0;}
    try {Date.Second=stoi(StringDate.substr(17,2),0,10);}
    catch (invalid_argument) { Sign=0;}

    if (Sign==0) {
        Date.Year=Date.Month =Date.Day=0;
        Date.Hour=Date.Minute=Date.Second=0;
        Date.Fsecond=0.0;
    }
    return Date;
}

bool Log::BLog::DetectLogSign(string DetectLine)
{
    if (DetectLine.find("[INFO   ]")==string::npos&&
        DetectLine.find("[WARNING]")==string::npos&&
        DetectLine.find("[ERROR  ]")==string::npos&&
        DetectLine.find("[FATAL  ]")==string::npos&&
        DetectLine.find("[UNKNOW ]")) return false;
    return true;
}

int Log::BLog::DetectTimeStamp(string PreLine,string CurLine,double *Dt)
{
    double Dt0,Dt1;

    // Only Support FLR Log Format:
    // [ LEVEL ] YYYY-MM-DD hh:mm:ss :Message.
    Cmn::Time PreT(this->String2Date(PreLine.substr(10,19)));
    Cmn::Time CurT(this->String2Date(CurLine.substr(10,19)));

    if (PreT.IsEmpty()) return -1;
    if (CurT.IsEmpty()) return -2;
    
    Dt1=round(CurT.Comp(PreT.GetSecTime()));
    Dt0=Dt[0]; Dt[0]=Dt1;

    if (Dt1<0) {
        if ((Dt0*Dt1)<0) { // Previous Record Detected
            this->PutMessage("V Time stamp detected jump=(Dt0="+to_string(Dt0)+", Dt1="+to_string(Dt1));
            return -3;
        }
        // Current Record Detected
        this->PutMessage("V Time stamp detected jump=(Dt0="+to_string(Dt0)+", Dt1="+to_string(Dt1));
        return -4;
    }
    if (Dt1>0) {
        if (fabs(Dt1)< MAX_LOG_TIME_JUMP) return 1; // No Record Detected
        if (fabs(Dt1)>=MAX_LOG_TIME_JUMP) {
            if ((Dt1-Dt0)>MAX_LOG_TIME_JUMP) { // Previous Record Detected
                this->PutMessage("Λ Time stamp detected jump=(Dt0="+to_string(Dt0)+", Dt1="+to_string(Dt1));
                return -3;
            }
        }
    }
    return 1;
}

bool Log::BLog::DetectLog(string PreLine,string CurLine,double *Dt,int *p)
{
    // Check Log Record Length

    // WARN: Lower
    if (PreLine.size()<=MIN_LINE||CurLine.size()<=MIN_LINE) {
        this->PutMessage("(Lower_Min_Line): "+CurLine);
        return false;
    }

    // WARN: Over Maxline
    if (PreLine.size()>MAX_LINE||CurLine.size()>MAX_LINE) {
        this->PutMessage("(Over_Max_Line): "+CurLine);
        return false;
    }

    // Check Date/Time Stamp

    // WARN: No Log Sign
    if (!this->DetectLogSign(CurLine)) {
        this->PutMessage("(No_Log_Sign): "+CurLine);
        return false;
    }
    
    switch (this->DetectTimeStamp(PreLine,CurLine,Dt))
    {
    // WARN: No Time Stamp
    case-1: this->PutMessage("(No_Time_Stamp): "+PreLine); return false;
    case-2: this->PutMessage("(No_Time_Stamp): "+CurLine); return false;
    // WARN: Time Stamp Jump
    case-3: this->PutMessage("(Time_Jump): "+PreLine); *p=-1; return false;
    case-4: this->PutMessage("(Time_Jump): "+CurLine); *p= 0; return false;
    }
    return true;
}

///////////////////////////     PUBLIC
Log::BLog::BLog(int MaxLogs)
{
    this->Init(MaxLogs);
}

void Log::BLog::PutMessage(string Msg)
{
    Fhd::FileHandle::PutMessage(Msg);
    return;
}

bool Log::BLog::AddLog(string LogMsg)
{
    this->Close();
    if (sef_FilePath.empty()) {
        this->PutMessage("No log file path");
        return false;
    }
    sef_FileHand.open(sef_FilePath,ios::app);
    
    sef_FileHand<<LogMsg<<endl;
    sef_LogAmount++;
    sef_FileHand.close();
    
    return true;
}

bool Log::BLog::DelLog(string LogMsg)
{
    this->Close();
    if (sef_FilePath.empty()) {
        this->PutMessage("No log file path");
        return false;
    }

    return false;
}

bool Log::BLog::CheckLog(void)
{
    int p,Counter[2]={0}; // [0]: Amount Counter[1]: Bad Log Record Counter
    double Dt[2]={0}; // Time Difference
    string Line[2]; // [0]: Previous Line[1]: Current Line

    if (!this->IsOpen()) return false;

    while (getline(sef_FileHand,Line[1])) {
        Counter[0]++; p=0;

        if (Counter[0]>=100&&(((double)Counter[1]/(double)Counter[0])>MAX_INV_LOGS_RATE)) {
            this->Close();
            this->PutMessage("fail (Over_Max_Invaild_Log_Rate)");
            return sef_LogState=false;
        }
        if (Counter[0]>=1+1&&!this->DetectLog(Line[0],Line[1],Dt,&p)) {
            if (!CorrectLog()) {
                Counter[1]++;
                this->PutMessage("invaild record, Line="+std::to_string(Counter[0]+p));
            }
        }
        Line[0]=Line[1];
    }
    if (((sef_LogAmount=Counter[0])-Counter[1])>MAX_LOGS) {
        this->PutMessage("Fail (Over_Max_Logs)");
        return false;
    }
    this->PutMessage("Ok !");
    return true;
}

bool Log::BLog::CorrectLog()
{
    return false;
}
