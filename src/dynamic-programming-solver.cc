#include "lib/dynamic-programming-solver.h"

#include <algorithm>
#include <vector>

EmployeeSchedulingSolution DynamicProgrammingSolver::Solve(const EmployeeSchedulingInstance& instance,
                                                           const std::vector<int>& days) const {
  EmployeeSchedulingSolution sol(instance);

  // remaining_work_days[e] tracks how many days employee e can still work.
  std::vector<int> remaining_work_days(instance.E, 0);
  for (int e = 0; e < instance.E; ++e) {
    remaining_work_days[e] = instance.D - instance.C[e];
  }

  for (int d : days) {
    std::vector<int> available_employees;
    available_employees.reserve(instance.E);
    for (int e = 0; e < instance.E; ++e) {
      if (remaining_work_days[e] > 0) {
        available_employees.push_back(e);
      }
    }

    std::vector<int> slots;
    for (int t = 0; t < instance.T; ++t) {
      const int required = std::max(0, instance.B[d][t]);
      for (int count = 0; count < required; ++count) {
        slots.push_back(t);
      }
    }

    const int n = static_cast<int>(available_employees.size());
    const int k_slots = static_cast<int>(slots.size());
    if (n == 0 || k_slots == 0) {
      continue;
    }

    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(k_slots + 1, 0));
    std::vector<std::vector<bool>> take(n + 1, std::vector<bool>(k_slots + 1, false));

    for (int e = 1; e <= n; ++e) {
      const int employee = available_employees[e - 1];
      for (int k = 1; k <= k_slots; ++k) {
        const int shift = slots[k - 1];
        const int skip_employee = dp[e - 1][k];
        const int assign_employee = dp[e - 1][k - 1] + instance.A[employee][d][shift];
        if (assign_employee > skip_employee) {
          dp[e][k] = assign_employee;
          take[e][k] = true;
        } else {
          dp[e][k] = skip_employee;
        }
      }
    }

    int k = k_slots;
    for (int e = n; e >= 1 && k >= 1; --e) {
      if (!take[e][k]) {
        continue;
      }
      const int employee = available_employees[e - 1];
      const int shift = slots[k - 1];
      sol.X[employee][d][shift] = 1;
      remaining_work_days[employee]--;
      k--;
    }
  }

  return sol;
}
