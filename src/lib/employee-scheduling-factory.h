/**
 * @brief Factory for Employee Scheduling solvers.
 */

#ifndef EMPLOYEE_SCHEDULING_FACTORY_H
#define EMPLOYEE_SCHEDULING_FACTORY_H

#include <memory>
#include <string>

#include <nlohmann/json.hpp>

#include "employee-scheduling-solver.h"

class EmployeeSchedulingFactory {
 public:
  static std::unique_ptr<EmployeeSchedulingSolver> CreateFromJSONFile(const std::string& filename);
  static std::unique_ptr<EmployeeSchedulingSolver> CreateFromJSON(const nlohmann::json& config);
};

#endif  // EMPLOYEE_SCHEDULING_FACTORY_H
