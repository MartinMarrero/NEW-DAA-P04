/**
 * @brief Employee Scheduling solution definition.
 */

#ifndef EMPLOYEE_SCHEDULING_SOLUTION_H
#define EMPLOYEE_SCHEDULING_SOLUTION_H

#include <string>
#include <vector>

#include "employee-scheduling-instance.h"

class EmployeeSchedulingSolution {
 public:
  std::vector<std::vector<std::vector<int>>> X;

  explicit EmployeeSchedulingSolution(const EmployeeSchedulingInstance& instance);
  int CalculateObjective(const EmployeeSchedulingInstance& instance) const;
  bool CheckRestDays(const EmployeeSchedulingInstance& instance) const;
  void Print() const;
  void ExportToFile(const std::string& filename) const;
};

#endif  // EMPLOYEE_SCHEDULING_SOLUTION_H
