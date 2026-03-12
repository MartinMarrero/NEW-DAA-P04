/**
 * @brief Binary Divide and Conquer solver for Employee Scheduling.
 */

#ifndef BINARY_DIVIDE_AND_CONQUER_SOLVER_H
#define BINARY_DIVIDE_AND_CONQUER_SOLVER_H

#include <memory>

#include "employee-scheduling-solver.h"

class BinaryDivideAndConquerSolver : public EmployeeSchedulingSolver {
 public:
  explicit BinaryDivideAndConquerSolver(std::unique_ptr<EmployeeSchedulingSolver> small_solver);
  EmployeeSchedulingSolution Solve(const EmployeeSchedulingInstance& instance,
                                   const std::vector<int>& days) const override;

 private:
  std::unique_ptr<EmployeeSchedulingSolver> small_solver_;
};

#endif  // BINARY_DIVIDE_AND_CONQUER_SOLVER_H
