#include "GraphVisualizer.hpp"
#include <gtest/gtest.h>

class GraphVisualizerTest : public ::testing::Test {
protected:
  std::string visualizerPath = "../../for_test/plantuml.jar";
  GraphVisualizer visualizer;

  GraphVisualizerTest() : visualizer(visualizerPath) {}
};

TEST_F(GraphVisualizerTest, FindJavaExecutable) {
  std::string javaPath = visualizer.findJavaExecutable();

  ASSERT_FALSE(javaPath.empty());
  EXPECT_TRUE(javaPath.find("java") != std::string::npos);
}

TEST_F(GraphVisualizerTest, VisualizeSimpleGraph) {
  std::string plantUMLCode = "@startuml\n@enduml";

  ASSERT_NO_THROW(visualizer.visualize(plantUMLCode));
}
