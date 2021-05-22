#include <string>
#include <algorithm>
#include <cassert>

#include <gtest/gtest.h>

// Write a method to replace all spaces in a string with '%20'. You may assume
// that the string has sufficient space at the end to hold the additional
// characters, and that you are given the "true" length of the string.
//
// EXAMPLE
// Input:  "Mr John Smith    ", 13
// Output: "Mr%20John%20Smith"

void replaceSpaces(std::string &str, std::size_t size)
{
    if (size == 0) {
        return;
    }

    constexpr char oldValue = ' ';
    constexpr int oldValueSize = 1;

    constexpr char newValue[] = { '%', '2', '0' };
    constexpr int newValueSize = std::size(newValue);

    assert(str.size() >= size);
    const int oldValuesCount = std::count(str.begin(), std::next(str.begin(), size),
            oldValue);

    std::size_t fromIndex = size;
    assert(str.size() >= fromIndex);

    std::size_t toIndex = fromIndex + oldValuesCount * (newValueSize -
            oldValueSize);
    assert(str.size() >= toIndex);

    std::reverse_iterator from(std::next(str.begin(), fromIndex));
    std::reverse_iterator to(std::next(str.begin(), toIndex));
    for (; from != str.crend(); ++from) {
        if (*from == oldValue) {
            to = std::copy(std::rbegin(newValue), std::rend(newValue), to);
        }
        else {
            *to = *from;
            ++to;
        }
    }
}

TEST(task_1_3, replaceSpaces_StringWithSpaces_AllSpacesReplaced)
{
    std::string str = " Aaaay, macarena       ";
    replaceSpaces(str, 17);
    ASSERT_STREQ(str.c_str(), "%20Aaaay,%20macarena%20");
}

TEST(task_1_3, replaceSpaces_EmptyString_EmptyString)
{
    std::string str;
    replaceSpaces(str, 0);
    ASSERT_STREQ(str.c_str(), "");
}

TEST(task_1_3, replaceSpaces_OneSpace_SpaceReplaced)
{
    std::string str = "   ";
    replaceSpaces(str, 1);
    ASSERT_STREQ(str.c_str(), "%20");
}

TEST(task_1_3, replaceSpaces_TwoSpaces_SpacesReplaced)
{
    std::string str = "      ";
    replaceSpaces(str, 2);
    ASSERT_STREQ(str.c_str(), "%20%20");
}

TEST(task_1_3, replaceSpaces_NoSpaces_TheSameString)
{
    std::string str = "aa";
    replaceSpaces(str, 2);
    ASSERT_STREQ(str.c_str(), "aa");
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
