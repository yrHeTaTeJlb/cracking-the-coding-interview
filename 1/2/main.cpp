#include <string>
#include <limits>
#include <array>
#include <algorithm>

#include <gtest/gtest.h>

// Given two strings, write a method to decide if one is a permutation of the
// other.

bool isPermutation(const std::string &x, const std::string &y)
{
    using namespace std::placeholders;

    if (x.size() != y.size()) {
        return false;
    }

    std::array<int, std::numeric_limits<char>::max()> chars = {};

    for (char c : x) {
        ++chars[c];
    }

    for (char c : y) {
        --chars[c];
        if (chars[c] < 0) {
            return false;
        }
    }

    return true;
}

TEST(task_1_2, isPermutation_Permutation_True)
{
    ASSERT_TRUE(isPermutation("macarena", "acamrena"));
}

TEST(task_1_2, isPermutation_TwoEmptyStrings_True)
{
    ASSERT_TRUE(isPermutation("", ""));
}

TEST(task_1_2, isPermutation_OneEmptyString_False)
{
    ASSERT_FALSE(isPermutation("", "aa"));
}

TEST(task_1_2, isPermutation_DifferentLength_False)
{
    ASSERT_FALSE(isPermutation("aa", "bbaa"));
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
