/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos
 * 
 * @brief Main file for the Divide and Conquer program
 * @since 25th of February, 2025
 * @authors Martín José Marrero Quintans, Fabián González Lence
 * @see { @link https://campusingenieriaytecnologia2425.ull.es/mod/assign/view.php?id=24915 }
 * @see { @link https://github.com/alu0101549491/DAA-P03.git }
 */

#include <fstream>
#include "lib/mergesort.h"
#include "lib/quicksort.h"
#include "lib/employee-scheduling.h"
#include "lib/tools.h"

/**
 * @brief Executes the algorithm and measures the time it takes to solve the problem
 * @param algorithm The algorithm to be executed
 * @param problem The problem to be solved
 * @param time The time it takes to solve the problem
 * @return The solution to the problem
 */
Solution ExecuteAlgorithm(DivideAndConquer* algorithm, Problem problem, double& time) {
  clock_t start, end;
  start = clock();
  Solution solution = algorithm->Solve(problem, problem.size(), 0);
  end = clock();
  time += double(end - start) / CLOCKS_PER_SEC;
  delete algorithm;
  return solution;
}

int main(int argc, char* argv[]) {
  srand(time(NULL));
  bool debugMode = argc > 1 && std::string(argv[1]) == "-d";
  bool comparingSolversMode = argc > 1 && std::string(argv[1]) == "-c";
  
  if (debugMode) {
    // Interactive mode
    std::cout << Colors::CYAN << "=== Divide and Conquer Algorithms ===\n" << Colors::RESET;
    std::cout << "Choose an option:\n";
    std::cout << "1. Employee Scheduling Problem\n";
    std::cout << "2. Other Divide and Conquer Algorithms\n";
    std::cout << "Enter your choice: ";
    
    int main_choice;
    std::cin >> main_choice;
    
    if (main_choice == 1) {
      // Employee Scheduling
      std::string json_file;
      std::string algorithm_config;
      std::cout << "Enter instance JSON file path: ";
      std::cin >> json_file;
      std::cout << "Enter algorithm config JSON file path: ";
      std::cin >> algorithm_config;
      EmployeeSchedulingInstance instance;
      try {
        instance.LoadFromJSON(json_file);
        std::cout << "\n" << Colors::GREEN << "Instance loaded successfully!" << Colors::RESET << "\n";
        instance.Print();
        
        EmployeeSchedulingDyV emp_sched = EmployeeSchedulingDyV::FromJSONConfig(instance, algorithm_config);
        double time = 0.0;
        clock_t start = clock();
        EmployeeSchedulingSolution sol = emp_sched.Solve();
        clock_t end = clock();
        time = double(end - start) / CLOCKS_PER_SEC;
        
        std::cout << "\n" << Colors::YELLOW << "=== SOLUTION ===" << Colors::RESET << "\n";
        std::cout << "Objective value: " << sol.CalculateObjective(instance) << "\n";
        sol.Print();
        std::cout << "Time: " << time << " seconds\n";
        
        // Ask if user wants to export to file
        std::cout << "\nExport solution to file? (y/n): ";
        char export_choice;
        std::cin >> export_choice;
        if (export_choice == 'y' || export_choice == 'Y') {
          std::string filename;
          std::cout << "Enter filename: ";
          std::cin >> filename;
          sol.ExportToFile(filename);
          std::cout << "Solution exported to " << filename << "\n";
        }
        
      } catch (const std::exception& e) {
        std::cout << Colors::RED << "Error: " << e.what() << Colors::RESET << "\n";
      }
    } else if (main_choice == 2) {
      // Other algorithms - debug mode style
      int size;
      std::cout << Colors::CYAN << "Input the size of the problem: ";
      std::cin >> size;
      std::cout << "0. All\n1. Quick Sort\n2. Merge Sort\n3. Binary Search\n4. Towers of Hanoi\n";
      std::cout << "Input the algorithm: ";
      int algorithm_choice;
      std::cin >> algorithm_choice;
      std::cout << Colors::RESET;
      
      Problem problem = GenerateRandomVector(size);
      Solution solution;
      
      if (algorithm_choice != 4) {
        std::cout << Colors::MAGENTA << "\nArray to sort: ";
        PrintVector(std::cout, problem);
      }
      
      if (algorithm_choice == 0 || algorithm_choice == 1) {
        DivideAndConquer* quicksort = new QuickSort();
        double time = 0.0;
        solution = ExecuteAlgorithm(quicksort, problem, time);
        PrintSolution(std::cout, solution, "Quick Sort");
        std::cout << Colors::YELLOW << "Time: " << time << " seconds" << Colors::RESET << std::endl;
      }
      if (algorithm_choice == 0 || algorithm_choice == 2 || algorithm_choice == 3) {
        DivideAndConquer* mergesort = new MergeSort();
        double time = 0.0;
        solution = ExecuteAlgorithm(mergesort, problem, time);
        PrintSolution(std::cout, solution, "Merge Sort");
        std::cout << Colors::YELLOW << "Time: " << time << " seconds" << Colors::RESET << std::endl;
      }
      // Binary search and Towers of Hanoi are commented out in original
    } else {
      std::cout << Colors::RED << "Invalid choice!" << Colors::RESET << "\n";
    }
  } 
  else if (comparingSolversMode) {
    std::string folder_path;
    std::cout << Colors::CYAN << "Enter folder path containing JSON instances: ";
    std::cin >> folder_path;
    std::cout << "Enter algorithm config folder path: ";
    std::string config_folder;
    std::cin >> config_folder;
    std::cout << Colors::RESET;

    std::vector<std::filesystem::path> config_files;
    for (const auto& config_entry : std::filesystem::directory_iterator(config_folder)) {
      if (config_entry.path().extension() == ".json" && config_entry.is_regular_file()) {
        config_files.push_back(config_entry.path());
      }
    }

    if (config_files.empty()) {
      std::cout << Colors::RED << "No algorithm config .json files found in: "
                << config_folder << Colors::RESET << "\n";
      return 1;
    }

    std::sort(config_files.begin(), config_files.end());

    struct CompareRow {
      int employees, days, shifts;
      std::string solver;
      int objective;
      double time_ms;
    };
    std::vector<CompareRow> results;

    std::vector<std::filesystem::path> instance_files;
    for (const auto& entry : std::filesystem::directory_iterator(folder_path)) {
      if (entry.path().extension() == ".json" && entry.is_regular_file()) {
        instance_files.push_back(entry.path());
      }
    }
    std::sort(instance_files.begin(), instance_files.end());

    for (const auto& inst_path : instance_files) {
      EmployeeSchedulingInstance instance;
      try {
        instance.LoadFromJSON(inst_path.string());
        std::cout << Colors::GREEN << "\nProcessing instance: "
                  << "Employees=" << instance.E
                  << ", Days=" << instance.D
                  << ", Shifts=" << instance.T
                  << Colors::RESET << "\n";
        for (const auto& config_path : config_files) {
          EmployeeSchedulingDyV emp_sched = EmployeeSchedulingDyV::FromJSONConfig(instance, config_path.string());
          clock_t start = clock();
          EmployeeSchedulingSolution sol = emp_sched.Solve();
          clock_t end = clock();
          double time_ms = double(end - start) / CLOCKS_PER_SEC * 1000.0;
          int obj = sol.CalculateObjective(instance);
          std::cout << "  Solver: " << config_path.filename()
                    << " | Objective: " << obj
                    << " | Time: " << time_ms << " ms\n";
          results.push_back({instance.E, instance.D, instance.T,
                             config_path.stem().string(), obj, time_ms});
        }
      } catch (const std::exception& e) {
        std::cout << Colors::RED << "Error: " << e.what() << Colors::RESET << "\n";
      }
    }

    std::cout << "\nExport results to CSV file? (y/n): ";
    char export_choice;
    std::cin >> export_choice;
    if (export_choice == 'y' || export_choice == 'Y') {
      std::string out_file;
      std::cout << "Enter output filename: ";
      std::cin >> out_file;
      std::sort(results.begin(), results.end(), [](const CompareRow& a, const CompareRow& b) {
        return a.solver < b.solver;
      });
      std::ofstream csv(out_file);
      if (!csv.is_open()) {
        std::cout << Colors::RED << "Could not open file: " << out_file << Colors::RESET << "\n";
      } else {
        csv << "Employees\tDays\tShifts\tSolver\tObjective\tTime_ms\n";
        for (const auto& row : results) {
          csv << row.employees << "\t" << row.days << "\t" << row.shifts << "\t"
              << row.solver << "\t" << row.objective << "\t" << row.time_ms << "\n";
        }
        csv.close();
        std::cout << Colors::GREEN << "Results exported to " << out_file << Colors::RESET << "\n";
      }
    }
  }
  else {
    // Benchmarking mode (original behavior)
    for (int i = 1; i <= MAX_INSTANCES_MULTIPLICATOR; i++) {
      int instances = 100 * i;
      for (int j = 1; j <= MAX_SIZE_MULTIPLICATOR; j++) {
        double quicksort_time = 0.0, mergesort_time = 0.0, binsearch_time = 0.0, hanoi_time = 0.0;
        // int quicksort_calls = 0, mergesort_calls = 0; //, binsearch_calls = 0, hanoi_calls = 0;
        // int quicksort_depth = 0, mergesort_depth = 0; //, binsearch_depth = 0, hanoi_depth = 0;
        int algorithm_choice = 0;
        int size = 1000 * j;
        int hanoi_size = (size / 1000) + 2;
        if (debugMode) {
          std::cout << Colors::CYAN << "Input the size of the problem: ";
          std::cin >> size;
          std::cout << "0. All\n1. Quick Sort\n2. Merge Sort\n3. Binary Search\n4. Towers of Hanoi\n5. Employee Scheduling\n";
          std::cout << "Input the algorithm: ";
          std::cin >> algorithm_choice;
          std::cout << Colors::RESET;
          hanoi_size = size > 24 ? (size % 22) + 3 : size;
        }
        for (int k = 0; k < instances; k++) {
          Problem problem = GenerateRandomVector(size);
          Solution solution;
          if (debugMode) {
            if (algorithm_choice != 4) {
              std::cout << Colors::MAGENTA << "\nArray to sort: ";
              PrintVector(std::cout, problem);
            }
            // std::cout << Colors::MAGENTA << "\nTowers of Hanoi: " << hanoi_size << " discs from rod 0 to rod 2" << std::endl;
          }
          if (algorithm_choice == 0 || algorithm_choice == 1) {
            DivideAndConquer* quicksort = new QuickSort();
            solution = ExecuteAlgorithm(quicksort, problem, quicksort_time);
            if (debugMode) PrintSolution(std::cout, solution, "Quick Sort");
            // quicksort_calls += quicksort->GetRecursiveCalls();
            // quicksort_depth += quicksort->GetMaxDepth();
          }
          if (algorithm_choice == 0 || algorithm_choice == 2 || algorithm_choice == 3) {
            DivideAndConquer* mergesort = new MergeSort();
            solution = ExecuteAlgorithm(mergesort, problem, mergesort_time);
            if (debugMode) PrintSolution(std::cout, solution, "Merge Sort");
            // mergesort_calls += mergesort->GetRecursiveCalls();
            // mergesort_depth += mergesort->GetMaxDepth();
          }
          // if (algorithm_choice == 0 || algorithm_choice == 3) {
          //   DivideAndConquer* binarysearch = new BinarySearch(solution[std::rand() % size]);
          //   solution = ExecuteAlgorithm(binarysearch, solution, binsearch_time);
          //   if (debugMode) PrintSolution(std::cout, solution, "Binary Search");
          //   // binsearch_calls += binarysearch->GetRecursiveCalls();
          //   // binsearch_depth += binarysearch->GetMaxDepth();
          // }
          // if (algorithm_choice == 0 || algorithm_choice == 4) {
          //   DivideAndConquer* towersofhanoi = new TowersOfHanoi(hanoi_size);
          //   solution = ExecuteAlgorithm(towersofhanoi, {hanoi_size, 0, 2}, hanoi_time);
          //   if (debugMode) PrintSolution(std::cout, solution, "Towers of Hanoi");
          //   // hanoi_calls += towersofhanoi->GetRecursiveCalls();
          //   // hanoi_depth += towersofhanoi->GetMaxDepth();
          // }
          if (algorithm_choice == 5) {
            // Employee Scheduling
            std::string json_file;
            std::string algorithm_config;
            std::cout << "Enter instance JSON file path: ";
            std::cin >> json_file;
            std::cout << "Enter algorithm config JSON file path: ";
            std::cin >> algorithm_config;
            EmployeeSchedulingInstance instance;
            try {
              instance.LoadFromJSON(json_file);
              if (debugMode) instance.Print();
              EmployeeSchedulingDyV emp_sched = EmployeeSchedulingDyV::FromJSONConfig(instance, algorithm_config);
              double time = 0.0;
              clock_t start = clock();
              EmployeeSchedulingSolution sol = emp_sched.Solve();
              clock_t end = clock();
              time = double(end - start) / CLOCKS_PER_SEC;
              std::cout << "Objective value: " << sol.CalculateObjective(instance) << "\n";
              if (debugMode) sol.Print();
              std::cout << "Time: " << time << " seconds\n";
            } catch (const std::exception& e) {
              std::cout << "Error: " << e.what() << "\n";
            }
          }
          if (debugMode) break;
        }
        if (algorithm_choice == 0) {
          PrintTable(std::cout, {quicksort_time, mergesort_time}, size, instances, std::pair<int, int>(i, j), hanoi_size);
        }
        else if (algorithm_choice == 1) {
          std::cout << Colors::YELLOW << "QuickSort total time: " << quicksort_time << " seconds" << Colors::RESET << std::endl; 
        }
        else if (algorithm_choice == 2) {
          std::cout << Colors::YELLOW << "MergeSort total time: " << mergesort_time << " seconds" << Colors::RESET << std::endl;
        }
        else if (algorithm_choice == 3) {
          std::cout << Colors::YELLOW << "BinarySearch total time: " << binsearch_time << " seconds" << Colors::RESET << std::endl;
        }
        else if (algorithm_choice == 4) {
          std::cout << Colors::YELLOW << "TowersOfHanoi total time: " << hanoi_time << " seconds" << Colors::RESET << std::endl;
        }
        else if (algorithm_choice == 5) {
          // Employee scheduling timing would be handled inside the loop
        }
        if (debugMode) return 0;
      }
    }
  }
  return 0;
}