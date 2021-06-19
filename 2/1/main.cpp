#include <initializer_list>
#include <memory>
#include <tuple>
#include <unordered_set>

#include <gtest/gtest.h>

// Write code to remove duplicates from an unsorted linked list.
// FOLLOW UP
// How would you solve this problem if a temporary buffer is not allowed?

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

namespace HashTable {

void removeDuplicates(List &list)
{
    if (list.isEmpty()) {
        return;
    }

    Node *prev = list.begin.get();
    Node *curr = prev->next.get();

    std::unordered_set<int> met = { prev->data };

    while (curr) {
        bool inserted = false;
        std::tie(std::ignore, inserted) = met.insert(curr->data);

        if (!inserted) {
            prev->next = std::move(curr->next);
            curr = prev;
        }

        prev = curr;
        curr = curr->next.get();
    }
}

}

namespace NoExtraMemory {

void removeDuplicatesOfFirstNode(Node *begin)
{
    if (!begin) {
        return;
    }

    Node *prev = begin;
    Node *curr = begin->next.get();

    while (curr) {
        if (curr->data == begin->data) {
            prev->next = std::move(curr->next);
            curr = prev;
        }

        prev = curr;
        curr = curr->next.get();
    }
}

void removeDuplicates(List &list)
{
    if (list.isEmpty()) {
        return;
    }

    for (Node *pos = list.begin.get(); pos; pos = pos->next.get()) {
        removeDuplicatesOfFirstNode(pos);
    }
}

}

enum class Implementation {
    HashTable,
    NoExtraMemory,
};

struct task_2_1 : public testing::TestWithParam<Implementation> {
    std::function<void(List &)> removeDuplicates;
    task_2_1()
    {
        switch (GetParam()) {
        case Implementation::HashTable:
            removeDuplicates = HashTable::removeDuplicates;
            break;
        case Implementation::NoExtraMemory:
            removeDuplicates = NoExtraMemory::removeDuplicates;
            break;
        }
    }
};

TEST_P(task_2_1, removeDuplicates_EmptyList_EmptyList)
{
    List list = {};
    removeDuplicates(list);

    List expected = {};

    ASSERT_EQ(list, expected);
}

TEST_P(task_2_1, removeDuplicates_NonEmptyList_NoDuplicates)
{
    List list = { 1, 2, 3, 4, 1, 4, 4 };
    removeDuplicates(list);

    List expected = { 1, 2, 3, 4 };

    ASSERT_EQ(list, expected);
}

INSTANTIATE_TEST_SUITE_P(Test, task_2_1,
    testing::Values(Implementation::HashTable, Implementation::NoExtraMemory));

int main(int argc, char **argv)
{

    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
