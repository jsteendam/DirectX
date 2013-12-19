#pragma once

#include <chrono>

class Timer
{
public:
	Timer();
	void Start();
	void Stop();
	void Restart();
	double GetTimePassed();
private:
	typedef std::chrono::time_point<std::chrono::system_clock> SystemClock;
	
	SystemClock begin;
	SystemClock end;

	bool isCounting;
};