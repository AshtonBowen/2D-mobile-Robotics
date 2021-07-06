#include <time.h>
#include "FrameTime.h"
class wander : public ArAction
{
public:
	wander();											//Default Constructor
	virtual ~wander() {}								//Default Deconstructor
	virtual ArActionDesired * fire(ArActionDesired d);	//Fire function for the class
	ArActionDesired desiredState;						//The state to be returned so it can be determined what action is to be used

protected:
	
	FrameTime m_Time;									//Object that is used to get a delta time for a timer

	float m_deltaTime;									//This records the delta time that is returned to be used
	float m_targetTime;									//This is the timer that will tick down for something to happen
	float m_heading;									//This stores the turning speed that is randomly set
	float m_speed;										//This stores the speed for the robot in this action

	bool m_isChangingDirection = false;					//A boolean that is used in decision making process to say if it's going forward or turning
	bool m_isGoingLeftOrRight = false;					//A boolean that is used to keep a decision that had been made

	int m_decision;										//A interger that is used to make a choice

	void GoForward();									//A function that is used to make the robot go forward
	void TurnLeft();									//A function that is used to make the robot to turn left
	void TurnRight();									//A function that is used to make the robot to turn right

};