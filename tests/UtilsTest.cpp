#include <gtest/gtest.h>
#include "Utils.hpp"

class UtilsTest : public ::testing::Test {
protected:
    void SetUp() override {
        //
    }
};

TEST_F(UtilsTest, SplitSimpleString) {
    std::string input = "org.example:artifact:1.0";
    auto result = Utils::split(input, ':');

    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], "org.example");
    EXPECT_EQ(result[1], "artifact");
    EXPECT_EQ(result[2], "1.0");
}

TEST_F(UtilsTest, ColorizeText) {
    std::string coloredText = Utils::colorize(Utils::Color::RED, "Error: ", "Something went wrong!");
    EXPECT_TRUE(coloredText.find("Error:") != std::string::npos);
    EXPECT_TRUE(coloredText.find("Something went wrong!") != std::string::npos);
}
