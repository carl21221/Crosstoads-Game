#include "Timer.h"

Timer::Timer()
{
	this->seconds = 0;
	this->minutes = 0;
	this->hours = 0;
}

Timer::Timer(int newSeconds, int newMinutes, int newHours) 
	: seconds(newSeconds), minutes(newMinutes), hours(newHours)
{}

int Timer::GetSeconds() { return this->seconds; }

int Timer::GetMinutes() { return this->minutes; }

int Timer::GetHours() { return this->hours; }

std::string Timer::GetTimeAsString()
{
	//Correctly format the values. ('1' should be '01' etc)
	std::string secondsString = "";
	std::string minutesString = "";
	std::string hoursString = "";

	if (seconds < 10) secondsString = "0" + seconds;
	else secondsString = "" + seconds;

	if (minutes < 10) minutesString = "0" + minutes;
	else minutesString = "" + seconds;

	if (hours < 10) hoursString = "0" + hours;
	else hoursString = "" + seconds;

	return secondsString + ":" + minutesString + ":" + hoursString;
}

/// <summary>
/// Should be called every frame to roughly calculate the time elapsed.
/// </summary>
void Timer::Tick()
{
	if (!this->isPaused)
	{
		this->frameCounter++;
		if (frameCounter >= 60) 
		{ 
			this->seconds++;
			this->frameCounter - 60;
		}
		this->FormatTimeRollover();
	}
}

void Timer::Reset()
{
	this->seconds = 0;
	this->minutes = 0;
	this->hours = 0;
	this->frameCounter = 0;
}

void Timer::Pause() { this->isPaused = true; }

void Timer::Stop()
{
	this->Reset();
	this->Pause();
}

void Timer::FormatTimeRollover()
{
	if (this->seconds >= 60)
	{
		seconds - 60;
		minutes++;
	}
	if (this->minutes >= 60)
	{
		minutes - 60;
		hours++;
	}
}

