#include "Euler.hpp"

Euler::Euler(SDEPtr sdeptr, int steps) : FDM(sdeptr, steps)
{
}

double Euler::advance(double SBefore, double tBefore, double dWt)
{
	double drift = sde->drift(SBefore, tBefore);
	double vol = sde->diffusion(SBefore, tBefore);

	return SBefore + drift*dt + vol*dWt;
}

FDMPtr Euler::copy() const
{
	return FDMPtr(new Euler(*this));
}
