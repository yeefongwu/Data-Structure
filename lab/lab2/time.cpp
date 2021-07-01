#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include<iomanip>
#include "time.h"


Time::Time(){
  hour=5;
  minute=30;
  second=59;
}

Time::Time(int mhour,int mminute,int msecond)
{
  hour=mhour;
  minute=mminute;
  second=msecond;
}

int Time::getHour() const
{
  return hour;
}

int Time::getMinute() const
{
  return minute;
}

int Time::getSecond() const
{
  return second;
}

void Time::PrintAMPM()
{

  if(hour>12)
  {
    hour-=12;
    std::cout<<std::setfill('0')<<std::setw(2)<<hour<<":";
    std::cout<<std::setw(2)<<std::setfill('0')<<minute<<":";
    std::cout<<std::setw(2)<<std::setfill('0')<<second<<":"<<"pm."<<std::endl;
  }
  else
  {
    std::cout<<std::setfill('0')<<std::setw(2)<<hour<<":";
    std::cout<<std::setw(2)<<std::setfill('0')<<minute<<":";
    std::cout<<std::setw(2)<<std::setfill('0')<<second<<":"<<"am."<<std::endl;
  }
}

void Time::setHour(int nhour)
{
  hour=nhour;
}

void Time::setMinute(int nminute)
{
  minute=nminute;
}

void Time::setSecond(int nsecond)
{
  second=nsecond;
}

bool IsEarlierThan(const Time& t1, const Time& t2)
{
  return (t1.getHour()*60*60+t1.getMinute()*60+t1.getSecond())< (t2.getHour()*60*60+t2.getMinute()*60+t2.getSecond());

}
