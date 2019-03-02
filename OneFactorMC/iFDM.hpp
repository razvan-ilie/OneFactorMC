// iFDM
// Abstract class that serves as an interface for the finite difference methods
// Base class

// A derived class object of iFDM has an SDE object

#ifndef iFDM_HPP
#define iFDM_HPP

#include "iSDE.hpp"
#include <memory>

using SDEPtr = std::shared_ptr<iSDE>;

class iFDM 
{
public:
	using FDMPtr = std::shared_ptr<iFDM>;

	virtual ~iFDM() {}

	// getter for SDE
	virtual SDEPtr StochasticEqn() = 0;
	// setter
	virtual void StochasticEqn(SDEPtr sde) = 0;

	// will return number of steps in the FDM
	virtual int numberOfSteps() = 0;
	// return size of a step
	virtual double sizeOfSteps() = 0;

	// advance FDM by one timestep
	// we will get the brownian motion increment from RNG
	virtual double advance(double SBefore, double tBefore, double dWt) = 0;

	// copy the fdm object and get a pointer to the new object
	virtual FDMPtr copy() const = 0;
};

#endif