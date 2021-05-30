#include <iostream>
#include <string>
#include <cstdint>
#include <algorithm>

#include <gtest/gtest.h>

// Assume you have a method isSubstring which checks if one word is a substring
// of another. Given two strings, s1 and s2, write code to check if s2 is a
// rotation of s1 using only one call to isSubstring
//
// EXAMPLE
// Input:  "waterbottle", "erbottlewat"
// Output: true

bool isSubstring(const std::string &x, const std::string &y)
{
    return y.find(x) != std::string::npos;
}

bool isRotation(const std::string &x, const std::string &y)
{
    if (x.size() != y.size()) {
        return false;
    }

    return isSubstring(y, x + x);
}

TEST(task_1_9, isRotation_EmptyStringAndEmptyString_True)
{
    ASSERT_TRUE(isRotation("", ""));
}

TEST(task_1_9, isRotation_EmptyStringAndNotEmptyString_False)
{
    ASSERT_FALSE(isRotation("", "a"));
}

TEST(task_1_9, isRotation_RotatedString_True)
{
    ASSERT_TRUE(isRotation("waterbottle", "erbottlewat"));
}

TEST(task_1_9, isRotation_NotRotatedString_False)
{
    ASSERT_FALSE(isRotation("waterbotrtle", "ebottlewat"));
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
