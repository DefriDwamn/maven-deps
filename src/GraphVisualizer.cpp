#include "GraphVisualizer.hpp"
#include "Utils.hpp"
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/process.hpp>
#include <boost/process/v1/environment.hpp>
#include <fstream>
#include <iostream>
#include <stdexcept>

namespace bp = boost::process;

GraphVisualizer::GraphVisualizer(const std::string &visualizerPath)
    : visualizerPath(visualizerPath) {}

void GraphVisualizer::visualize(const std::string &plantUMLCode) {
  const std::string plantUMLFile = "graph.puml";
  const std::string outputImage = "graph.png";

  std::ofstream file(plantUMLFile);
  if (!file.is_open()) {
    throw std::runtime_error("Failed to write PlantUML code to file.");
  }
  file << plantUMLCode;
  file.close();

  std::string javaPath = findJavaExecutable();

  bp::child plantUMLProcess(javaPath, "-jar", visualizerPath, "-tpng",
                            plantUMLFile);
  plantUMLProcess.wait();

  if (plantUMLProcess.exit_code() != 0) {
    throw std::runtime_error("Failed to execute PlantUML.");
  }

  std::cout << Utils::colorize(Utils::Color::GREEN, "Graph png file: ",
                               boost::filesystem::absolute(outputImage))
            << std::endl;
}

std::string GraphVisualizer::findJavaExecutable() {
#ifdef _WIN32
  bp::ipstream javaPathStream;
  bp::child findJavaProcess("where java", bp::std_out > javaPathStream);

  findJavaProcess.wait();
  if (findJavaProcess.exit_code() != 0) {
    throw std::runtime_error("Failed to locate Java executable on Windows.");
  }

  std::string line;
  while (std::getline(javaPathStream, line)) {
    if (line.find(".exe") != std::string::npos) {
      return line;
    }
  }
  throw std::runtime_error("Java executable not found in PATH on Windows.");

#else
  bp::ipstream javaPathStream;
  bp::child findJavaProcess("whereis java", bp::std_out > javaPathStream);

  findJavaProcess.wait();
  if (findJavaProcess.exit_code() != 0) {
    throw std::runtime_error("Failed to locate Java executable on Linux.");
  }

  std::string line;
  while (std::getline(javaPathStream, line)) {
    size_t colonPos = line.find(':');
    if (colonPos != std::string::npos) {
      std::istringstream pathsStream(line.substr(colonPos + 1));
      std::string path;
      while (pathsStream >> path) {
        if (path.find("/java") != std::string::npos) {
          return path;
        }
      }
    }
  }
  throw std::runtime_error("Java executable not found in PATH on Linux.");
#endif
}