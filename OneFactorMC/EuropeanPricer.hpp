// EuropeanPricer
// Type of pricer that only needs the price of the underlying at maturity
// Derived class of Pricer

#ifndef EuropeanPricer_HPP
#define EuropeanPricer_HPP

#include "Pricer.hpp"

class EuropeanPricer : public Pricer 
{
public:

	// constructor that calls Pricer's constructor to add payoff and discount function
	EuropeanPricer(Payoff pOff, std::function<double(double)> disc);

	//implement the overridden virtual functions
	void processPath(std::vector<double>& path) override;
};

#endif