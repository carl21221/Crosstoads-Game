#pragma once

#include <string>

class Timer
{
public:
	Timer();
	Timer(int seconds, int minutes, int newHours);

	int GetSeconds();
	int GetMinutes();
	int GetHours();
	int GetTimeInSeconds();
	std::string GetTimeAsString();

	void Tick();
	void Reset();
	void Pause();
	void Stop();

protected:
	

private:
	int seconds = 0;
	int minutes = 0;
	int hours = 0;
	int frameCounter = 0;

	bool isPaused = false;

};

