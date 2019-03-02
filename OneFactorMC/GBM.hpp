// GBM
// Geometric brownian motion SDE
// Derived class of SDE

// dS(t) = (r - q) S(t) dt + sig S(t) dW(t)

#ifndef GBM_HPP
#define GBM_HPP

#include "SDE.hpp"

class GBM : public SDE
{
private:

	double r;		// risk-free rate   in risk-neutral pricing mu does not matter!!
	double vol;		// volatility

	double q;		// div yield for equities
					// cost of carry for commodities
					// foreign intrest rate for FX

public:

	//constructors
	//each constructor calls SDEs constructor to initialize ic and exp
	GBM(double rf, double sig, double cost, double init, double mat);
	GBM(const GBM& gbm);

	//implemented as expected...
	double drift(double S, double t) override;
	double diffusion(double S, double t) override;
	double diffusionPrime(double S, double t) override;
};

#endif