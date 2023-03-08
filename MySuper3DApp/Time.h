#pragma once

using namespace std::chrono;

class Time {
	friend class Game;

protected:
	static time_point<steady_clock> startTime;
	static time_point<steady_clock> prevTime;
	static float totalTime;
	static float deltaTime;
	static unsigned int frameCount;

	static void Update() {
		auto curTime = steady_clock::now();
		deltaTime = duration_cast<microseconds>(curTime - prevTime).count() / 1000000.0f;
		prevTime = curTime;
		totalTime += deltaTime;
		frameCount++;
	}

public:

	static float DeltaTime() { return deltaTime; }
};
