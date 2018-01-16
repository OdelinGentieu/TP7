#ifndef FILE_FUNCTION_H

#include "DataFile.h"

class Function
{
 private:
  int type_init; // Gaussian or Rectangular
  enum {Gaussian, Rectangular};

  int type_velocity; // Uniform, Rotational or Sinusoidal
  enum {Uniform, Rotational, Sinusoidal};

  // parameters x0, y0, a, b, c, d, e and f
  double x0, y0, a, b, c, d, e, f;
  
  bool _in_flow;
  
 public: // Méthodes et opérateurs de la classe
  Function(DataFile& data_file);

  double ExactSolution(const double x, const double y, const double t) const;
  double InitialCondition(const double x, const double y) const;
  double Velocity_x(const double x, const double y, const double t) const;
  double Velocity_y(const double x, const double y, const double t) const;
  
};

#define FILE_FUNCTION_H
#endif
