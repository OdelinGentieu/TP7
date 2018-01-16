#ifndef FILE_ADVECTION_CPP

#include "Advection.h"
#include <fstream>
#include <iostream>

using namespace std;
using namespace Eigen;

double square(double x)
{
  return x*x;
}

// Constructeur
Advection::Advection(const DataFile& data, const Function& fct, const Mesh2D& mesh)
  : _function(fct), _mesh(mesh), _triangles(mesh.GetTriangles()), _edges(mesh.GetEdges()),
    _tri_center(mesh.GetTrianglesCenter()), _tri_area(mesh.GetTrianglesArea()),
    _edg_normal(mesh.GetEdgesNormal()), _edg_center(mesh.GetEdgesCenter())
{
  _results = data.Get_results();
  
  system(("mkdir -p ./" + data.Get_results()).c_str());
  system(("rm -f ./" + data.Get_results() + "/*.vtk").c_str());
  system(("cp ./" + data.Get_file_name() + " ./" + data.Get_results() + "/" + data.Get_file_name()).c_str());
  if (data.Get_numerical_flux_choice() == "centered")
    _type_flux = Centered;
  else
    _type_flux = Upwind;
}


// Construit le tableau contenant V pour tous les centres de triangle
void Advection::BuildVelocity(double t)
{
  int nb_tri = _triangles.size();
  _V.resize(nb_tri);
  
  // A FAIRE : remplir _V avec les vitesses pour chaque triangle
}


// Construit y = g(t, U)
void Advection::BuildF(const double& t, const Eigen::VectorXd& sol, Eigen::VectorXd& y)
{
  // on calcule v pour tous les triangles
  BuildVelocity(t);
  
  // A FAIRE : calculer y
}


// Construit la condition initiale au centre des triangles
VectorXd Advection::InitialCondition()
{
  VectorXd sol0(_triangles.size());

  //  A FAIRE : calculer la condition initiale au centre des triangles
  
  return sol0;
}


// Solution exacte au centre des triangles
VectorXd Advection::ExactSolution(double t)
{
  VectorXd exact_sol(_triangles.size());
  
  // A FAIRE : Construire exact_sol au centre des triangles
  
  return exact_sol;
}


// Sauvegarde la solution
void Advection::SaveSol(const VectorXd& sol, int n)
{
  string name_file = _results + "/solution_" + std::to_string(n) + ".vtk";
  
  const vector<Matrix<double, 2, 1> >& vertices = _mesh.GetVertices();
  int nb_vert = vertices.size();
  
  assert((sol.size() == int(_triangles.size())) && "The size of the solution vector is not the same than the number of _triangles !");
  

  ofstream solution;
  solution.open(name_file, ios::out);
  solution.precision(7);

  if (!solution.is_open())
    {
      cout << "Unable to open file " << name_file << endl;
      abort();
    }
  
  solution << "# vtk DataFile Version 3.0 " << '\n';
  solution << "2D Unstructured Grid" << '\n';
  solution << "ASCII" << '\n';
  solution << "DATASET UNSTRUCTURED_GRID" << '\n';

  solution << "POINTS " << nb_vert << " float " << '\n';
  for (int i = 0 ; i < nb_vert ; ++i)
    solution << vertices[i][0] << " " << vertices[i][1] << " 0." << '\n';
  
  solution << '\n';

  int nb_tri = _triangles.size();
  solution << "CELLS " << nb_tri << " " << nb_tri*4 << '\n';
  for (int i = 0 ; i < nb_tri ; ++i)
    solution << 3 << " " << _triangles[i].GetTriangle()[0] << " " << _triangles[i].GetTriangle()[1]
	     << " " << _triangles[i].GetTriangle()[2] << '\n';
  
  solution << '\n';

  solution << "CELL_TYPES " << nb_tri << '\n';
  for (int i = 0 ; i < nb_tri ; ++i)
    solution << 5 << '\n';

  solution << '\n';

  solution << "CELL_DATA " << nb_tri << '\n';
  solution << "SCALARS sol float 1" << '\n';
  solution << "LOOKUP_TABLE default" << '\n';
  for (int i = 0 ; i < nb_tri ; ++i)
    solution << float(sol[i]) << '\n';

  solution << '\n';
  
  solution.close();
}

#define FILE_ADVECTION_CPP
#endif
