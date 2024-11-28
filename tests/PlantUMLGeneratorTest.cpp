#include "PlantUMLGenerator.hpp"
#include <gtest/gtest.h>
#include <string>
#include <unordered_map>
#include <vector>

using DependencyGraph =
    std::unordered_map<std::string, std::vector<std::string>>;

class PlantUMLGeneratorTest : public ::testing::Test {
protected:
  PlantUMLGenerator generator;
};

TEST_F(PlantUMLGeneratorTest, GenerateEmptyGraph) {
  DependencyGraph graph;

  auto uml = generator.generate(graph);
  EXPECT_TRUE(uml.find("@startuml") != std::string::npos);
  EXPECT_TRUE(uml.find("@enduml") != std::string::npos);
  EXPECT_TRUE(uml.find("package") == std::string::npos);
}

TEST_F(PlantUMLGeneratorTest, GenerateSimpleGraph) {
  DependencyGraph graph = {
      {"org.example:artifact:1.0", {"org.example:dependency:1.0"}}};

  auto uml = generator.generate(graph);
  EXPECT_TRUE(uml.find("[artifact:1.0] --> [dependency:1.0]") !=
              std::string::npos);
}
