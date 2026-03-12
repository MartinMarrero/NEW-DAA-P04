/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos
 * 
 * @brief Divide and Conquer framework implementation for multiple algorithms.
 * @since 25th of February, 2025
 * @authors Martín José Marrero Quintans, Fabián González Lence
 * @see { @link https://campusingenieriaytecnologia2425.ull.es/mod/assign/view.php?id=24915 }
 * @see { @link https://github.com/alu0101549491/DAA-P03.git }
 */

#include "lib/divide-and-conquer.h"

/**
 * @brief Checks if the problem is small enough to be solved directly
 * @param problem The problem to check
 * @return True if the problem is small enough to be solved directly, false otherwise
 */
Solution DivideAndConquer::Solve(Problem problem, int size, int depth_so_far = 0) {
  if (int(problem.size()) != size) throw std::invalid_argument("Problem size does not match the size parameter");
  max_depth_ = std::max(max_depth_, depth_so_far);
  if (Small(problem)) {
    return SolveSmall(problem);
  }
  std::vector<Problem> subproblems = Divide(problem, size);
  std::vector<Solution> solutions;
  for (auto& subproblem : subproblems) {
    recursive_calls_++;
    solutions.push_back(Solve(subproblem, subproblem.size(), depth_so_far + 1));
  }
  Solution solution = Combine(solutions);
  return solution;
}