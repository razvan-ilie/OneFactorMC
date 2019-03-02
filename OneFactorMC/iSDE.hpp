// iSDE
// Abstract class that serves as an interface for SDEs
// Base class

// The properties of the underlyings define what the SDE is, so the specific SDEs
// will contain all the parameters (volatility, risk-free rate, strike, cost of carry/div yield, IC, maturity)

// It is assumed SDEs all have brownian motion as the source of randomness and are of the form:
// dS(t) = a(S, t) dt + b(S, t) dW(t)

#ifndef iSDE_HPP
#define iSDE_HPP

class iSDE
{
public:

	//virtual destructor
	virtual ~iSDE() {}

	// return a(S, t)
	virtual double drift(double S, double t) = 0;

	// return b(S, t)
	virtual double diffusion(double S, double t) = 0;

	// derivative of diffusion
	virtual double diffusionPrime(double S, double t) = 0;

	//getters
	//time to expiry
	virtual double expiry() = 0;
	//initial value
	virtual double initial() = 0;

	//setters
	virtual void expiry(double mat) = 0;
	virtual void initial(double init) = 0;
};

#endif