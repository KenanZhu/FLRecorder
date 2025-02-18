#ifndef _CMNS_H_
#define _CMNS_H_

#include "../FLRecorder.h"

/// -DATA TYPE ///
typedef struct {    // Second with Fraction-Second Format
    long Second;    // Second
    double Fsecond; // Fraction-Second
} SecTime;          
                    
typedef struct {    // Time Struct in Cal Format 
    int Year;       // Year   YYYY
    int Month;      // Month  MM
    int Day;        // Day    DD
    int Hour;       // Hour   HH
    int Minute;     // Minute mm
    int Second;     // Second ss
    double Fsecond; // Fraction-Second
} CalTime;

/// -FUNCTIONS ///
extern CalTime Sec2CalTime(SecTime Time);
extern SecTime Cal2SecTime(CalTime Time);

/// 
/// Common Depends Classes
/// 
namespace Cmn {

/// Common Depends Class
/// 
class Time
{
protected:
    SecTime sef_SecTime;
    CalTime sef_CalTime;
private:
    // Get time state: SecTime state
    bool IsSecEmpty(void);

    // Get time state: CalTime state
    bool IsCalEmpty(void);

    // Convert time format
    void TimeConvert(int *Sign);
public:
    Time(CalTime _CalTime);
    Time(SecTime _SecTime);

    // Get sef_SecTime
    SecTime GetSecTime(void);

    // Get sef_CalTime
    CalTime GetCalTime(void);

    // Get time state
    bool IsEmpty(void);

    // Compare time with target time
    double Comp(CalTime TargetCalTime);
    double Comp(SecTime TaretSecTime);

    // Add seconds/fraction-second
    void Add(int Secs,double FSec=0.0);
};

}

#endif // !_CMNS_H_