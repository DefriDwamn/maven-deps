#include "PlantUMLGenerator.hpp"
#include <sstream>

std::string PlantUMLGenerator::generate(const DependencyGraph &graph) {
  std::ostringstream oss;
  oss << "@startuml\n";

  for (const auto &node : graph) {
    const auto &sourceName = node.first;
    for (const auto &targetName : node.second) {
      oss << sourceName << " --> " << targetName << "\n";
    }
  }

  oss << "@enduml\n";
  return oss.str();
}