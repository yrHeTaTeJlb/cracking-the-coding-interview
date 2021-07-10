#include <initializer_list>
#include <memory>
#include <tuple>

#include <gtest/gtest.h>

// Implement an algorithm to delete a node in the middle (i.e., any node but the
// first and last node, not necessarily the exact middle) of a singly linked
// list, given only access to that node.
//
// EXAMPLE
// Input: the node c from the linked list a - >b- >c - >d - >e- >f
// Result: nothing is returned, but the new linked list looks like
//     a - >b- >d - >e- >f

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

void erase(Node &node)
{
    node.data = node.next->data;
    node.next = std::move(node.next->next);
}

TEST(task_2_2, erase_middleNode_nodeErased)
{
    List list = { 1, 2, 3, 4, 5, 6 };
    erase(*list.begin->next);

    const List expected = { 1, 3, 4, 5, 6 };
    ASSERT_EQ(list, expected);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
