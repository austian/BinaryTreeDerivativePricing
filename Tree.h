#ifndef Tree_h
#define Tree_h

#include "Parameters.h"
#include <vector>
#include "Option.h"

class Tree	{
public:
	std::vector<double>* NodeGenerator(Parameters& Parameters);
	double Price(Parameters& Parameters, std::vector<double> Node, Option& Option);	
};

#endif