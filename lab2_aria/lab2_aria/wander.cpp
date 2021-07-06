#include <iostream>
#include <stdlib.h>
#include <Aria.h>
#include "lib/wander.h"

/*
	Most of the new stuff was just shuffling the algorithim around as the problems were that it wasn't backing out of the function after altering some of the conditions to make the next check valid or true when it shouldn't.
	The biggest change with adding a timer to the action as it allowed for a lot of redundant code to be cut, as there was a lot of checks for conditions as I was using a different method for checking when to turn and go forward.
*/

wander::wander() : ArAction("Wander About")
{
	srand(time(NULL));																	//This is used to randomise the seed for the random number generator																
	m_speed = 100;																		//Sets the speed for the robot
	m_targetTime = 10;																	//Set the target time
}

ArActionDesired * wander::fire(ArActionDesired d)
{
	desiredState.reset();																//Reset the state

	if (m_targetTime > 0 && m_isChangingDirection == false)								//This is a statement used to check if the robot should be going forward
	{

		m_Time.Update();																//Update the timer
		m_deltaTime = m_Time.GetDeltaTime();											//Get the delta time
		m_targetTime = m_targetTime - m_deltaTime;										//Take away the delta from the target time to get a countdown

		system("cls");																	//Clear the control panel
		GoForward();																	//Use the go forward function
		std::cout << std::endl;															//A output for the command console to show what the Action is doing and what action is being taken
		std::cout << "------------------------------------------------" << std::endl;
		std::cout << "Robot Action : Wandering" << std::endl;
		std::cout << "Robot X position: " << myRobot->getX() << std::endl;
		std::cout << "Robot Y position: " << myRobot->getY() << std::endl;
	}
	else
	{
		m_decision = rand() % 100 + 1;													//A random number generation to create a random decision

		if (m_isChangingDirection == true && m_targetTime < 0)							//A check of if the robot is done turning
		{
			m_isChangingDirection = false;												//Reset the timer and boolean statement
			m_targetTime = rand() % 20 + 5;

			return &desiredState;														//Return the state so it doesn't continue. This is a new addition as it was causing algorithim problems as the function was still executing while the conditions had been reset.
		}

		if (m_isChangingDirection == false)
		{
			std::cout << "Robot Action : Turning" << std::endl;
			if (m_decision <= 50)														//A if statement that checks what the decision is
			{
				m_isGoingLeftOrRight = false;											//Set the boolean for going left
				TurnLeft();																//Make the robot turn left

				m_targetTime = rand() % 10 + 4;											//Reset the timer

				std::cout << "Turning left" << std::endl;
			}
			else
			{
				m_isGoingLeftOrRight = true;											//Set the timer 
				TurnRight();															//Make the robot turn right

				m_targetTime = rand() % 10 + 4;											//Reset the timer

				std::cout << "Turning right" << std::endl;
			}
			m_isChangingDirection = true;												//Set the boolean to say that the robot should be turning
		}

		if (m_targetTime > 0 && m_isChangingDirection == true)							//An if statement saying if the robot should be turning
		{
			m_Time.Update();															//Update the time 
			m_deltaTime = m_Time.GetDeltaTime();										//Get the delta time
			m_targetTime = m_targetTime - m_deltaTime;									//Tick the clock down

			if (m_isGoingLeftOrRight == false)											//Check if the robot is turning left
			{
				desiredState.setDeltaHeading(m_heading);								//Turn left by the m_heading speed
			}
			else
			{
				desiredState.setDeltaHeading(m_heading);								//Turn right
			}
		}

	}
	
	return &desiredState;																//Return the state
}

void wander::GoForward()
{
	desiredState.setVel(m_speed);														//Go forward based on the m_speed 
}

void wander::TurnLeft()
{
	m_heading = rand() % (-2) + (-10);													//A random generator for the speed going left

	desiredState.setDeltaHeading(m_heading);											//Turn left
}

void wander::TurnRight()
{
	m_heading = rand() % 10 + 2;														//A random generator for the speed going right

	desiredState.setDeltaHeading(m_heading);											//Turn right
}