#ifndef FILE_ODE_SYSTEM_H

#include "Dense"
#include <fstream>

class OdeSystem
{
 public:
  // Constructeur par défaut
  OdeSystem();
  
  // Destructeur par défaut
  virtual ~OdeSystem();
  
  // Pour construire _f en fonction de votre système
  virtual void BuildF(const double& t, const Eigen::VectorXd& rho,
		      Eigen::VectorXd& f) = 0;

  virtual void SaveSol(const Eigen::VectorXd& sol, int n) = 0;
  
};

#define FILE_ODE_SYSTEM_H
#endif

