// FDM
// Abstract class that serves as a base class for FDMs
// Holds number of subdivisions, their size and the points for each subdivision
// Base class, derived class of iFDM

#ifndef FDM_HPP
#define FDM_HPP

#include "iSDE.hpp"
#include "iFDM.hpp"
#include <vector>

class FDM : public iFDM 
{
protected:
	// each FDM has an SDE they aim to approximate
	SDEPtr sde;
	//constructor will be used by derived classes
	FDM(SDEPtr sdeptr, int steps);

public:
	// public members we might need to access
	
	int numSteps;				// number of subdivisions
	//std::vector<double> t;		// array of each step
	double dt;					// size of a step

	virtual ~FDM();

	// getter + setter
	SDEPtr StochasticEqn() override;
	void StochasticEqn(SDEPtr sdeptr) override;

	// get number of steps
	int numberOfSteps() override;
	// get size of steps
	double sizeOfSteps() override;

	//implemented in each specific FDM
	virtual double advance(double SBefore, double tBefore, double dWt) override = 0;

	// override copy method
	virtual FDMPtr copy() const override = 0;
};

#endif