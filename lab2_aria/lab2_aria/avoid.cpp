#include <iostream>
#include <stdlib.h>
#include <Aria.h>

#include "avoid.h"

avoid::avoid() : ArAction("Avoid")
{
	m_speed = 0;
}

ArActionDesired * avoid::fire(ArActionDesired d)
{
	if (isObjectToClose())											//Check if it's too close to an object
	{
		m_speed = desiredState.getVel();							//Get its current speed value
		desiredState.reset();										//Reset it's speed
		if (m_speed > 0) m_speed--;									//Check if speed is 0
		desiredState.setDeltaHeading(-10);							//Set the delta heading so it turns
		return &desiredState;
	}
	return &desiredState;
}

bool avoid::isObjectToClose()
{
	double dist;
	double angle = myRobot->getTh();
	
	dist = (myRobot->checkRangeDevicesCumulativePolar(90, -90, &angle) - myRobot->getRobotRadius());		//Check the distance
	std::cout << "This is the distance of the closest object " << dist << std::endl;
	
	if (dist <= 50)																							//Compare it with how close it can get to a objects surface.
	{
		return true;
	}

	return false;
}

