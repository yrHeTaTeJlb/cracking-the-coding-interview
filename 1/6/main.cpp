#include <iostream>
#include <string>
#include <cstdint>
#include <algorithm>

#include <gtest/gtest.h>

// Implement a method to perform basic string compression using the counts of
// repeated characters. If the "compressed" string would not become smaller than
// the original string, your method should return the original string. You can
// assume the string has only uppercase and lowercase letters (a - z).
//
// EXAMPLE
// Input:  "aabcccccaaa"
// Output: "a2b1c5a3"

std::string compress(const std::string &str)
{
    using Iterator = std::string::const_iterator;

    if (str.size() < 2) {
        return str;
    }

    std::string compressed;
    for (Iterator current = str.begin(); current != str.end();) {
        Iterator next = std::find_if_not(current, str.end(),
        [&current](char c) {
            return *current == c;
        });

        std::ptrdiff_t count = std::distance(current, next);

        compressed.push_back(*current);
        compressed += std::to_string(count);

        if (compressed.size() >= str.size()) {
            return str;
        }

        current = next;
    }

    return compressed;
}

TEST(task_1_6, compress_IncompressibleString_SameString)
{
    ASSERT_STREQ(compress("macarena").c_str(), "macarena");
}

TEST(task_1_6, compress_CompressibleString_CompressedString)
{
    ASSERT_STREQ(compress("aabcccccddd").c_str(), "a2b1c5d3");
}

TEST(task_1_6, compress_Emptytring_EmptyString)
{
    ASSERT_STREQ(compress("").c_str(), "");
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
