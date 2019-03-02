// RNG
// Abstract class that serves as a base class for RNGs
// Base class

// Here, we simply overload the () operator to get a random number from the desired distributions
// Each distribution will be a derived class

#ifndef RNG_HPP
#define RNG_HPP

#include <random>
#include <chrono>
#include <memory>

//to easily input a seed
using myClock = std::chrono::high_resolution_clock;

class RNG
{
protected:
	// mersenne twister random engine
	std::mt19937 randEngine;

	// gives it a seed based on time to ensure it is different each time
	RNG();
	// give a specific seed to try to reproduce results
	RNG(int seed);

public:
	using RNGPtr = std::shared_ptr<RNG>;

	// virtual destructor
	virtual ~RNG() {}

	// generate a random number
	virtual double operator()() = 0;

	// copy the object in the RNGPtr and create a new pointer to it
	virtual RNGPtr copy() const = 0;
};

#endif