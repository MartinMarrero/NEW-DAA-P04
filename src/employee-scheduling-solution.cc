#include "lib/employee-scheduling-solution.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

EmployeeSchedulingSolution::EmployeeSchedulingSolution(const EmployeeSchedulingInstance& instance)
    : X(instance.E, std::vector<std::vector<int>>(instance.D, std::vector<int>(instance.T, 0))) {}

int EmployeeSchedulingSolution::CalculateObjective(const EmployeeSchedulingInstance& instance) const {
  int suma_satisfaccion = 0;
  int suma_turnos_cubiertos = 0;
  for (int e = 0; e < instance.E; ++e) {
    for (int d = 0; d < instance.D; ++d) {
      for (int t = 0; t < instance.T; ++t) {
        if (X[e][d][t]) {
          suma_satisfaccion += instance.A[e][d][t];
        }
      }
    }
  }
  for (int d = 0; d < instance.D; ++d) {
    for (int t = 0; t < instance.T; ++t) {
      int empleados_en_turno = 0;
      for (int e = 0; e < instance.E; ++e) {
        empleados_en_turno += X[e][d][t];
      }
      if (empleados_en_turno >= instance.B[d][t]) {
        suma_turnos_cubiertos++;
      }
    }
  }
  return suma_satisfaccion + 100 * suma_turnos_cubiertos;
}

bool EmployeeSchedulingSolution::CheckRestDays(const EmployeeSchedulingInstance& instance) const {
  for (int e = 0; e < instance.E; ++e) {
    int work_days = 0;
    for (int d = 0; d < instance.D; ++d) {
      bool works = false;
      for (int t = 0; t < instance.T; ++t) {
        if (X[e][d][t]) {
          works = true;
          break;
        }
      }
      if (works) {
        work_days++;
      }
    }
    const int rest_days = instance.D - work_days;
    if (rest_days < instance.C[e]) {
      return false;
    }
  }
  return true;
}

void EmployeeSchedulingSolution::Print() const {
  const unsigned E = X.size();
  const unsigned D = X[0].size();
  const unsigned T = X[0][0].size();

  std::cout << "\nSchedule\n\n";
  std::cout << "            ";
  for (unsigned d = 0; d < D; ++d) {
    std::cout << "Dia " << d + 1 << "      ";
  }
  std::cout << "\n";

  for (unsigned e = 0; e < E; ++e) {
    std::cout << "Empleado " << e + 1 << "   ";
    for (unsigned d = 0; d < D; ++d) {
      for (unsigned t = 0; t < T; ++t) {
        if (X[e][d][t]) {
          std::cout << "■ ";
        } else {
          std::cout << "□ ";
        }
      }
      std::cout << "     ";
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}

void EmployeeSchedulingSolution::ExportToFile(const std::string& filename) const {
  std::ofstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Cannot open file: " + filename);
  }

  file << "Employee Scheduling Solution:\n";
  for (unsigned e = 0; e < X.size(); ++e) {
    file << "Employee " << e << " schedule:\n";
    for (unsigned d = 0; d < X[e].size(); ++d) {
      file << "  Day " << d << ": ";
      for (unsigned t = 0; t < X[e][d].size(); ++t) {
        if (X[e][d][t]) {
          file << "Shift " << t << " ";
        }
      }
      file << "\n";
    }
    file << "\n";
  }
}
