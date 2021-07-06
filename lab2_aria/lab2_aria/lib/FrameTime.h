#pragma once
#include<Windows.h>

class FrameTime
{
public:
	FrameTime();				//Default Constructor
	void Update();				//A function to update the time
	float GetDeltaTime();		//A function to get and return the delta time
private:
	__int64 m_PrevFrame;		//
	__int64 m_CurrentFrame;
	__int64 m_Freq;
	float m_deltaTime;

};