/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos
 * 
 * @brief Header file for the base Algoritmo class
 * @since 25th of February, 2025
 * @authors Martín José Marrero Quintans, Fabián González Lence
 * @see { @link https://campusingenieriaytecnologia2425.ull.es/mod/assign/view.php?id=24915 }
 * @see { @link https://github.com/alu0101549491/DAA-P03.git }
 */

#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "tools.h"

class Algorithm {
 public:
  Algorithm() {}
  virtual ~Algorithm() {}
  virtual Solution Solve(Problem problem, int size, int depth_so_far) = 0;
};

#endif  // ALGORITHM_H