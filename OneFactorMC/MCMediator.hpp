// MCMediator
// Mediator class that communicates with all the other classes to make the simulation run

#ifndef MCMediator_HPP
#define MCMediator_HPP

#include <thread>
#include <mutex>
#include <future>
#include <cmath>

#include "MCBuilder.hpp"
#include "EuropeanPricer.hpp"

// how many threads are running simulations
#define NUM_THREADS 8

using PricerPtr = std::shared_ptr<Pricer>;

class MCMediator 
{
private:
	SDEPtr sde;	
	FDMPtr fdm;
	RNGPtr rng;

	// holds a pricer that processes the paths
	PricerPtr pricer;

	// number of simulations
	int numSims;

	// mutex common to the class when resources are shared between threads
	std::mutex mediatorMutex;

public:

	// constructor takes the tuple from MCBuilder as input and the number of simulations to be used
	MCMediator(std::tuple<SDEPtr, FDMPtr, RNGPtr> parts, int numSims, PricerPtr pricerPtr);

	// run the simulations
	void runSim();
	// simulations for one thread
	void runSubSim(std::vector<double>& path, int numSubSims, int threadNum);
};

#endif