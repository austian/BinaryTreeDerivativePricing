#ifndef Option_h
#define Option_h
#include "Parameters.h"
#include <vector>


class Option	{
public:
	virtual double Payoff(Option& Option, double Spot) = 0;
};

class CallOption	:	public Option	{
public:
	double Payoff(Option& Option, double Spot);
	CallOption(double Strike);
private:
	double Strike;
};

class PutOption	:	public Option	{
public:
	double Payoff(Option& Option, double Spot);
	PutOption(double Strike);
private:
	double Strike;
};

class DnOCall	:	public Option	{
public:
	double Payoff(Option& Option, double Spot);
	DnOCall(double Strike, double Barrier);
	double Price(Parameters& Parameters, std::vector<double> Tree);
private:
	double Strike;
	double Barrier;
};

class AmPut	:	public Option	{
public:
	double Payoff(Option& Option, double Spot);
	AmPut(double Strike);
	double Price(Parameters& Parameters, std::vector<double> Tree);
private:
	double Strike;
};
#endif