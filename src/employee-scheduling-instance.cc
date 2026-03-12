#include "lib/employee-scheduling-instance.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <nlohmann/json.hpp>

EmployeeSchedulingInstance::EmployeeSchedulingInstance() : E(0), D(0), T(0) {}

void EmployeeSchedulingInstance::LoadFromJSON(const std::string& filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Cannot open file: " + filename);
  }

  nlohmann::json j;
  file >> j;

  E = j["employees"].size();
  T = j["shifts"].size();
  D = j["planningHorizon"];

  A.assign(E, std::vector<std::vector<int>>(D, std::vector<int>(T, 0)));
  for (const auto& s : j["satisfaction"]) {
    const int e = s["employee"];
    const int d = s["day"];
    const int t = s["shift"];
    const int v = s["value"];
    A[e][d][t] = v;
  }

  B.assign(D, std::vector<int>(T, 0));
  for (const auto& r : j["requiredEmployees"]) {
    const int d = r["day"];
    const int t = r["shift"];
    const int v = r["value"];
    B[d][t] = v;
  }

  C.assign(E, 0);
  for (int e = 0; e < E; ++e) {
    C[e] = j["employees"][e]["freeDays"];
  }
}

void EmployeeSchedulingInstance::Print() const {
  std::cout << "Employee Scheduling Instance:\n";
  std::cout << "Employees (E): " << E << "\n";
  std::cout << "Days (D): " << D << "\n";
  std::cout << "Shifts per day (T): " << T << "\n";
  std::cout << "\nSatisfaction A[e][d][t]:\n";
  for (int e = 0; e < E; ++e) {
    std::cout << "Employee " << e << ":\n";
    for (int d = 0; d < D; ++d) {
      for (int t = 0; t < T; ++t) {
        std::cout << A[e][d][t] << " ";
      }
      std::cout << "\n";
    }
    std::cout << "\n";
  }

  std::cout << "Minimum employees B[d][t]:\n";
  for (int d = 0; d < D; ++d) {
    for (int t = 0; t < T; ++t) {
      std::cout << B[d][t] << " ";
    }
    std::cout << "\n";
  }

  std::cout << "\nRest days C[e]:\n";
  for (int e = 0; e < E; ++e) {
    std::cout << "Employee " << e << ": " << C[e] << " rest days\n";
  }
}
