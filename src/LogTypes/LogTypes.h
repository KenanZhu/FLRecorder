#ifndef _LOGTYPES_H_
#define _LOGTYPES_H_

#include "..\FLRecorder.h"
#include "..\Depends\Cmns.h"
#include "..\FileHandle\FileHandle.h"

/// CONSTANT ///
#define MAX_LOG_TIME_JUMP 2    // Max Jump of Log Time Stamp
#define MAX_INV_LOGS_RATE 5E-2 // Max Rate of Invaild Log Records

/// 
/// Log Classes
/// 
namespace Log{

/// Log Basic Class
/// 
class BLog:public Fhd::FileHandle
{
protected:
    int sef_MaxLogs;
    int sef_LogAmount;
    bool sef_LogState;
private:
    // Self-Methord
    void Init(int MaxLogs);

    // Convert String to Date
    CalTime String2Date(string StringDate);

    // Detect Log Sign
    bool DetectLogSign(string DetectLine);
    
    // Detect Time Stamp 
    int DetectTimeStamp(string PreLine,string CurLine,double *Dt);
    
    // Detect Log Message
    bool DetectLog(string PreLine,string CurLine,double *Dt,int *p);
public:
    BLog(int MaxLogs=MAX_LOGS);

    // ReWrite Base Class
    void PutMessage(string Msg);

    // Add Log Record
    bool AddLog(string LogMsg=" ");

    // Delete Log Record
    bool DelLog(string LogMsg=" ");

    // Check Log Vaild
    bool CheckLog(void);

    // Correct Invaild Log
    bool CorrectLog(void);
};

/// Project Log Constructer Class
/// 
class PLog:public BLog
{
protected:
private:
public:
};

/// Fast Project Log Constructer Class
/// 
class FLog:public BLog
{
protected:
private:
public:
};

}

#endif // !_LOGTYPES_H_