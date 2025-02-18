#ifndef _LOGTYPES_H_
#define _LOGTYPES_H_

#include "../FLRecorder.h"
#include "../Depends/Cmns.h"
#include "../FileHandle/FileHandle.h"

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
    // Self-methord
    void Init(int MaxLogs);

    // Convert string to date
    CalTime String2Date(string StringDate);

    // Detect log sign
    bool DetectLogSign(string DetectLine);
    
    // Detect time stamp 
    int DetectTimeStamp(string PreLine,string CurLine,double *Dt);
    
    // Detect log message
    bool DetectLog(string PreLine,string CurLine,double *Dt,int *p);
public:
    BLog(int MaxLogs=MAX_LOGS);

    // ReWrite base class form class Fhd::FileHandle
    void PutMessage(string Msg);

    // Add log record, when argument is empty,
    // add empty log record, but this will cause warning or reject
    // on methord 'CheckLog()'
    bool AddLog(string LogMsg=" ");

    // Delete log record, when argument is empty,
    // delete all log records
    bool DelLog(string LogMsg=" ");

    // Check log vaild, mainly for check log time stamp jump
    bool CheckLog(void);

    // Correct invaild log
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