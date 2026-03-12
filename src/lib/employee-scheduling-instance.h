/**
 * @brief Employee Scheduling instance definition.
 */

#ifndef EMPLOYEE_SCHEDULING_INSTANCE_H
#define EMPLOYEE_SCHEDULING_INSTANCE_H

#include <string>
#include <vector>

class EmployeeSchedulingInstance {
 public:
  int E;
  int D;
  int T;
  std::vector<std::vector<std::vector<int>>> A;
  std::vector<std::vector<int>> B;
  std::vector<int> C;

  EmployeeSchedulingInstance();
  void LoadFromJSON(const std::string& filename);
  void Print() const;
};

#endif  // EMPLOYEE_SCHEDULING_INSTANCE_H
