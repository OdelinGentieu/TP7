#ifndef FILE_DATA_FILE_H

#include <string>
#include <vector>
#include <iostream>

// Définition de la classe
class DataFile
{
 private:
  std::string _file_name;
  double _t0;
  double _tfinal;
  double _dt;
  double _x0, _y0, _a, _b, _c, _d, _e, _f;

  std::string _mesh_name;
  std::string _scheme;
  std::string _velocity_choice;
  std::string _initial_condition_choice;
  std::string _numerical_flux_choice;
  std::string _results;

  bool _if_mesh_name;
  bool _if_t0;
  bool _if_tfinal;
  bool _if_dt;
  bool _if_scheme;
  bool _if_velocity_choice;
  bool _if_initial_condition_choice;
  bool _if_numerical_flux_choice;
  bool _if_results;

 public: // Méthodes et opérateurs de la classe
  DataFile(std::string file_name);
  void ReadDataFile();
  
  inline std::string Get_file_name() const {return _file_name;}
  inline void Adapt_dt(double dt) {_dt = dt;};
  inline double Get_t0() const {return _t0;};
  inline double Get_tfinal() const {return _tfinal;};
  inline double Get_dt() const {return _dt;};

  inline double Get_param_x0() const { return _x0; }
  inline double Get_param_y0() const { return _y0; }
  inline double Get_param_a() const { return _a; }
  inline double Get_param_b() const { return _b; }
  inline double Get_param_c() const { return _c; }
  inline double Get_param_d() const { return _d; }
  inline double Get_param_e() const { return _e; }
  inline double Get_param_f() const { return _f; }
  
  inline std::string Get_mesh_name() const { return _mesh_name;};
  inline std::string Get_scheme() const { return _scheme;};
  inline std::string Get_velocity_choice() const { return _velocity_choice;};
  inline std::string Get_initial_condition_choice() const { return _initial_condition_choice;};
  inline std::string Get_numerical_flux_choice() const { return _numerical_flux_choice;};
  inline std::string Get_results() const { return _results;};
  
};

#define FILE_DATA_FILE_H
#endif
