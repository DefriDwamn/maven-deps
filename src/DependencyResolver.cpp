#include "DependencyResolver.hpp"
#include <Utils.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <cpr/cpr.h>
#include <iostream>
#include <sstream>

void DependencyResolver::resolveDependenciesRecursive(
    const std::string &packageName, int depth, int maxDepth,
    DependencyGraph &graph) {
  if (depth > maxDepth)
    return;

  if (graph.find(packageName) != graph.end())
    return;

  std::cout << Utils::colorize(Utils::Color::GREEN,
                               "Resolving dependencies for: ", packageName)
            << std::endl;

  auto colon1 = packageName.find(':');
  auto colon2 = packageName.rfind(':');
  if (colon1 == std::string::npos || colon2 == std::string::npos ||
      colon1 == colon2) {
    std::cerr << Utils::colorize(Utils::Color::RED,
                                 "Invalid package format: ", packageName)
              << "\n";
    return;
  }

  std::string groupId = packageName.substr(0, colon1);
  std::string artifactId = packageName.substr(colon1 + 1, colon2 - colon1 - 1);
  std::string version = packageName.substr(colon2 + 1);

  std::string groupPath = groupId;
  std::replace(groupPath.begin(), groupPath.end(), '.', '/');

  std::string url = "https://repo1.maven.org/maven2/" + groupPath + "/" +
                    artifactId + "/" + version + "/" + artifactId + "-" +
                    version + ".pom";

  auto response = cpr::Get(cpr::Url{url});
  if (response.status_code != 200) {
    std::cerr << Utils::colorize(Utils::Color::RED, "Failed to fetch POM for ",
                                 packageName)
              << "\n";
    return;
  }

  std::istringstream xmlData(response.text);
  boost::property_tree::ptree tree;
  boost::property_tree::read_xml(xmlData, tree);

  auto depsNode = tree.get_child_optional("project.dependencies");
  if (!depsNode) {
    graph[packageName] = {};
    return;
  }

  std::vector<std::string> dependencies;
  for (const auto &dep : depsNode.get()) {
    if (dep.first == "dependency") {
      std::string depGroupId = dep.second.get<std::string>("groupId", "");
      std::string depArtifactId = dep.second.get<std::string>("artifactId", "");
      std::string depVersion = dep.second.get<std::string>("version", "");

      if (depVersion.find("${") != std::string::npos) {
        std::cerr << Utils::colorize(Utils::Color::YELLOW,
                                     "Warning: Unresolved version placeholder "
                                     "found in dependency: ")
                  << depGroupId << ":" << depArtifactId << ":" << depVersion
                  << std::endl;
        depVersion = "latest";
      }

      if (!depGroupId.empty() && !depArtifactId.empty() &&
          !depVersion.empty()) {
        dependencies.push_back(depGroupId + ":" + depArtifactId + ":" +
                               depVersion);
      }
    }
  }

  graph[packageName] = dependencies;

  for (const auto &dep : dependencies) {
    resolveDependenciesRecursive(dep, depth + 1, maxDepth, graph);
  }
}

DependencyResolver::DependencyGraph
DependencyResolver::resolve(const std::string &packageName, int maxDepth) {
  DependencyGraph graph;
  resolveDependenciesRecursive(packageName, 0, maxDepth, graph);
  std::cout << Utils::colorize(Utils::Color::DEFAULT,
                               "End of Resolving dependencies.")
            << std::endl;
  return graph;
}