#pragma once
#include <string>
#include <unordered_map>
#include <vector>

class PlantUMLGenerator {
public:
  using DependencyGraph =
      std::unordered_map<std::string, std::vector<std::string>>;

  std::string generate(const DependencyGraph &graph);
};