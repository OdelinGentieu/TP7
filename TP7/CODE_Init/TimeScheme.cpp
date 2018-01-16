#ifndef FILE_TIME_SCHEME_CPP

#include "TimeScheme.h"
#include <iostream>

using namespace Eigen;
using namespace std;

// Constructeur avec le systeme d'edo a resoudre
TimeScheme::TimeScheme(OdeSystem& sys) : _sys(sys)
{}

// Destructeur (car on a des fonctions virtuelles)
TimeScheme::~TimeScheme()
{}

// Initialisation de vos différentes variables
void TimeScheme::Initialize(double t0, double dt, Eigen::VectorXd& rho0)
{
  _dt = dt;
  _t = t0;
  _sol = rho0;
}

// Renvoie _sol (pratique pour vérifier la résolution)
const VectorXd & TimeScheme::GetIterateSolution() const
{
  return _sol;
}

void TimeScheme::SaveSolution(int n)
{
  // on appelle SaveSol du systeme d'EDO
  _sys.SaveSol(_sol, n);
}
  
// Euler Explicite
void EulerScheme::Initialize(double t0, double dt, Eigen::VectorXd & sol0)
{
  TimeScheme::Initialize(t0, dt, sol0);
  _f.resize(_sol.rows());
}

void EulerScheme::Advance()
{
  _sys.BuildF(_t, _sol, _f);
  _sol += _dt*_f;
  _t += _dt;
}

// RungeKutta
void RungeKuttaScheme::Initialize(double t0, double dt, Eigen::VectorXd & sol0)
{
  TimeScheme::Initialize(t0, dt, sol0);
  k1.resize(sol0.rows());
  k2.resize(sol0.rows());
  k3.resize(sol0.rows());
  k4.resize(sol0.rows());
}

void RungeKuttaScheme::Advance()
{
  _sys.BuildF(_t, _sol, k1);
  _sys.BuildF(_t+_dt/2., _sol+_dt/2.*k1, k2);
  _sys.BuildF(_t+_dt/2., _sol+_dt/2.*k2, k3);
  _sys.BuildF(_t+_dt, _sol+_dt*k3, k4);
  _sol += _dt/6.*(k1 + 2.*k2 + 2.*k3 + k4);
  _t += _dt; 
}

#define FILE_TIME_SCHEME_CPP
#endif
