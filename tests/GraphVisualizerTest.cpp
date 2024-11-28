#include <gtest/gtest.h>
#include "GraphVisualizer.hpp"

class GraphVisualizerTest : public ::testing::Test {
protected:
    std::string visualizerPath = "plantuml.jar";
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
