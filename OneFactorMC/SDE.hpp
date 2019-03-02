// SDE
// Abstract class that serves as a base class for SDEs
// Holds expiry and initial value of underlying, which all SDEs have
// Base class, derived class of iSDE

#ifndef SDE_HPP
#define SDE_HPP

#include "iSDE.hpp"

class SDE : public iSDE 
{
protected:

	// protected constructor which gets called by derived classes in their constructors
	// to initialize the private member data in SDE 
	// should not be able to initialize SDE on its own
	SDE(double init, double mat);

	// properties common to all SDEs
	// we can set them private as we have getters
	double ic;		// initial condition
	double exp;		// expiry

public:

	//virtual destructor
	virtual ~SDE();

	virtual double drift(double S, double t) override = 0;
	virtual double diffusion(double S, double t) override = 0;
	virtual double diffusionPrime(double S, double t) override = 0;

	//getters
	//time to expiry
	virtual double expiry() override;
	//initial value
	virtual double initial() override;

	//setters
	virtual void expiry(double mat) override;
	virtual void initial(double init) override;
};

#endif