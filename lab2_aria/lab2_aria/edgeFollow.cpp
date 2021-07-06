#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <Aria.h>
#include <math.h>

#include "lib/edgeFollow.h"

/*
	The biggest changes with this is that the mapping and PID functions were moved to there own classes which cleaned up things.
	My idead of having the robot be able to try and go through tight spaces was cut for simplicty and to clean up the code to remove possible errors.
	Another new addition to the code was the timer which made printing out the map much easier as it will just keep updating the map everytime it comes around and makes it consistent without issues.
*/

edgeFollow::edgeFollow() : ArAction("Edge Following")
{
	speed = 100;						//Set the robots speed to 50 mm/s. 200 is top speed
	deltaHeading = 0;					//Straight line
	m_targetTime = 100;					//Sets the target time
	
	// PID control set up
	RightCal.setProportional(0.4);
	RightCal.setIntegral(0.002);
	RightCal.setDifferential(2.2);

	LeftCal.setProportional(-0.4);
	LeftCal.setIntegral(-0.002);
	LeftCal.setDifferential(-2.2);

}

ArActionDesired* edgeFollow::fire(ArActionDesired d)
{
	
	m_distLeftSensor = myRobot->checkRangeDevicesCurrentPolar(10, 150, &m_angle) - myRobot->getRobotRadius();			//Check the sensors and see how close objects are
	m_distRightSensor = myRobot->checkRangeDevicesCurrentPolar(-150, -10, &m_angle) - myRobot->getRobotRadius();

	if (m_distLeftSensor < 1450 || m_distRightSensor < 1450)															//Check if the object is close enough to the robot to edge follow 			
	{
		system("cls");																									//Clear the console
		desiredState.reset();																							//Reset the desired state
		std::cout << std::endl;																							//Print out what action is being used
		std::cout << "------------------------------------------------" << std::endl;
		std::cout << "Robot Action: Edge Following" << std::endl;
		std::cout << "Robot Heading: " << myRobot->getTh() << std::endl;
		std::cout << "Time remaining: " << m_targetTime << std::endl;

		Time.Update();																									//Update the timer
		m_targetTime = m_targetTime - Time.GetDeltaTime();																//Tick down the timer


		if (m_distLeftSensor < m_distRightSensor)																		//Check if the object is on the left or right of the robot
		{
			
			myRobot->checkRangeDevicesCurrentPolar(10, 150, &m_angle) - myRobot->getRobotRadius();						//Reset the angle of the closest object to the robot
			map.ObjectCal(myRobot->getX(), myRobot->getY(), myRobot->getTh(), m_angle, m_distLeftSensor, myRobot->getRobotRadius());	//Input the infomation for mapping the enviroment
			deltaHeading = LeftCal.PIDCalculation(1000 - m_distLeftSensor);												//Use the PID calculation to get the new heading so it can follow the edge of the object
			desiredState.setDeltaHeading(deltaHeading);																	//Set the heading
			desiredState.setVel(speed);																					//Set the speed of the robot
		}
		else
		{
			myRobot->checkRangeDevicesCurrentPolar(-150, -10, &m_angle) - myRobot->getRobotRadius();					//Same as above but different side of the robot
			map.ObjectCal(myRobot->getX(), myRobot->getY(), myRobot->getTh(), m_angle, m_distRightSensor, myRobot->getRobotRadius());
			deltaHeading = RightCal.PIDCalculation(1000 - m_distRightSensor);
			desiredState.setDeltaHeading(deltaHeading);
			desiredState.setVel(speed);
		}
	
		if(m_targetTime < 0)																							//A check to see if its time to write out the map
		{
			map.WriteOutTheMap();																						//Write out the map
			m_targetTime = 100;																							//Reset the timer
		}

		return &desiredState;																							//Return the desired stare for the robot
	}

	return &desiredState;
}