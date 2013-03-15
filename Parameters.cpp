#include "Parameters.h"

Parameters::Parameters(double Expiry, double Rate, double Spot, double Vol, long NumberOfSteps, double Barrier)	:	
Expiry(Expiry), Rate(Rate), Spot(Spot), Vol(Vol), NumberOfSteps(NumberOfSteps), Barrier(Barrier) 	{
	Increment = Expiry / NumberOfSteps;
}