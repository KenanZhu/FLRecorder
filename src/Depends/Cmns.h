#ifndef _CMNS_H_
#define _CMNS_H_

#include "..\FLRecorder.h"

/// 
/// Common Depends Classes
/// 
namespace Cmn {

/// Common Depends
/// 
class Time
{
protected:
    SecTime sef_SecTime;
    CalTime sef_CalTime;
private:
    // Get Time State: SecTime State
    bool IsSecEmpty(void);

    // Get Time State: CalTime State
    bool IsCalEmpty(void);

    // Convert Time Format
    void TimeConvert(int *Sign);
public:
    Time(CalTime _CalTime);
    Time(SecTime _SecTime);

    // Get sef_SecTime
    SecTime GetSecTime(void);

    // Get sef_CalTime
    CalTime GetCalTime(void);

    // Get Time State
    bool IsEmpty(void);

    // Compare Time With Target Time
    double Comp(CalTime TargetCalTime);
    double Comp(SecTime TaretSecTime);

    // Add Seconds/Fraction-Second
    void Add(int Secs,double FSec=0.0);
};

}

#endif // !_CMNS_H_