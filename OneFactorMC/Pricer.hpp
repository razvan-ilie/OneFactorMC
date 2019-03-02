// Pricer
// Base class for different pricing methods that defines the basic methods common to all pricers
// Base class

#ifndef Pricer_HPP
#define Pricer_HPP

#include "Payoff.hpp"
#include <functional>
#include <iostream>
#include <vector>

class Payoff;

class Pricer 
{
protected:
	// function that discounts the price

	// **************
	// usually the discount function should be defined directly by the SDE that is used
	// however, for the scope of this project, we can assume that it can be different
	std::function<double(double)> discountFunc;

	double price;		// price after computation
	double sum;			// rolling sum of the payoffs
	int numSims;		// counter for the number of simulations

public:
	
	virtual ~Pricer() {}

	// Pricer takes a payoff function to compute payoffs for each path
	// public for easy access
	Payoff payoff;

	//constructor gives a payoff and discounting function
	Pricer(Payoff pOff, std::function<double(double)> disc);

	// process a path depending on the type of pricer
	virtual void processPath(std::vector<double>& path) = 0;
	// print price and number of simulations
	void printDetails();		
	// get discount factor
	double discountFactor(double t);		
	// calculate the price with rolling sum, numSims and discount factor
	double calcPrice(double t);
	// reset the pricer
	void reset();

};

#endif