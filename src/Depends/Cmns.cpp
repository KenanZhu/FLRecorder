#include "Cmns.h"

/// Convert time format from (sec) to (cal) /////
CalTime Sec2CalTime(SecTime Time)
{
    CalTime Time_c={0};

    int BC,N1,N2,N3,Y0;
    double JD,J0,dD;

    JD=(Time.Second+Time.Fsecond)/(3600.0*24);

    if (JD<1721423.5) BC=1; /* BC:0001-01-01 0:00 */
    else              BC=0;
 
    if (JD<2299160.5) {
        J0=floor(JD+0.5);
        dD=JD+0.5-J0;
    } else {
        N1=floor((JD-2342031.5)/36524.25/4)+1;// BC:1700-03-01 0:00
        N2=floor((JD-2378555.5)/36524.25/4)+1;// BC:1800-03-01 0:00
        N3=floor((JD-2415079.5)/36524.25/4)+1;// BC:1900-03-01 0:00
        J0=N1+N2+N3+JD+10;
        dD=J0+0.5-floor(J0+0.5);
        J0=floor(J0+0.5);
    }

    J0  =J0+32083;
    Y0  =ceil(J0/365.25)-1;
    Time_c.Year =Y0-4800;
    Time_c.Day  =J0-floor(Y0*365.25);
    Time_c.Month=floor((Time_c.Day-0.6)/30.6)+3;
    Time_c.Day -=round((Time_c.Month-3)*30.6);

    if (Time_c.Month>12) { Time_c.Month-=12; Time_c.Year+=1; }

    Time_c.Year  -=BC;
    Time_c.Second =round(dD*(3600.0*24));
    Time_c.Hour   =floor(Time_c.Second/3600.0);
    Time_c.Second-=Time_c.Hour*3600.0;
    Time_c.Minute =floor(Time_c.Second/60.0);
    Time_c.Second-=Time_c.Minute*60.0;

    return Time_c;
}
/// Convert time format from (cal) to (sec) /////
SecTime Cal2SecTime(CalTime Time)
{
    SecTime Time_c={0};
    double Hour,JD;

    if (Time.Month> 2) {
        Time.Year=Time.Year;   Time.Month=Time.Month;
    }
    if (Time.Month<=2) {
        Time.Year=Time.Year-1; Time.Month=Time.Month+12;
    }

    Hour =Time.Hour+(Time.Minute/60.0)+(Time.Second/3600.0);
    JD=(int)(365.25*Time.Year)+
        (int)(30.6001*(Time.Month+1))+
        (Time.Day)+(Hour/24.0)+1720981.5;

    JD-=2440587.5000000; // 1970-01-01-00:00:00

    Time_c.Fsecond =JD*3600.0*24;
    Time_c.Second  =(long)Time_c.Fsecond;
    Time_c.Fsecond-=Time_c.Second;

    return Time_c;
}

/// Common Depends Class
///
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
    // Not empty or empty all
    if      (Sign[0]==Sign[1]) {
        return;
    }
    // SecTime type is empty
    else if (Sign[0]==0&&Sign[1]==1) {
        sef_SecTime=Cal2SecTime(sef_CalTime);
        return;
    }
    // CalTime type is empty
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
