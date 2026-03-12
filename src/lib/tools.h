/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos
 * 
 * @brief Auxiliary file for various function declarations.
 * @since 25th of February, 2025
 * @authors Martín José Marrero Quintans, Fabián González Lence
 * @see { @link https://campusingenieriaytecnologia2425.ull.es/mod/assign/view.php?id=24915 }
 * @see { @link https://github.com/alu0101549491/DAA-P03.git }
 */

#ifndef TOOLS_H
#define TOOLS_H

#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>
#include <ctime>
#include <iomanip>

typedef std::vector<int> Problem;
typedef std::vector<int> Solution;

#define ERROREXIT(message) std::cout << Colors::RED << "./RAM: " << message << "\n" << Colors::RESET; return false

namespace Colors {
  // ANSI 8 colors supported by most terminals
  const std::string BLACK   = "\033[30m";
  const std::string RED     = "\033[91m";
  const std::string GREEN   = "\033[92m";
  const std::string YELLOW  = "\033[93m";
  const std::string BLUE    = "\033[94m";
  const std::string MAGENTA = "\033[95m";
  const std::string CYAN    = "\033[96m";
  const std::string WHITE   = "\033[97m";
  
  // Bright
  const std::string BRIGHT_BLACK   = "\033[90m";
  const std::string BRIGHT_RED     = "\033[91m";
  const std::string BRIGHT_GREEN   = "\033[92m";
  const std::string BRIGHT_YELLOW  = "\033[93m";
  const std::string BRIGHT_BLUE    = "\033[94m";
  const std::string BRIGHT_MAGENTA = "\033[95m";
  const std::string BRIGHT_CYAN    = "\033[96m";
  const std::string BRIGHT_WHITE   = "\033[97m";

  // Extended
  const std::string ORANGE = "\033[38;5;214m";
  const std::string GRAY   = "\033[38;5;240m";
  const std::string LIGHT_GRAY = "\033[38;5;250m";

  // Reset and Get function
  const std::string RESET = "\033[0m";
  const std::string Get(std::ostream& out, const std::string& color);
}

const int MAX_SIZE_MULTIPLICATOR = 10;
const int MAX_INSTANCES_MULTIPLICATOR = 3;

Problem GenerateRandomVector(int size);
const std::string Colors::Get(std::ostream& out, const std::string& color);
void PrintVector(std::ostream& out, std::vector<int> vector);
void PrintSolution(std::ostream& out, Solution solution, std::string algorithm);
void PrintTable(std::ostream& out, std::vector<double> times, int size, int instances, std::pair<int, int> iteration, int discs);

#endif // TOOLS_H