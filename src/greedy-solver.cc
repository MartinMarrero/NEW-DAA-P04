#include "lib/greedy-solver.h"
#include <algorithm>
#include <utility>
#include <vector>

EmployeeSchedulingSolution GreedySolver::Solve(const EmployeeSchedulingInstance& instance,
                                               const std::vector<int>& days) const {
  EmployeeSchedulingSolution sol(instance);
  for (int d : days) {
    for (int t = 0; t < instance.T; ++t) {
      std::vector<std::pair<int, int>> candidates;
      for (int e = 0; e < instance.E; ++e) {
        int current_work_days = 0;
        for (int prev_d = 0; prev_d < d; ++prev_d) {
          for (int prev_t = 0; prev_t < instance.T; ++prev_t) {
            if (sol.X[e][prev_d][prev_t]) {
              current_work_days++;
            }
          }
        }
        if (current_work_days < instance.D - instance.C[e]) {
          candidates.emplace_back(instance.A[e][d][t], e);
        }
      }
      std::sort(candidates.rbegin(), candidates.rend());
      for (int i = 0; i < std::min(instance.B[d][t], static_cast<int>(candidates.size())); ++i) {
        const int employee = candidates[i].second;
        sol.X[employee][d][t] = 1;
      }
    }
  }
  return sol;
}
