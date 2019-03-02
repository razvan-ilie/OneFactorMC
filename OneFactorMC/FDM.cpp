#include "FDM.hpp"

FDM::~FDM()
{
}

FDM::FDM(SDEPtr sdeptr, int steps) : sde(sdeptr), numSteps(steps), dt(sde->expiry() / numSteps)
{
}

SDEPtr FDM::StochasticEqn()
{
	return sde;
}

void FDM::StochasticEqn(SDEPtr sdeptr)
{
	sde = sdeptr;
}

int FDM::numberOfSteps()
{
	return numSteps;
}

double FDM::sizeOfSteps()
{
	return dt;
}
