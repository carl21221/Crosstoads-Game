#include "Timer.h"
#include <iostream>
#include <stdio.h>

Timer::Timer()
{
	this->seconds = 0;
	this->minutes = 0;
	this->hours = 0;
	this->isPaused = false;
}

const int Timer::GetSeconds() const { return this->seconds; }

const int Timer::GetMinutes() const { return this->minutes; }

const int Timer::GetHours() const { return this->hours; }

const int Timer::GetTimeInSeconds() const
{
	return this->seconds + ((this->minutes + (this->hours * 60)) * 60);
}

const std::string Timer::GetTimeAsString() const
{
	return std::to_string(GetSeconds()) + " : " + std::to_string(GetMinutes());
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
			//std::cout << "Debug: Timer has increased to " << GetTimeAsString() << "\n";
			this->seconds++;
			this->frameCounter = 0;
		}

		if (this->seconds >= 60)
		{
			seconds -= 60;
			minutes += 1;
		}
		if (this->minutes >= 60)
		{
			minutes -= 60;
			hours += 1;
		}
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

