#ifndef FILE_ADVECTION_H

#include <string>
#include "Dense"
#include "Sparse"

#include "Mesh2D.h"
#include "OdeSystem.h"
#include "DataFile.h"
#include "Function.h"

class Advection : public OdeSystem
{
 private:
  // Reference vers la classe Function (condition initale, sol exacte, vitesse)
  const Function& _function;
  
  // Reference de la classe Mesh2D (accès à tout ce qui concerne le maillage
  // et les données géométriques)
  const Mesh2D& _mesh;

  // Variables géométriques
  const std::vector<Triangle>& _triangles;
  const std::vector<Edge>& _edges;
  const std::vector<Eigen::Matrix<double, 2, 1> >& _tri_center;
  const std::vector<double>& _tri_area;
  const std::vector<Eigen::Matrix<double, 2, 1> >& _edg_normal;
  const std::vector<Eigen::Matrix<double, 2, 1> >& _edg_center;

  // repertoire de sortie
  std::string _results;
  
  // Le choix du flux
  int _type_flux; // Centered ou Upwind
  enum{Centered, Upwind};
  
  // ecoulement V aux centres des triangles
  std::vector<Eigen::Matrix<double, 2, 1> > _V;
  
 public:
  // Constructeur
  Advection(const DataFile& data, const Function& fct, const Mesh2D& mesh);
  
  // calcul de V au centre des triangles
  void BuildVelocity(double t);

  // Construit le vecteur f = g(u) (EDO : du/dt = g(u))
  void BuildF(const double& t, const Eigen::VectorXd& sol, Eigen::VectorXd& f);

  // Condition Initiale au centre des triangles
  Eigen::VectorXd InitialCondition();
  
  // Solution exacte au centre des triangles
  Eigen::VectorXd ExactSolution(double t);

  // Sauvegarde la solution
  void SaveSol(const Eigen::VectorXd& sol, int n);
    
};

#define FILE_ADVECTION_H
#endif
