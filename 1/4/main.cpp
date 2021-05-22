#include <string>
#include <bitset>
#include <cctype>
#include <cstdint>

#include <gtest/gtest.h>

// Given a string, write a function to check if it is a permutation of a
// palindrome. A palindrome is a word or phrase that is the same forwards and
// backwards. A permutation is a rearrangement of letters. The palindrome does
// not need to be limited to just dictionary words.
//
// EXAMPLE
// Input:  "Tact Coa"
// Output: true (permutations: "taco cat". "atco cta". etc.)

bool isPalindromePermutation(const std::string &str)
{
    std::bitset < 'z' - 'a' > isOdd;
    for (char c : str) {
        if (!std::isalpha(c)) {
            continue;
        }

        isOdd[std::tolower(c) - 'a'].flip();
    }

    return isOdd.count() <= 1;
}

TEST(task_1_4, isPalindromePermutation_NotPalindrome_False)
{
    ASSERT_FALSE(isPalindromePermutation("macarena"));
}

TEST(task_1_4, isPalindromePermutation_NotPalindromeDifferentCase_False)
{
    ASSERT_FALSE(isPalindromePermutation("Aaabbb"));
}

TEST(task_1_4, isPalindromePermutation_Palindrome_True)
{
    ASSERT_TRUE(isPalindromePermutation("taco cat"));
}

TEST(task_1_4, isPalindromePermutation_EmptyStrign_True)
{
    ASSERT_TRUE(isPalindromePermutation(""));
}

TEST(task_1_4, isPalindromePermutation_PalindromeDifferentCase_True)
{
    ASSERT_TRUE(isPalindromePermutation("Aa"));
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
