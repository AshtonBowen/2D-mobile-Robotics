#include "FrameTime.h"

/*
	This is the only way I had found to create a timer in c++ without using third party libraries like SFML.
	I found a few youtube tutorials on the how do make this. Below is the URL to the video I used to make this. 
*/

// https://www.youtube.com/watch?v=Ks4oTdJMXWo

FrameTime::FrameTime()
{
	m_PrevFrame = 0;
	m_CurrentFrame = 0;
	m_Freq = 0;
	m_deltaTime = 0;
}

void FrameTime::Update()
{
	m_deltaTime = 0;
	QueryPerformanceFrequency((LARGE_INTEGER*)& m_Freq);		//This query's the computer to get the frequency which is how many computer ticks in a second.
	QueryPerformanceCounter((LARGE_INTEGER*)& m_CurrentFrame);	//This query's the computers timer.  
	int deltaTicks = ((float)m_CurrentFrame - m_PrevFrame);		//This takes the previous frame from the current fram to get the amount of ticks that has passed in the time
	m_deltaTime = ((float)deltaTicks / (float)m_Freq);			//This then divides ticks and frequency to get the amount of time that has passed.
	m_PrevFrame = m_CurrentFrame;								//This then sets the new previous frame
}

float FrameTime::GetDeltaTime()
{
	float dt = m_deltaTime;										
	if (dt <= 0.0f || dt > 1.0f)								//This is used to standardise the delta time, just incase it is too large or too small from another action being taken place or the program executing too quickly.
	{
		dt = 0.025f;
	}

	return dt;													//Returns the delta time
}


