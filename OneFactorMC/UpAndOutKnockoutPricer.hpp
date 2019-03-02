// UpAndOutKnockoutPricer
// Type of pricer that knocks out above a certain level
// Derived class of Pricer

#ifndef UpAndOutKnockoutPricer_HPP
#define UpAndOutKnockoutPricer_HPP

#include "Pricer.hpp"
#include <algorithm>

class UpAndOutKnockoutPricer : public Pricer
{
private:
	// knockout level
	double barrier;

public:

	// constructor that calls Pricer's constructor to add payoff and discount function
	// also adds barrier level
	UpAndOutKnockoutPricer(Payoff pOff, std::function<double(double)> disc, double level);

	//implement the overridden virtual functions
	void processPath(std::vector<double>& path) override;
};

#endif