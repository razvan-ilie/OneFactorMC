// Euler
// Euler's Method for FDM
// Derived class of iFDM

#ifndef Euler_HPP
#define Euler_HPP

#include "FDM.hpp"

using FDMPtr = std::shared_ptr<iFDM>;

class Euler : public FDM 
{
public:

	// constructor
	// calls FDM constructor
	Euler(SDEPtr sdeptr, int steps);

	// advance one time step given data
	double advance(double SBefore, double tBefore, double dWt) override;

	// override copy method
	FDMPtr copy() const override;

};

#endif