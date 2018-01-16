#ifndef _FUNCTION_CPP

#include "Function.h"

#include <cmath>

using namespace std;

Function::Function(DataFile& data_file)
{
  x0 = data_file.Get_param_x0();
  y0 = data_file.Get_param_y0();
  a = data_file.Get_param_a();
  b = data_file.Get_param_b();
  c = data_file.Get_param_c();
  d = data_file.Get_param_d();
  e = data_file.Get_param_e();
  f = data_file.Get_param_f();
  if (data_file.Get_initial_condition_choice() == "gaussian")
    type_init = Gaussian;
  else if (data_file.Get_initial_condition_choice() == "rectangular")
    type_init = Rectangular;
  else
    {
      cout << "Invalid initial condition" << endl;
      abort();
    }

  if (data_file.Get_velocity_choice() == "uniform")
    type_velocity = Uniform;
  else if (data_file.Get_velocity_choice() == "rotational")
    type_velocity = Rotational;
  else if (data_file.Get_velocity_choice() == "sinusoidal")
    type_velocity = Sinusoidal;
  else
    {
      cout << "Invalid velocity" << endl;
      abort();
    }

}

double Function::ExactSolution(const double x, const double y, const double t) const
{
  if (type_velocity != Uniform)
    {
      std::cout << "The exact solution is not known !" << std::endl;
      exit(0);
    }
  
  return 0.; // TODO : À compléter
}

double Function::InitialCondition(const double x, const double y) const
{
  switch (type_init)
    {
    case Gaussian:
      return 0.; // TODO :  À compléter
    case Rectangular:
      return 0.; // TODO : À compléter
    }

  return 0.0;
}

double Function::Velocity_x(const double x, const double y, const double t) const
{
  switch (type_velocity)
    {
    case Uniform:
      return 0.; // TODO : À compléter
    case Rotational:
      return 0.; // TODO : À compléter
    case Sinusoidal:
      return 0.; // TODO : À compléter
    }

  return 0.0;
}

double Function::Velocity_y(const double x, const double y, const double t) const
{
  switch (type_velocity)
    {
    case Uniform:
      return 0.; // TODO : À compléter
    case Rotational:
      return 0.; // TODO : À compléter
    case Sinusoidal:
      return 0.; // TODO : À compléter
    }

  return 0.0;
}


#define FILE_FUNCTION_CPP
#endif
