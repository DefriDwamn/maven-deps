#include "DependencyResolver.hpp"
#include <gtest/gtest.h>

class DependencyResolverTest : public ::testing::Test {
protected:
  DependencyResolver resolver;
};

TEST_F(DependencyResolverTest, ResolveSinglePackage) {
  std::string package = "al.aldi:sprova4j:0.2.1";
  auto result = resolver.resolve(package, 1);

  ASSERT_TRUE(result.find(package) != result.end());
  ASSERT_EQ(result[package].size(), 11);
}

TEST_F(DependencyResolverTest, ResolveWithDependencies) {
  auto result = resolver.resolve("org.springframework:spring-core:5.3.20", 1);

  ASSERT_TRUE(result.find("org.springframework:spring-core:5.3.20") !=
              result.end());
  ASSERT_GT(result["org.springframework:spring-core:5.3.20"].size(), 0);
}
