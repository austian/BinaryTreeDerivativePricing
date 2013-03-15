#include "Option.h"
#include "Parameters.h"
#include <minmax.h>
#include <vector>
#include <iostream>

using namespace std;

//Call Option
CallOption::CallOption(double Strike)	:	Strike(Strike)	{}

double CallOption::Payoff(Option& Option, double Spot)	{
	 return max(Spot - Strike, 0.0);
}

//Put Option
PutOption::PutOption(double Strike)	:	Strike(Strike)	{}

double PutOption::Payoff(Option& Option, double Spot)	{
	 return max(Strike - Spot, 0.0);
}

//Down and Out Call
double DnOCall::Payoff(Option& Option, double Spot)	{
	 return max(Strike - Spot, 0.0);
}

DnOCall::DnOCall(double Strike, double Barrier)	:	Strike(Strike), Barrier(Barrier)	{}

double DnOCall::Price(Parameters& Parameters, vector<double> Tree)	{
	double OldSum;
	double NewSum;
	OldSum = 0.5*(Parameters.NumberOfSteps)*(Parameters.NumberOfSteps-1);
	for(int i = 1; i <=Parameters.NumberOfSteps; i++)	{
		if(Tree[OldSum+i] > Parameters.Barrier)
				Tree[OldSum+i] = max(Tree[OldSum+i] - Strike, 0.0);	
			else		
				Tree[OldSum+i] = 0;	
	}
	for(int i = Parameters.NumberOfSteps-1; i > 0; i--)	{
		OldSum = 0.5*(i-1)*i;
		NewSum = 0.5*i*(1+i);
		for(int j = 1; j <= i; j++)	{
			if(Tree[OldSum+j] > Parameters.Barrier)
				Tree[OldSum+j] = exp(-1*Parameters.Rate*Parameters.Increment)*0.5*(Tree[NewSum + j] + Tree[NewSum + j + 1]);
			else
				Tree[OldSum+j] = 0;
		}
	}
	return Tree[1];
}

//American Put
double AmPut::Payoff(Option& Option, double Spot)	{
	 return max(Strike - Spot, 0.0);
}
AmPut::AmPut(double Strike)	:	Strike(Strike)	{}

double AmPut::Price(Parameters& Parameters, vector<double> Tree)	{
	double OldSum;
	double NewSum;
	double EUOpt;
	double Intrinsic;
	OldSum = 0.5*(Parameters.NumberOfSteps)*(Parameters.NumberOfSteps-1);
	for(int i = 1; i <=Parameters.NumberOfSteps; i++)	
				Tree[OldSum+i] = max(Strike - Tree[OldSum+i], 0.0);	
	for(int i = Parameters.NumberOfSteps-1; i > 0; i--)	{
		OldSum = 0.5*(i-1)*i;
		NewSum = 0.5*i*(1+i);
		for(int j = 1; j <= i; j++)	{
			EUOpt = exp(-1*Parameters.Rate*Parameters.Increment)*0.5*(Tree[NewSum + j] + Tree[NewSum + j + 1]);
			Intrinsic = max(Strike - Tree[OldSum+j], 0.0);
			Tree[OldSum+j] = max(EUOpt, Intrinsic);			
		}
	}
	return Tree[1];
}