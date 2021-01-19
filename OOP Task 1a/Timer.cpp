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

int Timer::GetSeconds() { return this->seconds; }

int Timer::GetMinutes() { return this->minutes; }

int Timer::GetHours() { return this->hours; }

int Timer::GetTimeInSeconds()
{
	int total = this->seconds;
	this->minutes += (hours * 60);
	total += (this->minutes * 60);
	return total;
}

std::string Timer::GetTimeAsString()
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
			std::cout << "Timer has increased to " << GetTimeAsString() << "\n";
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

