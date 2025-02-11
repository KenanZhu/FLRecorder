#include "Cmns.h"

///////////////////////////     PRIVATE
bool Cmn::Time::IsSecEmpty(void)
{
    if (sef_SecTime.Second==0&&sef_SecTime.Fsecond==0.0) return true;
    return false;
}

bool Cmn::Time::IsCalEmpty(void)
{
    if      (sef_CalTime.Year ==0) return true;
    else if (sef_CalTime.Month==0) return true;
    else if (sef_CalTime.Day  ==0) return true;

    if (sef_CalTime.Hour  ==0&&sef_CalTime.Minute ==0&&
        sef_CalTime.Second==0&&sef_CalTime.Fsecond==0.0) return true;

    return false;
}

void Cmn::Time::TimeConvert(int *Sign)
{
    // Not Empty or Empty All
    if      (Sign[0]==Sign[1]) {
        return;
    }
    // SecTime is Empty
    else if (Sign[0]==0&&Sign[1]==1) {
        sef_SecTime=Cal2SecTime(sef_CalTime);
        return;
    }
    // CalTime is Empty
    else if (Sign[0]==1&&Sign[1]==0) {
        sef_CalTime=Sec2CalTime(sef_SecTime);
        return;
    }
    return;
}

///////////////////////////     PUBLIC
Cmn::Time::Time(CalTime CalTime)
{
    int Sign[2]={1,1};

    sef_CalTime=CalTime;

    Sign[0]=0;
    if (this->IsCalEmpty()) Sign[1]=0;
    this->TimeConvert(Sign);
}
Cmn::Time::Time(SecTime SecTime)
{
    int Sign[2]={1,1};

    sef_SecTime=SecTime;

    Sign[1]=0;
    if (this->IsSecEmpty()) Sign[0]=0;

    this->TimeConvert(Sign);
}

SecTime Cmn::Time::GetSecTime(void)
{
    return sef_SecTime;
}

CalTime Cmn::Time::GetCalTime(void)
{
    return sef_CalTime;
}

bool Cmn::Time::IsEmpty(void)
{
    return this->IsSecEmpty()||this->IsCalEmpty();
}

double Cmn::Time::Comp(CalTime TargetCalTime)
{
    if (this->IsSecEmpty()) return -2;

    SecTime Temp={0};
    Temp=Cal2SecTime(TargetCalTime);
    return (sef_SecTime.Second+sef_SecTime.Fsecond)-(Temp.Second+Temp.Fsecond);
}

double Cmn::Time::Comp(SecTime TargetSecTime)
{
    if (this->IsSecEmpty()) return -2;
    return (sef_SecTime.Second+sef_SecTime.Fsecond)-(TargetSecTime.Second+TargetSecTime.Fsecond);
}

void Cmn::Time::Add(int Secs, double FSec)
{
    return;
}
