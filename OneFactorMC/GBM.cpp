#include "GBM.hpp"

GBM::GBM(double rf, double sig, double cost, double init, double mat) : r(rf), vol(sig), q(cost), SDE(init, mat)
{
}

GBM::GBM(const GBM & gbm) : r(gbm.r), vol(gbm.vol), q(gbm.q), SDE(gbm.ic, gbm.exp)
{
}

double GBM::drift(double S, double t)
{
	return (r - q) * S;
}

double GBM::diffusion(double S, double t)
{
	return vol * S;
}

double GBM::diffusionPrime(double S, double t)
{
	return vol;
}