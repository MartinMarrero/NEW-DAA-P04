/**
 * @brief Greedy solver for Employee Scheduling.
 */

#ifndef GREEDY_SOLVER_H
#define GREEDY_SOLVER_H

#include "employee-scheduling-solver.h"

class GreedySolver : public EmployeeSchedulingSolver {
 public:
  EmployeeSchedulingSolution Solve(const EmployeeSchedulingInstance& instance,
                                   const std::vector<int>& days) const override;
};

#endif  // GREEDY_SOLVER_H
