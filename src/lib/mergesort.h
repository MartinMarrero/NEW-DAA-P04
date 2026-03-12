/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos
 * 
 * @brief Header file for the quicksort algorithm.
 * @since 25th of February, 2025
 * @authors Martín José Marrero Quintans, Fabián González Lence
 * @see { @link https://campusingenieriaytecnologia2425.ull.es/mod/assign/view.php?id=24915 }
 * @see { @link https://github.com/alu0101549491/DAA-P03.git }
 */

#ifndef MERGESORT_H
#define MERGESORT_H

#include "divide-and-conquer.h"

class MergeSort : public DivideAndConquer {
 public:
  MergeSort() {}
  ~MergeSort() {}
  bool Small(Problem problem);
  Solution SolveSmall(Problem problem);
  std::vector<Problem> Divide(Problem problem, int size);
  Solution Combine(std::vector<Solution> solutions);
  std::string GetRecurrence() const { return recurrence_; }
 private:
  std::string recurrence_ = "2T(n/2) + O(n)";
};



#endif // MERGESORT_H