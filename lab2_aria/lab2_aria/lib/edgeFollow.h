#include <ArAction.h>
#include "PID.h"
#include "Mapping.h"
#include "FrameTime.h"

class edgeFollow : public ArAction
{
public:
	edgeFollow();										//A default constructor
	virtual ~edgeFollow() {};							//A defualt deconstuctor
	virtual ArActionDesired * fire(ArActionDesired d);	//A fire function for the action 
	ArActionDesired desiredState;						//A state to be returned for the robot for decisions to determine which action should be executed

protected:
	int speed;											//Speed of the robot in mm/s

	double deltaHeading;								//Change in heading

	double m_distLeftSensor;							//A variable to store the value from the sensors
	double m_distRightSensor;
	double m_angle;										//A output from the sensors that stores the angle at which the closest point from to the robot to the object

	//Time till write
	float m_targetTime;									//A variable that holds the target time 

	//Time Keeping
	FrameTime Time;										//A Object for accessing the timer

	//Mapping
	Mapping map;										//A object for storing and creating the map

	//PID
	PID LeftCal;										//Objects for left and right PID control system 
	PID RightCal;
};