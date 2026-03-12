/**
 * @brief Divide and Conquer wrapper for Employee Scheduling.
 */

#ifndef EMPLOYEE_SCHEDULING_DYV_H
#define EMPLOYEE_SCHEDULING_DYV_H

#include <memory>
#include <string>

#include "employee-scheduling-instance.h"
#include "employee-scheduling-solution.h"
#include "employee-scheduling-solver.h"

class EmployeeSchedulingDyV {
 public:
  explicit EmployeeSchedulingDyV(const EmployeeSchedulingInstance& instance);
  EmployeeSchedulingDyV(const EmployeeSchedulingInstance& instance,
                        std::unique_ptr<EmployeeSchedulingSolver> solver);
  static EmployeeSchedulingDyV FromJSONConfig(const EmployeeSchedulingInstance& instance,
                                              const std::string& config_filename);
  EmployeeSchedulingSolution Solve();

 private:
  EmployeeSchedulingInstance instance_;
  std::unique_ptr<EmployeeSchedulingSolver> solver_;
};

#endif  // EMPLOYEE_SCHEDULING_DYV_H
