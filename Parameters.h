#ifndef Parameters_h
#define Parameters_h

class Parameters	{
public:
	Parameters(double Expiry, double Rate, double Spot, double Vol, long NumberOfSteps, double Barrier);
	double Expiry;
	double Rate;
	double Spot;
	double Vol;
	long NumberOfSteps;
	double Increment;
	double Barrier;
};

#endif