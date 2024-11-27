#include "DependencyResolver.hpp"
#include "GraphVisualizer.hpp"
#include "PlantUMLGenerator.hpp"
#include "Utils.hpp"
#include <boost/program_options.hpp>
#include <iostream>
#include <string>

namespace po = boost::program_options;

int main(int argc, char *argv[]) {
  try {
    std::string visualizerPath, packageName;
    int maxDepth;

    po::options_description desc("Allowed options");
    desc.add_options()("help,h", "Show help message")(
        "visualizer,v", po::value<std::string>(&visualizerPath)->required(),
        "Path to PlantUML visualizer")(
        "package,p", po::value<std::string>(&packageName)->required(),
        "Package name in format: groupId:artifactId:version")(
        "depth,d", po::value<int>(&maxDepth)->default_value(10000),
        "Maximum dependency depth");
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    if (vm.count("help")) {
      std::cout << desc << "\n";
      return 0;
    }
    po::notify(vm);

    DependencyResolver resolver;
    PlantUMLGenerator generator;
    GraphVisualizer visualizer(visualizerPath);

    auto dependencies = resolver.resolve(packageName, maxDepth);
    std::string plantUMLCode = generator.generate(dependencies);
    visualizer.visualize(plantUMLCode);

  } catch (const std::exception &e) {
    std::cerr << Utils::colorize(Utils::Color::RED, "Error: ", e.what())
              << "\n";
    return 1;
  }

  return 0;
}
