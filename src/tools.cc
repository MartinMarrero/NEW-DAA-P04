/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos
 * 
 * @brief Auxiliary file for various function implementations
 * @since 25th of February, 2025
 * @authors Martín José Marrero Quintans, Fabián González Lence
 * @see { @link https://campusingenieriaytecnologia2425.ull.es/mod/assign/view.php?id=24915 }
 * @see { @link https://github.com/alu0101549491/DAA-P03.git }
 */

#include "lib/tools.h"

/**
 * @brief Generates a random vector of integers.
 * @param[in] size: Size of the vector.
 * @return Random vector.
 */
Problem GenerateRandomVector(int size) {
  Problem problem;
  for (int i = 0; i < size; i++) {
    problem.push_back(rand() % 1000000);
  }
  return problem;
}

/**
 * @brief Returns the color code for the specified color.
 * @param[in] out: Output stream.
 * @param[in] color: Color to be returned.
 * @return Color code.
 */
const std::string Colors::Get(std::ostream& out, const std::string& color) {
  if (&out == &std::cout) {
    return color;
  }
  return "";
}

/**
 * @brief Prints the elements of a vector.
 * @param[in] out: Output stream.
 * @param[in] vector: Vector to be printed.
 */
void PrintVector(std::ostream& out, std::vector<int> vector) {
  for (unsigned i = 0; i < vector.size(); i++) {
    out << vector[i] << " ";
  }
  out << Colors::RESET << std::endl;
}

/**
 * @brief Function that prints the solution of a problem.
 * @param[in] out: Output stream.
 * @param[in] solution: Solution to be printed.
 * @param[in] algorithm: Algorithm used to solve the problem.
 */
void PrintSolution(std::ostream& out, Solution solution, std::string algorithm) {
  out << Colors::Get(out, Colors::GREEN) << algorithm << " solution: ";
  if (algorithm.find("Sort") != std::string::npos) {
    out << "Sorted array: ";
    PrintVector(out, solution);
  } else if (algorithm.find("Search") != std::string::npos) {
    out << (solution[0] == 1 ? "Found" : "Not found") << Colors::RESET << std::endl;
  } else if (algorithm.find("Hanoi") != std::string::npos) {
    out << "Moves: " << solution[0] << Colors::RESET << std::endl;
  } else {
    PrintVector(out, solution);
  }
}

/**
 * @brief Function that prints the time taken by an algorithm to solve a problem.
 * @param[in] out: Output stream.
 * @param[in] time: Time taken by the algorithm.
 * @param[in] algorithm: Algorithm used to solve the problem.
 */
void PrintTable(std::ostream& out, std::vector<double> times, int size, int instances, std::pair<int, int> iteration, int discs) {
  std::ostringstream quicktime_s, mergetime_s, size_s, instances_s;

  instances_s << std::setw(11) << Colors::Get(out, Colors::RED) << instances << Colors::RESET;
  size_s << Colors::Get(out, Colors::ORANGE) << std::setw(9) << size << Colors::RESET;
  quicktime_s << std::setw(6) << std::fixed << std::setprecision(6) << Colors::Get(out, Colors::GREEN) << times[0] << Colors::RESET;
  mergetime_s << std::setw(6) << std::fixed << std::setprecision(6) << Colors::Get(out, Colors::CYAN) << times[1] << Colors::RESET;

  if (iteration.first == 1 && iteration.second == 1) {
    out << "╔═══════════╦═══════════╦═══════════╦═══════════╗" << std::endl;
    out << "║ Instances ║     N     ║ QuickSort ║ MergeSort ║" << std::endl;
    out << "╠═══════════╬═══════════╬═══════════╬═══════════╣" << std::endl;
  }
  out << "║ " << instances_s.str() << " ║ " << size_s.str() << " ║ " << quicktime_s.str(); 
  out << " ║ " << mergetime_s.str() << " ║" << std::endl;
  if (iteration.first == MAX_INSTANCES_MULTIPLICATOR && iteration.second == MAX_SIZE_MULTIPLICATOR) {
    out << "╚═══════════╩═══════════╩═══════════╩═══════════╝" << std::endl;
  }
}
