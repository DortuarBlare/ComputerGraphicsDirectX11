#include "pch.h"
#include "Time.h"

time_point<steady_clock> Time::startTime = {};
time_point<steady_clock> Time::prevTime = {};
float Time::totalTime = 0;
float Time::deltaTime = 0;
unsigned int Time::frameCount = 0;