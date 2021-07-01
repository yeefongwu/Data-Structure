//file: time.h
//Purpose:  Declaration of the Time class

class Time
{
public:
  Time();
  Time(int mhour,int mminute,int msecond);
  //accessors
  int getHour() const;
  int getMinute() const;
  int getSecond() const;
  void PrintAMPM();
  void setHour(int nhour);
  void setMinute(int nminute);
  void setSecond(int nsecond);

private:
  int hour;
  int minute;
  int second;
};

bool IsEarlierThan(const Time& t1, const Time& t2);
