#pragma once
#include <string>
#include <unordered_map>
#include <vector>

class DependencyResolver {
public:
  using DependencyGraph =
      std::unordered_map<std::string, std::vector<std::string>>;

  DependencyGraph resolve(const std::string &packageName, int maxDepth);

private:
  void resolveDependenciesRecursive(const std::string &packageName, int depth,
                                    int maxDepth, DependencyGraph &graph);
};