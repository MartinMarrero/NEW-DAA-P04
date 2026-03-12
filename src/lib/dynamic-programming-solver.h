/**
 * @brief Dynamic Programming solver for Employee Scheduling.
 */

#ifndef DYNAMIC_PROGRAMMING_SOLVER_H
#define DYNAMIC_PROGRAMMING_SOLVER_H

#include "employee-scheduling-solver.h"

class DynamicProgrammingSolver : public EmployeeSchedulingSolver {
 public:
  EmployeeSchedulingSolution Solve(const EmployeeSchedulingInstance& instance,
                                   const std::vector<int>& days) const override;
};

#endif  // DYNAMIC_PROGRAMMING_SOLVER_H
