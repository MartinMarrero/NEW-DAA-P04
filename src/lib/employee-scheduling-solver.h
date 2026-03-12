/**
 * @brief Base solver interface for Employee Scheduling.
 */

#ifndef EMPLOYEE_SCHEDULING_SOLVER_H
#define EMPLOYEE_SCHEDULING_SOLVER_H

#include <vector>

#include "employee-scheduling-instance.h"
#include "employee-scheduling-solution.h"

class EmployeeSchedulingSolver {
 public:
  virtual ~EmployeeSchedulingSolver() = default;
  virtual EmployeeSchedulingSolution Solve(const EmployeeSchedulingInstance& instance,
                                           const std::vector<int>& days) const = 0;
};

#endif  // EMPLOYEE_SCHEDULING_SOLVER_H
