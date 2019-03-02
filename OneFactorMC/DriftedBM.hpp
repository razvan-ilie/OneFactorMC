// DriftedBM
// Brownian motion with drift
// Derived class of SDE

// dS(t) = r dt + sig dW(t)

#ifndef DriftedBM_HPP
#define DriftedBM_HPP

#include "SDE.hpp"

class DriftedBM : public SDE
{
private:

	double r;		// risk-free rate   in risk-neutral pricing mu does not matter!!
	double vol;		// volatility

	//using q assumes dividend yield is not proportional to underlying value
	//which is a wild assumption...
	//but then again, this model is rarely used

	double q;		// div yield for equities
					// cost of carry for commodities
					// foreign intrest rate for FX

public:

	//constructors
	//each constructor calls SDEs constructor to initialize ic and exp
	DriftedBM(double rf, double sig, double cost, double init, double mat);
	DriftedBM(const DriftedBM& bm);

	//implemented as expected...
	double drift(double S, double t) override;
	double diffusion(double S, double t) override;
	double diffusionPrime(double S, double t) override;
};

#endif