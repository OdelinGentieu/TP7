#ifndef FILE_TIME_SCHEME_H

#include "OdeSystem.h"

class TimeScheme
{
 protected:
  // Pas de temps
  double _dt;
  
  // Temps en cours
  double _t;
  
  // Vecteur solution
  Eigen::VectorXd _sol;

  // Reference vers le systeme d'EDO
  OdeSystem& _sys;
  
 public:
  // Constructeur avec le systeme d'EDO
  TimeScheme(OdeSystem& sys);
  
  // Destructeur par défaut - Si la classe ne contient pas de destructeur par défaut
  // alors le compilateur en génère un implicitement.
  virtual ~TimeScheme();
  
  // Initialisation de vos différentes variables
  virtual void Initialize(double t0, double dt, Eigen::VectorXd& rho0);
  
  // Une étape du schéma en temps
  virtual void Advance() = 0;

  // sortie
  void SaveSolution(int n);
  
  // Permet de récupérer _sol
  const Eigen::VectorXd & GetIterateSolution() const;
  
};


class EulerScheme : public TimeScheme
{
 private:
  // evaluation de f
  Eigen::VectorXd _f;
  
 public:
 EulerScheme(OdeSystem& sys) : TimeScheme(sys) {}

  void Initialize(double t0, double dt, Eigen::VectorXd& rho0);
  
  // Une étape du schéma en temps
  void Advance();
};

class RungeKuttaScheme : public TimeScheme
{
 private:
  Eigen::VectorXd k1, k2, k3, k4;
  
 public:
 RungeKuttaScheme(OdeSystem& sys) : TimeScheme(sys) {}

  void Initialize(double t0, double dt, Eigen::VectorXd& rho0);
  
  // Une étape du schéma en temps
  void Advance();
};

#define FILE_TIME_SCHEME_H
#endif
