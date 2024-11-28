#include <gtest/gtest.h>
#include "DependencyResolver.hpp"

class DependencyResolverTest : public ::testing::Test {
protected:
    DependencyResolver resolver;
};

TEST_F(DependencyResolverTest, ResolveSinglePackage) {
    auto result = resolver.resolve("org.example:my-artifact:1.0", 1);

    ASSERT_TRUE(result.find("org.example:my-artifact:1.0") != result.end());
    ASSERT_EQ(result["org.example:my-artifact:1.0"].size(), 0); 
}

TEST_F(DependencyResolverTest, ResolveWithDependencies) {
    auto result = resolver.resolve("org.springframework:spring-core:5.3.20", 1);

    ASSERT_TRUE(result.find("org.springframework:spring-core:5.3.20") != result.end());
    ASSERT_GT(result["org.springframework:spring-core:5.3.20"].size(), 0); 
}
