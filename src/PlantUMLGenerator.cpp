#include "PlantUMLGenerator.hpp"
#include "Utils.hpp"
#include <iostream>
#include <set>
#include <sstream>

const std::string PlantUMLGenerator::pumlCode =
    "skinparam nodeSep 50\n"
    "skinparam rankSep 30\n"
    "skinparam ArrowThickness 2\n"
    "skinparam DefaultFontSize 14\n"
    "skinparam DefaultFontColor Black\n"
    "<style>\n"
    ".main {\n"
    "    BackgroundColor LightGreen\n"
    "}\n"
    "</style>\n"
    "hide stereotype\n";

std::string PlantUMLGenerator::generate(const DependencyGraph &graph) {
  std::ostringstream oss;
  oss << "@startuml\n" << pumlCode;

  std::set<std::string> unique;
  for (const auto &[key, values] : graph) {
    makePackageRecord(oss, unique, key);
    for (const auto &value : values) {
      makePackageRecord(oss, unique, value);
    }
  }

  for (const auto &[key, values] : graph) {
    if (values.empty())
      continue;
    auto keyParts = Utils::split(key, ':');
    std::string keyName = keyParts[1] + ":" + keyParts[2];
    for (const auto &value : values) {
      auto valParts = Utils::split(value, ':');
      std::string valName = valParts[1] + ":" + valParts[2];
      oss << "[" << keyName << "] --> [" << valName << "]\n";
    }
  }

  oss << "@enduml\n";
  return oss.str();
}

void PlantUMLGenerator::makePackageRecord(
    std::ostringstream &oss, std::set<std::string> &set,
    const std::basic_string<char> &package) {
  auto parts = Utils::split(package, ':');
  std::string base = parts[0];
  std::string_view component = parts[1];
  std::string_view version = parts[2];

  if (!set.contains(package)) {
    auto packParts = Utils::split(base, '.');
    int tabCount = 0;

    for (const auto &part : packParts) {
      oss << std::string(tabCount++, '\t') << "package " << part << " {\n";
    }
    oss << std::string(--tabCount, '\t') << "[" << component << ":" << version
        << "]" << (package == mainPackage ? " <<main>>\n" : "\n");

    while (tabCount != -1)
      oss << std::string(tabCount--, '\t') << "}\n";

    set.insert(package);
  }
}