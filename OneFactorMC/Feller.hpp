// Feller
// Feller mean reverting process
// Derived class of SDE

// usually used in two-factor models...
// dS(t) = kappa * ( theta - S(t) ) dt + sig S(t) dW(t)

#ifndef Feller_HPP
#define Feller_HPP

#include "SDE.hpp"

class Feller : public SDE
{
private:

	double kappa;	// mean reversion rate
	double theta;	// mean reversion level
	double vol;		// volatility

	double ic;		// initial value
	double exp;		// expiry

public:

	//constructor
	//each constructor calls SDEs constructor to initialize ic and exp
	Feller(double k, double th, double sig, double init, double mat);
	Feller(const Feller& f);

	//implemented as expected...
	double drift(double S, double t) override;
	double diffusion(double S, double t) override;
	double diffusionPrime(double S, double t) override;
};

#endif