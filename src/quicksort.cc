/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos
 * 
 * @brief Source code file for the quicksort algorithm.
 * @since 25th of February, 2025
 * @authors Martín José Marrero Quintans, Fabián González Lence
 * @see { @link https://campusingenieriaytecnologia2425.ull.es/mod/assign/view.php?id=24915 }
 * @see { @link https://github.com/alu0101549491/DAA-P03.git }
 */

#include "lib/quicksort.h"

/**
 * @brief Function that checks if the problem is small enough to be solved.
 * @param problem The problem to be solved.
 * @return True if the problem is small enough to be solved, false otherwise.
 */
bool QuickSort::Small(Problem problem) {
  return problem.size() < 2;
}

/**
 * @brief Function that solves the problem when it is small enough.
 * @param problem The problem to be solved.
 * @return The solution to the problem.
 */
Solution QuickSort::SolveSmall(Problem problem) {
  Solution solution;
  if (problem.size() == 0) {
    return solution;
  }
  if (problem.size() == 1) {
    solution.push_back(problem[0]);
  }
  else if (problem[0] > problem[1]) {
    solution.push_back(problem[1]);
    solution.push_back(problem[0]);
  } 
  else {
    solution.push_back(problem[0]);
    solution.push_back(problem[1]);
  }
  return solution;
}

/**
 * @brief Function that divides the problem into smaller subproblems.
 * @param problem The problem to be solved.
 * @param size The size of the problem.
 * @return A vector containing the subproblems.
 */
std::vector<Problem> QuickSort::Divide(Problem problem, int size) {
  if (problem.size() <= 1) {
    return {problem};
  }
  int pivot = problem[0];
  Problem left, right;
  for (unsigned i = 1; i < problem.size(); ++i) {
    if (problem[i] <= pivot) {
      left.push_back(problem[i]);
    } 
    else {
      right.push_back(problem[i]);
    }
  }
  right.push_back(pivot);
  return {left, right};
}

/**
 * @brief Function that combines the solutions of the subproblems.
 * @param solutions The solutions of the subproblems.
 * @return The combined solution.
 */
Solution QuickSort::Combine(std::vector<Solution> solutions) {
  Solution combined_solution;
  for (auto solution : solutions) {
    for (unsigned i = 0; i < solution.size(); i++) {
      combined_solution.push_back(solution[i]);
    }
  }
  return combined_solution;
}