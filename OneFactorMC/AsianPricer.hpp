// AsianPricer
// Type of pricer that averages prices over a path
// Derived class of Pricer

#ifndef AsianPricer_HPP
#define AsianPricer_HPP

#include "Pricer.hpp"
#include <numeric>

class AsianPricer : public Pricer
{
public:

	// constructor that calls Pricer's constructor to add payoff and discount function
	AsianPricer(Payoff pOff, std::function<double(double)> disc);

	//implement the overridden virtual functions
	void processPath(std::vector<double>& path) override;
};

#endif