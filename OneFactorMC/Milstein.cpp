#include "Milstein.hpp"

Milstein::Milstein(SDEPtr sdeptr, int steps) : FDM(sdeptr, steps)
{
}

double Milstein::advance(double SBefore, double tBefore, double dWt)
{
	double drift = sde->drift(SBefore, tBefore);
	double vol = sde->diffusion(SBefore, tBefore);
	double volPrime = sde->diffusionPrime(SBefore, tBefore);

	return SBefore + drift*dt + vol*dWt + 0.5*vol*volPrime*((dWt*dWt) - dt);
}

FDMPtr Milstein::copy() const
{
	return FDMPtr(new Milstein(*this));
}
