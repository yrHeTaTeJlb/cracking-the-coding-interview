#include <initializer_list>
#include <memory>
#include <tuple>

#include <gtest/gtest.h>

// Implement an algorithm to find the kth to last element of a singly linked
// list

struct Node {
    int data = 0;
    std::unique_ptr<Node> next;

    Node(int data, std::unique_ptr<Node> next):
        data(data),
        next(std::move(next))
    {}
};

struct List {
    std::unique_ptr<Node> begin;

    List(const std::initializer_list<int> &values)
    {
        for (auto it = std::rbegin(values); it != std::rend(values); ++it) {
            begin = std::make_unique<Node>(*it, std::move(begin));
        }
    }

    bool isEmpty() const
    {
        return !begin;
    }

    bool operator==(const List &other) const
    {
        Node *pos = begin.get();
        Node *otherPos = other.begin.get();

        while (pos && otherPos) {
            if (pos->data != otherPos->data) {
                return false;
            }

            pos = pos->next.get();
            otherPos = otherPos->next.get();
        }

        return !pos && !otherPos;
    }
};

std::ostream &operator<<(std::ostream &os, const List &list)
{
    for (Node *pos = list.begin.get(); pos; pos = pos->next.get()) {
        os << pos->data << ",";
    }

    return os;
}

int size(const List &list)
{
    int result = 0;
    for (Node *pos = list.begin.get(); pos; pos = pos->next.get()) {
        ++result;
    }

    return result;
}

namespace Size {

Node *findLastNthElenemt(const List &list, int n)
{
    const int s = size(list);

    if (n >= s) {
        return nullptr;
    }

    Node *pos = list.begin.get();
    for (int i = 0; i < s - n - 1; ++i) {
        pos = pos->next.get();
    }

    return pos;
}

}

namespace TwoPointers {

Node *findLastNthElenemt(const List &list, int n)
{
    Node *ahead = list.begin.get();
    for (int i = 0; i <= n; ++i) {
        if (!ahead) {
            return nullptr;
        }

        ahead = ahead->next.get();
    }

    Node *behind = list.begin.get();

    while (ahead) {
        ahead = ahead->next.get();
        behind = behind->next.get();
    }

    return behind;
}

}

namespace Recursive {

std::tuple<Node *, int> findLastNthElenemtHelper(Node *prev, int n)
{
    if (!prev->next) {
        return { prev, 0 };
    }

    auto [node, k] = findLastNthElenemtHelper(prev->next.get(), n);

    if (k != n) {
        return { prev, ++k };
    }

    return { node, n };
}

Node *findLastNthElenemt(const List &list, int n)
{
    if (list.isEmpty()) {
        return nullptr;
    }

    auto[node, k] = findLastNthElenemtHelper(list.begin.get(), n);

    if (k != n) {
        return nullptr;
    }

    return node;
}

}

enum class Implementation {
    Size,
    TwoPointers,
    Recursive,
};

struct task_2_2 : public testing::TestWithParam<Implementation> {
    std::function<Node*(const List &, int)> findLastNthElenemt;
    task_2_2()
    {
        switch (GetParam()) {
        case Implementation::Size:
            findLastNthElenemt = Size::findLastNthElenemt;
            break;
        case Implementation::TwoPointers:
            findLastNthElenemt = TwoPointers::findLastNthElenemt;
            break;
        case Implementation::Recursive:
            findLastNthElenemt = Recursive::findLastNthElenemt;
            break;
        }
    }
};

TEST_P(task_2_2, findLastNthElenemt_nLessThanSize_nthToLastNode)
{
    List list = { 1, 2, 3, 4, 5, 6 };
    Node *node = findLastNthElenemt(list, 3);

    ASSERT_NE(node, nullptr);
    ASSERT_EQ(node->data, 3);
}

TEST_P(task_2_2, findLastNthElenemt_nBiggerThanSize_nullptr)
{
    List list = { 1, 2, 3, 4, 5, 6 };
    Node *node = findLastNthElenemt(list, 99);

    ASSERT_EQ(node, nullptr);
}

TEST_P(task_2_2, findLastNthElenemt_nEqualsToSize_nullptr)
{
    List list = { 1, 2, 3, 4, 5, 6 };
    Node *node = findLastNthElenemt(list, 6);

    ASSERT_EQ(node, nullptr);
}

TEST_P(task_2_2, findLastNthElenemt_nIsZero_LastNode)
{
    List list = { 1, 2, 3, 4, 5, 6 };
    Node *node = findLastNthElenemt(list, 0);

    ASSERT_NE(node, nullptr);
    ASSERT_EQ(node->data, 6);
}

TEST_P(task_2_2, findLastNthElenemt_emptyList_nullptr)
{
    List list = {};
    Node *node = findLastNthElenemt(list, 0);

    ASSERT_EQ(node, nullptr);
}

INSTANTIATE_TEST_SUITE_P(Test, task_2_2,
    testing::Values(Implementation::Size, Implementation::TwoPointers,
        Implementation::Recursive));

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
