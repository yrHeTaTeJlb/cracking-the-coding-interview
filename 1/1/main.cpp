#include <string>
#include <limits>
#include <bitset>

#include <gtest/gtest.h>

// Implement an algorithm to determine if a string has all unique characters.
// What if you cannot use additional data structures?

bool hasDuplicates(const std::string &str)
{
    constexpr char charMax = std::numeric_limits<char>::max();

    if (str.size() > charMax) {
        return true;
    }

    std::bitset<charMax> met;

    for (char c : str) {
        if (met.test(c)) {
            return true;
        }

        met.set(c);
    }

    return false;
}

TEST(task_1_1, hasDuplicates_DuplicatesSameCase_True)
{
    ASSERT_TRUE(hasDuplicates("macarena"));
}

TEST(task_1_1, hasDuplicates_EmptyString_False)
{
    ASSERT_FALSE(hasDuplicates(""));
}

TEST(task_1_1, hasDuplicates_OnlyDuplicatesSameCase_True)
{
    ASSERT_TRUE(hasDuplicates("aa"));
}

TEST(task_1_1, hasDuplicates_DuplicatesDifferentCase_False)
{
    ASSERT_FALSE(hasDuplicates("HIi, World"));
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
