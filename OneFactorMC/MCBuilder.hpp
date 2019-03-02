// MCBuilder
// Builder class that takes all necessary data to price an option and
// returns the objects that are needed for pricing
// Base class

// This class would be easy to modify in case we add new specific objects for the other base classes
// We simply add a new element to the respective enum class

#ifndef MCBuilder_HPP
#define MCBuilder_HPP

#include <tuple>
#include <memory>
#include <vector>
#include <iostream>
#include "Exception.hpp"

#include "GBM.hpp"
#include "DriftedBM.hpp"

#include "Euler.hpp"
#include "Milstein.hpp"

#include "NormalDist.hpp"

using SDEPtr = std::shared_ptr<iSDE>;
using FDMPtr = std::shared_ptr<iFDM>;
using RNGPtr = std::shared_ptr<RNG>;

// the enum classes let the user easily select what kind of objects they want to create
// just add a new element to an enum when a new class is created


enum class SDEType
{
	GBM			= 1,
	DriftedBM	= 2
};

enum class FDMType 
{
	Euler		= 1,
	Milstein	= 2
};

enum class RNGType 
{
	Normal		= 1
};

// template parameters are parameter packs for the arguments that will be passed in as arguments to the constructors
// note: FDM always only takes an SDE and a number of steps
class MCBuilder 
{
private:

	// check if the arguments are set to build the objects
	bool argsSetFlag;

	// members are elements of the enum classes
	// these define which objects the builder will create
	// these members can be changed through setter functions
	SDEType builderSDE;
	FDMType builderFDM;
	RNGType builderRNG;

	// arguments for SDE constructor
	std::vector<double> sdeArgs;
	// number of steps for FDM
	int numSteps;
	// arguments for constructor of RNG
	std::vector<double> rngArgs;


	// functions that build each part to send to the mediator
	SDEPtr getSDE();
	FDMPtr getFDM(SDEPtr sdePtr);
	RNGPtr getRNG();

public:

	// parameter constructor selects type of SDE, FDM and RNG
	// size of argument vectors can now properly be determined based on type of objects given
	MCBuilder	(	SDEType chooseSDE,
					FDMType chooseFDM,
					RNGType chooseRNG
				);

	// set the arguments to build the objects
	// also set the flag to signal that arguments are set
	void setArgs(	const std::vector<double>& SDEArgs,
					int numSteps,
					const std::vector<double>& RNGArgs
				);

	// return a tuple with the required objects for the Mediator
	std::tuple<SDEPtr, FDMPtr, RNGPtr> parts();


};

#endif