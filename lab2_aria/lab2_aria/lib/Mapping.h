#pragma once
#include <vector>
#include <iostream>
#include <fstream>

class Mapping
{
public:
	Mapping();																											//Defualt Constructor

	void ObjectCal(double RobotX, double RobotY, double RobotTh, double ObjectAngle, double Dist, double RobotR);		//A function used to calculate the object position to world position
	void WriteOutTheMap();																								//This writes out a map of the data collected

private:
	std::vector<double> m_XPos;																							//A vector to store the x coordinates 
	std::vector<double> m_YPos;																							//A vector to store the y coordinates
};