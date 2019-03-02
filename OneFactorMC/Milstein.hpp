// Milstein
// Milstein's Method for FDM
// Derived class of iFDM

#ifndef Milstein_HPP
#define Milstein_HPP

#include "FDM.hpp"

using FDMPtr = std::shared_ptr<iFDM>;

class Milstein : public FDM
{
public:

	// constructor
	// calls FDM constructor
	Milstein(SDEPtr sdeptr, int steps);

	// advance one time step given data
	double advance(double SBefore, double tBefore, double dWt) override;

	//override copy method
	FDMPtr copy() const override;

};

#endif