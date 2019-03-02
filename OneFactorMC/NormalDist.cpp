#include "NormalDist.hpp"

NormalDist::NormalDist() : mu(0.), sig(1.), RNG()
{
}

NormalDist::NormalDist(int seed) : mu(0.), sig(1.), RNG(seed)
{
}

NormalDist::NormalDist(double mean, double sigma) : mu(mean), sig(sigma), RNG()
{
}

NormalDist::NormalDist(double mean, double sigma, int seed) : mu(mean), sig(sigma), RNG(seed)
{
}

double NormalDist::mean()
{
	return mu;
}

double NormalDist::stdDev()
{
	return sig;
}

void NormalDist::mean(double newMu)
{
	mu = newMu;
}

void NormalDist::stdDev(double newSig)
{
	sig = newSig;
}

double NormalDist::operator()()
{
	return normDist(randEngine);
}

RNGPtr NormalDist::copy() const
{
	return RNGPtr( new NormalDist(*this) );
}
