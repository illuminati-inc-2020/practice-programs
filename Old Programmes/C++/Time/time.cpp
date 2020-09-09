#include <iostream>

using namespace std;

class Time
{
	int hour, minute, second;
public:
	Time(int, int, int);
	Time operator++();
	Time operator--();
	Time operator+(Time);
	Time operator-(Time);
	friend ostream& operator<<(ostream&, Time);
};
Time::Time(int hour=0, int minute=0, int second=0)
{
	if(hour>0 && minute>=0 && minute<60 && second>=0 && second<60)
	{
		Time::hour=hour;
		Time::minute=minute;
		Time::second=second;
	}
	else
		Time::hour=Time::minute=Time::second=0;
}
Time Time::operator++()
{
	Time::second++;
	if(Time::second==60)
	{
		Time::second=0;
		Time::minute++;
	}
	if(Time::minute==60)
	{
		Time::minute=0;
		Time::hour++;
	}
	return *this;
}
Time Time::operator--()
{
	Time::second--;
	if(Time::second==-1)
	{
		Time::second=59;
		Time::minute--;
	}
	if(Time::minute==-1)
	{
		Time::minute=59;
		if(Time::hour>0)
			Time::hour--;
	}
	return *this;
}
Time Time::operator+(Time t)
{
	Time t1;
	t1.second=(Time::second+t.second)%60;
	t1.minute=(Time::minute+t.minute+(Time::second+t.second)/60)%60;
	t1.hour=Time::hour+t.hour+(Time::minute+t.minute+(Time::second+t.second)/60)/60;
	return t1;
}
Time Time::operator-(Time t)
{
	Time t1;
	t1.second=(Time::second-t.second+60)%60;
	t1.minute=(Time::minute-t.minute+60+(Time::second-t.second-60)/60)%60;
	t1.hour=Time::hour-t.hour+(Time::minute-t.minute-60+(Time::second-t.second-60)/60)/60;
	return t1;
}
ostream& operator<<(ostream& os, Time t)
{
	os<<t.hour<<":"<<t.minute<<":"<<t.second;
}

main()
{
	Time t1(5,30,30);
	Time t2(3,50,40);
	Time t3;
	cout<<t1<<endl;
	cout<<t2<<endl;
	cout<<(t3=(t1-t2))<<endl;
	cout<<t3+t2<<endl;
}
