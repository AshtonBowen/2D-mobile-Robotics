#include "lib/PID.h"
#include <string>
#include <time.h>

/*
	Not much was changed here but having it's own class to cut down on complexity and duplication
*/

PID::PID()
{
}

void PID::setProportional(double pGain)
{
	m_PGain = pGain;
}

void PID::setIntegral(double iGain)
{
	m_IGain = iGain;
}

void PID::setDifferential(double dGain)
{
	m_DGain = dGain;
}

double PID::PIDCalculation(double Error)
{
	double pTerm_, dTerm_, iTerm_;

	pTerm_ = Proportional(Error);														//Calculate the proportional 
	iTerm_ = Intergral(Error);															//Calculate the intergral 
	dTerm_ = Differential(Error);														//Calculate the differential


	if (Error > 500)
	{
		iTerm_ = 0;
	}
	
	std::cout << "pTerm: " + std::to_string(pTerm_) + "|| iTerm: " + std::to_string(iTerm_) + "|| dTerm: " + std::to_string(dTerm_) << std::endl;

	return pTerm_ + iTerm_ + dTerm_;
}

double PID::Proportional(double Error)
{
	double pTerm_;

	pTerm_ = m_PGain * Error;														//Times the error by the gain

	return pTerm_;
}

double PID::Intergral(double Error)
{
	double iTerm_;

	if (Error < 50 && Error > 0.05 || Error > -50 && Error < -0.05)			//Check to see how close it is to the error so the iterm doesn't build up to much and make sure it stops
	{
		m_ErrorT += Error;															//Add the error to the total error increasing it
	}
	else if (Error <= 0.05 || Error >= -0.05)
	{
		m_ErrorT = 0;																//Sets it to zero
	}

	iTerm_ = m_IGain * m_ErrorT;													//Times the total by the i gain

	return iTerm_;
}

double PID::Differential(double Error)
{
	double dTerm_;
	std::cout << " || Last error is:" << m_LastError << " || dGain is: " << m_DGain << std::endl;
	dTerm_ = m_DGain * (Error - m_LastError);									//Takes the error away from the last error then times it by the gain
	m_LastError = Error;															//Sets the new error to the last error
	return dTerm_;
}
