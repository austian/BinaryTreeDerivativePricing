#include <iostream>
#include "Parameters.h"
#include "Option.h"
#include "Tree.h"
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

double Expiry;
double Rate;
double Strike;
double Spot;
double Vol;
long NumberOfSteps;
double Barrier;

int main()	{

	cout << "Input time to expiry:\n";
	cin >> Expiry;

	cout << "Input interest rate\n";
	cin >> Rate;

	cout << "Input strike\n";
	cin >> Strike;

	cout << "Input spot\n";
	cin >> Spot;
	
	cout << "Input barrier\n";
	cin >> Barrier;

	cout << "Input volatility\n";
	cin >> Vol;

	cout << "Input number of steps\n";
	cin >> NumberOfSteps;

	Parameters CurrentParameters(Expiry, Rate, Spot, Vol, NumberOfSteps, Barrier);
	Tree RNTree;

	CallOption Call(Strike);
	PutOption Put(Strike);
	DnOCall DnOCall(Strike, Barrier);
	AmPut AmPut(Strike);
	
	vector<double>* RNTreePointer = RNTree.NodeGenerator(CurrentParameters);
	vector<double> RNTreeVector = *RNTreePointer;

	//ofstream out("CallvsSteps.txt");
	//double CallPrice;
	//for(int i = 2; i < 12; i++)	{
	//	CurrentParameters.NumberOfSteps = pow(2.0,i);
	//	vector<double>* RNTreePointer = RNTree.NodeGenerator(CurrentParameters);
	//	vector<double> RNTreeVector = *RNTreePointer;
	//	CallPrice = RNTree.Price(CurrentParameters, RNTreeVector, Call);
	//	out << i << "	" << CallPrice << endl;
	//}

	double CallPrice = RNTree.Price(CurrentParameters, RNTreeVector, Call);
	cout << "Call = " << CallPrice << endl;

	double PutPrice = RNTree.Price(CurrentParameters, RNTreeVector, Put);
	cout << "Put = " << PutPrice << endl;

	double DnOCallPrice = DnOCall.Price(CurrentParameters, RNTreeVector);
	cout << "Down and out call = " << DnOCallPrice << endl;

	double AmPutPrice = AmPut.Price(CurrentParameters, RNTreeVector);
	cout << "American Put = " << AmPutPrice << endl;

}