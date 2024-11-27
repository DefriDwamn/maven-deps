#pragma once
#include <string>

class GraphVisualizer {
public:
  explicit GraphVisualizer(const std::string &visualizerPath);
  void visualize(const std::string &plantUMLCode);

private:
  std::string visualizerPath;
  std::string findJavaExecutable();
};