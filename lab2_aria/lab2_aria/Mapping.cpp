#include "lib/Mapping.h"

/*
	The header and cpp file is new as I put cut the code out of the edge following class and into here.
	It allowed me to fix it and understand what is happping in this code. 
	Most of the new stuff is changing the variables used to fix the maths to properly get the object positions in global space.
	The other change was making two files instead of one. This allows it to easily copy and paste the x and y coords into spreadsheet software like excel.
*/

Mapping::Mapping()
{
}

void Mapping::ObjectCal(double RobotX, double RobotY, double RobotTh, double ObjectAngle, double Dist, double RobotR)
{
	float _thHeading = RobotTh;																//Set the robots current heading
	float _xRobot;
	float _yRobot;
	float _xObject;
	float _yObject;
	float _finalX;
	float _finalY;

	_xRobot = cos(ObjectAngle) * (Dist + RobotR);											//This finds the x and y position of the object 
	_yRobot = sin(ObjectAngle) * (Dist + RobotR);
	std::cout << std::endl;
	std::cout << "------------------------------------------------" << std::endl;
	std::cout << "Object Position Calculation" << std::endl;
	std::cout << "Robot X rotation calculation: " << _xRobot << std::endl;
	std::cout << "Robot Y rotation calculation: " << _yRobot << std::endl;

	_xObject = (cos(-_thHeading) * _xRobot) + (-sin(-_thHeading) * _yRobot);				//This then rotates the local positions to the global rotation of the world
	_yObject = (sin(-_thHeading) * _xRobot) + (cos(-_thHeading) * _yRobot);

	std::cout << "Object X rotation calculation: " << _xObject << std::endl;
	std::cout << "Object Y rotation calculation: " << _yObject << std::endl;

	_finalX = (_xObject + RobotX);															//This then translates from local to global position in the world
	_finalY = (_yObject + RobotY);

	std::cout << "Final X position calculation: " << _finalX << std::endl;
	std::cout << "Final Y position calculation: " << _finalY << std::endl;
	std::cout << "------------------------------------------------" << std::endl;
	std::cout << std::endl;

	m_XPos.emplace_back(_finalX);															//This places the information into the back of the vector
	m_YPos.emplace_back(_finalY);
}

void Mapping::WriteOutTheMap()
{
	std::ofstream outputFileX;																//Sets up a file stream 
	std::ofstream outputFileY;

	outputFileX.open("MappingXCoords.txt");													//Creates and opens up a file called MappingXCoords.txt

	for (int i = 0; i < m_XPos.size(); i++)													//This goes through the vector printing out each coordinate that was stored in the vector
	{
		outputFileX << m_XPos[i] << std::endl;
	}

	outputFileX.close();																	//Close the open file to open another and do the same with the Y coordinates.

	outputFileY.open("MappingYCoords.txt");

	for (int i = 0; i < m_YPos.size(); i++)
	{
		outputFileY << m_YPos[i] << std::endl;
	}

	outputFileY.close();
}