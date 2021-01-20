#pragma once

#include <string>

class Timer
{
public:
	Timer();

	const const int GetSeconds() const;
	const int GetMinutes() const;
	const int GetHours() const;
	const int GetTimeInSeconds() const;
	const std::string GetTimeAsString() const;

	void Tick();
	void Reset();
	void Pause();
	void Stop();

private:
	int seconds = 0;
	int minutes = 0;
	int hours = 0;
	int frameCounter = 0;

	bool isPaused = false;

};

