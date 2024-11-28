#pragma once
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

class PlantUMLGenerator {
public:
  using DependencyGraph =
      std::unordered_map<std::string, std::vector<std::string>>;

  void makePackageRecord(std::ostringstream &oss, std::set<std::string> &set,
                         const std::basic_string<char> &package);
  std::string generate(const DependencyGraph &graph);
  
  static const std::string pumlCode;
  std::string mainPackage;
};