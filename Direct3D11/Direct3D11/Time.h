#pragma once
#include <Windows.h>
#include <string>
#include <chrono>

using namespace std;

#define TIMEPOINT chrono::high_resolution_clock::time_point //okay but not nice for data types
#define NOW chrono::high_resolution_clock::now()
typedef chrono::high_resolution_clock::time_point time_point;
typedef chrono::duration<float> duration;

class Time
{
public:
	FLOAT Init();
	FLOAT Update();
	FLOAT DeInit();

	FLOAT GetDeltaTime() { return deltaTime; }
	UINT GetFPS() { return fps; }

private:
	time_point lastTimeStamp = {};

	FLOAT deltaTime = 0.0f;
	FLOAT totalTime = 0.0f;
	UINT fps = 0;
	FLOAT lastFps = 0;
	FLOAT fpsTime = 0.0f;
};

