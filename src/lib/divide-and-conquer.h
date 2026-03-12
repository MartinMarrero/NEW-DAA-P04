/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos
 * 
 * @brief Header file for the Divide and Conquer framework
 * @since 25th of February, 2025
 * @authors Martín José Marrero Quintans, Fabián González Lence
 * @see { @link https://campusingenieriaytecnologia2425.ull.es/mod/assign/view.php?id=24915 }
 * @see { @link https://github.com/alu0101549491/DAA-P03.git }
 */

#ifndef DIVIDE_AND_CONQUER_H
#define DIVIDE_AND_CONQUER_H

#include "tools.h"
#include "algorithm.h"

class DivideAndConquer : public Algorithm {
 public:
  DivideAndConquer() {}
  virtual ~DivideAndConquer() {}
  virtual Solution Solve(Problem problem, int size, int depth_so_far);
  virtual std::string GetRecurrence() const = 0;
  virtual int GetRecursiveCalls() const { return recursive_calls_; }
  virtual int GetMaxDepth() const { return max_depth_; }
 protected:
  virtual bool Small(Problem problem) = 0;
  virtual Solution SolveSmall(Problem problem) = 0;
  virtual std::vector<Problem> Divide(Problem problem, int size) = 0;
  virtual Solution Combine(std::vector<Solution> solutions) = 0;
 private:
  int recursive_calls_ = 0;
  int max_depth_ = 0;
};

#endif  // DIVIDE_AND_CONQUER_H