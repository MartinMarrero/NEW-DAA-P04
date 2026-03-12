/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos
 * 
 * @brief Source code file for the mergesort algorithm.
 * @since 25th of February, 2025
 * @authors Martín José Marrero Quintans, Fabián González Lence
 * @see { @link https://campusingenieriaytecnologia2425.ull.es/mod/assign/view.php?id=24915 }
 * @see { @link https://github.com/alu0101549491/DAA-P03.git }
 */

#include "lib/mergesort.h"

/**
 * @brief Function that checks if the problem is small enough to be solved.
 * @param problem The problem to be solved.
 * @return True if the problem is small enough to be solved, false otherwise.
 */
bool MergeSort::Small(Problem problem) {
  return problem.size() <= 1;
}

/**
 * @brief Function that solves the problem when it is small enough.
 * @param problem The problem to be solved.
 * @return The solution to the problem.
 */
Solution MergeSort::SolveSmall(Problem problem) {
  return problem;
}

/**
 * @brief Function that divides the problem into subproblems.
 * @param problem The problem to be solved.
 * @param size The size of the problem.
 * @return A vector containing the subproblems.
 */
std::vector<Problem> MergeSort::Divide(Problem problem, int size) {
  std::vector<Problem> subproblems;
  Problem subproblem_1;
  Problem subproblem_2;
  for (unsigned i = 0; i < problem.size(); i++) {
    if (i < problem.size() / 2) {
      subproblem_1.push_back(problem[i]);
    } else {
      subproblem_2.push_back(problem[i]);
    }
  }
  subproblems.push_back(subproblem_1);
  subproblems.push_back(subproblem_2);
  return subproblems;
}

/**
 * @brief Function that combines the solutions of the subproblems.
 * @param solutions The solutions of the subproblems.
 * @return The solution to the problem.
 */
Solution MergeSort::Combine(std::vector<Solution> solutions) {
  Solution solution1 = solutions[0];
  Solution solution2 = solutions[1];
  Solution solution;
  unsigned i = 0;
  unsigned j = 0;
  while (i < solution1.size() && j < solution2.size()) {
    if (solution1[i] < solution2[j]) {
      solution.push_back(solution1[i]);
      i++;
    } else {
      solution.push_back(solution2[j]);
      j++;
    }
  }
  while (i < solution1.size()) {
    solution.push_back(solution1[i]);
    i++;
  }
  while (j < solution2.size()) {
    solution.push_back(solution2[j]);
    j++;
  }
  return solution;
}