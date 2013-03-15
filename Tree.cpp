#include "Parameters.h"
#include "Tree.h"
#include <vector>
#include <cmath>
#include "Option.h"

using namespace std;

vector<double>* Tree::NodeGenerator(Parameters& Parameters)	{
	vector<double>* RNTreePointer = new vector<double>;
	vector<double>& RNTree = *RNTreePointer;
	RNTree.push_back(0.0);
	RNTree.push_back(log(Parameters.Spot));
	double CurrentNode;
	double LastNode;
	long Sum;
	for(int i = 2; i < Parameters.NumberOfSteps + 1; i++)	{
		Sum = 0.5*(i-2)*(i-1);
		LastNode = RNTree[Sum+1];
		CurrentNode = LastNode + (Parameters.Rate - 0.5*Parameters.Vol*Parameters.Vol)*Parameters.Increment + Parameters.Vol*sqrt(Parameters.Increment);
		RNTree.push_back(CurrentNode);
		 for(int j = 1; j < i; j++)	{
			LastNode = RNTree[Sum + j];
			CurrentNode = RNTree[Sum + j] + (Parameters.Rate - 0.5*Parameters.Vol*Parameters.Vol)*Parameters.Increment - Parameters.Vol*sqrt(Parameters.Increment);  
			RNTree.push_back(CurrentNode);
			}
		}
	for(int k = 0; k < RNTree.size(); k++)
		RNTree[k] = exp(RNTree[k]);
	return RNTreePointer;
}

double Tree::Price(Parameters& Parameters, vector<double> Node, Option& Option)	{
	long OldSum;
	long NewSum;
	for(int i = 1; i < Node.size(); i++)	{
		Node[i] = (Option.Payoff(Option, Node[i])); 
	}
	for(int i = Parameters.NumberOfSteps-1; i > 0; i--)	{
		OldSum = 0.5*(i-1)*i;
		NewSum = 0.5*i*(1+i);
		for(int j = 1; j <= i; j++)	{
		Node[OldSum+j] = exp(-1*Parameters.Rate*Parameters.Increment)*0.5*(Node[NewSum + j] + Node[NewSum + j + 1]);
		}
	}
	return Node[1];
}
		


