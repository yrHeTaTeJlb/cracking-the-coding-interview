#include <iostream>
#include <string>
#include <cstdint>
#include <algorithm>
#include <cassert>

#include <gtest/gtest.h>

// There are three types of edits that can be performed on strings: insert a
// character, remove a character, or replace a character. Given two strings,
// write a function to check if they are one edit (or zero edits) away.
//
// EXAMPLE
// Input:  "pale", "ple"
// Output: true
//
// Input:  "pales", "pale"
// Output: true
//
// Input:  "pale", "bale"
// Output: true
//
// Input:  "pale", "bake"
// Output: false

bool isShorter(const std::string &x, const std::string &y)
{
    return x.size() < y.size();
}

bool isOneChangeAway(const std::string &x, const std::string &y)
{
    auto[shortStr, longStr] = std::minmax(x, y, isShorter);

    if (longStr.size() - shortStr.size() > 1) {
        return false;
    }

    std::string::const_iterator mismatchShort;
    std::string::const_iterator mismatchLong;

    std::tie(mismatchShort, mismatchLong) = std::mismatch(shortStr.begin(),
            shortStr.end(), longStr.begin());

    if (mismatchShort == shortStr.end()) {
        return true;
    }

    ++mismatchLong;
    if (longStr.size() == shortStr.size()) {
        ++mismatchShort;
    }

    return std::mismatch(mismatchShort, shortStr.end(),
            mismatchLong) == std::make_pair(shortStr.end(), longStr.end());
}

TEST(task_1_5, isOneChangeAway_EqualStrings_True)
{
    ASSERT_TRUE(isOneChangeAway("macarena", "macarena"));
}

TEST(task_1_5, isOneChangeAway_EmptyStrings_True)
{
    ASSERT_TRUE(isOneChangeAway("", ""));
}

TEST(task_1_5, isOneChangeAway_OneSetAway_True)
{
    ASSERT_TRUE(isOneChangeAway("macarena", "maaarena"));
}

TEST(task_1_5, isOneChangeAway_OneInsertAway_True)
{
    ASSERT_TRUE(isOneChangeAway("macarena", "macaren"));
}

TEST(task_1_5, isOneChangeAway_OneEraseAway_True)
{
    ASSERT_TRUE(isOneChangeAway("macaren", "macarena"));
}

TEST(task_1_5, isOneChangeAway_TooDifferentSize_False)
{
    ASSERT_FALSE(isOneChangeAway("macaren", "macar"));
}

TEST(task_1_5, isOneChangeAway_TooDifferentContent_False)
{
    ASSERT_FALSE(isOneChangeAway("macarena", "aaaarena"));
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
