#pragma once
#include <string>

class GraphVisualizer {
public:
  explicit GraphVisualizer(const std::string &visualizerPath);
  void visualize(const std::string &plantUMLCode);
  std::string findJavaExecutable();

private:
  std::string visualizerPath;
};