/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos
 *
 * @brief Implementation of the Employee Scheduling problem using Divide and Conquer
 * @since March 9, 2026
 * @authors Martín José Marrero Quintans, Fabián González Lence
 * @see { @link https://campusingenieriaytecnologia2425.ull.es/mod/assign/view.php?id=24915 }
 * @see { @link https://github.com/alu0101549491/DAA-P03.git }
 */

#include "lib/employee-scheduling.h"
#include <algorithm>
#include <fstream>
#include <limits>
#include <stdexcept>

namespace {

EmployeeSchedulingSolution MergeSolutions(const EmployeeSchedulingInstance& instance,
                                         const EmployeeSchedulingSolution& sol1,
                                         const EmployeeSchedulingSolution& sol2) {
  EmployeeSchedulingSolution merged(instance);
  for (int e = 0; e < instance.E; ++e) {
    for (int d = 0; d < instance.D; ++d) {
      for (int t = 0; t < instance.T; ++t) {
        merged.X[e][d][t] = sol1.X[e][d][t];
      }
    }
  }
  for (int e = 0; e < instance.E; ++e) {
    int work_days_in_merged = 0;
    for (int d = 0; d < instance.D; ++d) {
      bool works = false;
      for (int t = 0; t < instance.T; ++t) {
        if (merged.X[e][d][t]) {
          works = true;
          break;
        }
      }
      if (works) {
        work_days_in_merged++;
      }
    }
    for (int d = 0; d < instance.D; ++d) {
      for (int t = 0; t < instance.T; ++t) {
        if (!sol2.X[e][d][t]) {
          continue;
        }
        bool already_works = false;
        for (int prev_t = 0; prev_t < instance.T; ++prev_t) {
          if (merged.X[e][d][prev_t]) {
            already_works = true;
            break;
          }
        }
        if (!already_works && work_days_in_merged < instance.D - instance.C[e]) {
          merged.X[e][d][t] = 1;
          work_days_in_merged++;
        }
      }
    }
  }
  return merged;
}

std::vector<int> BuildAllDays(int total_days) {
  std::vector<int> days(total_days);
  for (int d = 0; d < total_days; ++d) {
    days[d] = d;
  }
  return days;
}

}  // namespace

BinaryDivideAndConquerSolver::BinaryDivideAndConquerSolver(
    std::unique_ptr<EmployeeSchedulingSolver> small_solver)
    : small_solver_(std::move(small_solver)) {
  if (!small_solver_) {
    throw std::invalid_argument("BinaryDivideAndConquer requires a valid small solver");
  }
}

EmployeeSchedulingSolution BinaryDivideAndConquerSolver::Solve(
    const EmployeeSchedulingInstance& instance,
    const std::vector<int>& days) const {
  if (days.size() <= 1) {
    return small_solver_->Solve(instance, days);
  }
  const int mid = static_cast<int>(days.size() / 2);
  std::vector<int> left(days.begin(), days.begin() + mid);
  std::vector<int> right(days.begin() + mid, days.end());
  EmployeeSchedulingSolution sol1 = Solve(instance, left);
  EmployeeSchedulingSolution sol2 = Solve(instance, right);
  return MergeSolutions(instance, sol1, sol2);
}

std::unique_ptr<EmployeeSchedulingSolver> EmployeeSchedulingFactory::CreateFromJSONFile(
    const std::string& filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Cannot open algorithm config file: " + filename);
  }
  nlohmann::json config;
  file >> config;
  return CreateFromJSON(config);
}

std::unique_ptr<EmployeeSchedulingSolver> EmployeeSchedulingFactory::CreateFromJSON(
    const nlohmann::json& config) {
  if (!config.contains("class") || !config["class"].is_string()) {
    throw std::invalid_argument("Algorithm config must contain string field 'class'");
  }

  const std::string class_name = config["class"].get<std::string>();
  if (class_name == "Greedy") {
    return std::make_unique<GreedySolver>();
  }
  if (class_name == "DynamicProgramming") {
    return std::make_unique<DynamicProgrammingSolver>();
  }
  if (class_name == "BinaryDivideAndConquer") {
    if (!config.contains("smallSolver") || !config["smallSolver"].is_object()) {
      throw std::invalid_argument("BinaryDivideAndConquer requires object field 'smallSolver'");
    }
    return std::make_unique<BinaryDivideAndConquerSolver>(CreateFromJSON(config["smallSolver"]));
  }
  throw std::invalid_argument("Unknown algorithm class: " + class_name);
}

EmployeeSchedulingDyV::EmployeeSchedulingDyV(const EmployeeSchedulingInstance& instance)
    : instance_(instance),
      solver_(std::make_unique<BinaryDivideAndConquerSolver>(std::make_unique<GreedySolver>())) {}

EmployeeSchedulingDyV::EmployeeSchedulingDyV(const EmployeeSchedulingInstance& instance,
                                             std::unique_ptr<EmployeeSchedulingSolver> solver)
    : instance_(instance), solver_(std::move(solver)) {
  if (!solver_) {
    throw std::invalid_argument("EmployeeSchedulingDyV requires a valid solver");
  }
}

EmployeeSchedulingDyV EmployeeSchedulingDyV::FromJSONConfig(const EmployeeSchedulingInstance& instance,
                                                            const std::string& config_filename) {
  return EmployeeSchedulingDyV(instance, EmployeeSchedulingFactory::CreateFromJSONFile(config_filename));
}

/**
 * @brief Solve the problem using Divide and Conquer
 * @return The best solution found
 */
EmployeeSchedulingSolution EmployeeSchedulingDyV::Solve() {
  return solver_->Solve(instance_, BuildAllDays(instance_.D));
}