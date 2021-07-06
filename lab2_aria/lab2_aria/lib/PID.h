#pragma once
#include <iostream>

class PID
{
public:
	PID();									//Default Constructor 

	void setProportional(double pGain);		//Sets the Proportional gain
	void setIntegral(double iGain);			//Sets the Integral gain
	void setDifferential(double dGain);		//Sets the Differential gain

	double PIDCalculation(double Error);	//This is the fuction that does the PID calculation and returns the result

private:

	double m_PGain;							//Stores the Proportional gain
	double m_IGain;							//Stores the Integral gain
	double m_DGain;							//Stores the Differential gain

	double m_ErrorT;						//This keeps track of the error total for the intergral calculation

	double m_LastError;						//This keeps track of the last error for the differential calculation

	double Proportional(double Error);		//This is a function for the proportional calculation
	double Intergral(double Error);			//This is a function for the integral calculation
	double Differential(double Error);		//This is a function for the differential calculation
};