#include "Feller.hpp"

Feller::Feller(double k, double th, double sig, double init, double mat) : kappa(k), theta(th), vol(sig), SDE(init, mat)
{
}

Feller::Feller(const Feller & f) : kappa(f.kappa), theta(f.theta), vol(f.vol), SDE(f.ic, f.exp)
{
}

double Feller::drift(double S, double t)
{
	return kappa * (theta - S);
}

double Feller::diffusion(double S, double t)
{
	return vol * S;
}

double Feller::diffusionPrime(double S, double t)
{
	return vol;
}