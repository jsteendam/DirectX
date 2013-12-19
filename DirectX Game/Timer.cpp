#include "Timer.h"

Timer::Timer() : isCounting(false)
{
}

void Timer::Start()
{
	begin = std::chrono::system_clock::now();
	isCounting = true;
}

void Timer::Stop()
{
	end = std::chrono::system_clock::now();
	isCounting = false;
}

void Timer::Restart()
{
	begin = std::chrono::system_clock::now();
	isCounting = true;
}

double Timer::GetTimePassed()
{
	if(isCounting) {
		SystemClock now = std::chrono::system_clock::now();
		return ((std::chrono::duration<double, std::milli>)(now - begin)).count();
	}
	else {
		return ((std::chrono::duration<double, std::milli>)(end - begin)).count();
	}
}
