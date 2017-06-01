#pragma once

#include <ctime>
#include <iostream>




static class GlobalClock
{
public :
	GlobalClock()
	{

	}
	~GlobalClock()
	{

	}
	
	void Update()
	{
		currentTicks = std::clock();
		deltaTicks = static_cast<float>(currentTicks - previousTicks);
		previousTicks = currentTicks;

		deltaTime = deltaTicks / static_cast<float>CLOCKS_PER_SEC;
	}

	float deltaTime;
	float deltaTicks;
	float startUp;
	float sinceStartUp;

	std::clock_t currentTicks;
	std::clock_t previousTicks;
};


GlobalClock Time;
