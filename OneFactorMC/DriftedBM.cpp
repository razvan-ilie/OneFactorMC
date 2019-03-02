#include "DriftedBM.hpp"

DriftedBM::DriftedBM(double rf, double sig, double cost, double init, double mat) : r(rf), vol(sig), q(cost), SDE(init, mat)
{
}

DriftedBM::DriftedBM(const DriftedBM & bm) : r(bm.r), vol(bm.vol), q(bm.q), SDE(bm.ic, bm.exp)
{
}

double DriftedBM::drift(double S, double t)
{
	return r;
}

double DriftedBM::diffusion(double S, double t)
{
	return vol;
}

double DriftedBM::diffusionPrime(double S, double t)
{
	return 0.0;
}