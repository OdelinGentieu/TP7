#include <iostream>
#include <fstream>
#include <chrono>

#include "Advection.h"
#include "TimeScheme.h"

using namespace std;
using namespace Eigen;

int main(int argc, char** argv)
{
  if (argc < 2)
    {
      cout << "Please, enter the name of your data file." << endl;
      abort();
    }
  
  const string data_file_name = argv[1];
  
  // ----------------------- Fichier de données --------------------------------
  DataFile data_file(data_file_name);
  data_file.ReadDataFile();

  // ------------------Définition du nombre d'itérations------------------------
  int nb_iterations = int(ceil((data_file.Get_tfinal()-data_file.Get_t0())/data_file.Get_dt()));
  data_file.Adapt_dt(data_file.Get_tfinal() / nb_iterations);
  
  // ---------------------------- Lecture maillage  ----------------------------------
  Mesh2D mesh;
  mesh.Read(data_file.Get_mesh_name());

  // Fonctions a utiliser
  Function source_fct(data_file);

  // objet principal pour resoudre le pb d'advection
  Advection adv(data_file, source_fct, mesh);

  // schema en temps
  TimeScheme* time_scheme = NULL;

  if (data_file.Get_scheme() == "RungeKutta")
    time_scheme = new RungeKuttaScheme(adv);
  else
    time_scheme = new EulerScheme(adv);
  
  // on calcule la condition initiale
  VectorXd sol0 = adv.InitialCondition();

  time_scheme->Initialize(data_file.Get_t0(), data_file.Get_dt(), sol0);
  time_scheme->SaveSolution(0);

  // enlever la ligne suivante lorsque vous aurez construit BuildF correctement
  return 0;
  
  // démarrage du chrono
  auto start = chrono::high_resolution_clock::now();
  
  // boucle principale en temps
  for (int nt = 0; nt < nb_iterations; nt++)
    {
      time_scheme->Advance();
      time_scheme->SaveSolution(nt);
    }  

  // Fin du chrono
  auto finish = chrono::high_resolution_clock::now();
  double t = chrono::duration_cast<chrono::seconds>(finish-start).count();

  // Affichage du chrono
  cout << "Cela a pris "<< t << " seconds" << endl;

  //------------------- Si on connait la solution exacte -----------------------
  if (data_file.Get_velocity_choice() == "uniform")
    {
      VectorXd exact_sol = adv.ExactSolution(data_file.Get_tfinal());
      VectorXd approx_sol = time_scheme->GetIterateSolution();
      double error = ((approx_sol-exact_sol).array().abs()).maxCoeff();
      cout << "Erreur = " << error << endl;
      cout << "-------------------------------------------------" << endl;
    }
  
  delete time_scheme;
  
  return 0;
}
