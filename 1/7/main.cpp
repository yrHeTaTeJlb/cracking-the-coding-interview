#include <iostream>
#include <string>
#include <cstdint>
#include <algorithm>

#include <gtest/gtest.h>

// Given an image represented by an NxN matrix, where each pixel in the image is
// 4 bytes, write a method to rotate the image by 90 degrees. Can you do this in
// place?

template <class T>
using SquareMatrix = std::vector<std::vector<T>>;

void rotate(std::uint32_t &a, std::uint32_t &b, std::uint32_t &c,
    std::uint32_t &d)
{
    std::swap(a, b);
    std::swap(a, c);
    std::swap(a, d);
}

void rotate(SquareMatrix<std::uint32_t> &matrix, std::size_t layer)
{
    assert(matrix.size() > layer * 2);

    const std::size_t layerSize = matrix.size() - layer * 2;
    const std::size_t sideSize = layerSize - 1;
    const std::size_t first = layer;
    const std::size_t last = layer + sideSize;

    for (std::size_t i = 0; i < sideSize; ++i) {
        std::uint32_t &top = matrix[first][first + i];
        std::uint32_t &right = matrix[first + i][last];
        std::uint32_t &bottom = matrix[last][last - i];
        std::uint32_t &left = matrix[last - i][first];

        rotate(top, right, bottom, left);
    }
}

void rotate(SquareMatrix<std::uint32_t> &matrix)
{
    const std::size_t layerCount = matrix.size() / 2;

    for (std::size_t layer = 0; layer < layerCount; ++layer) {
        rotate(matrix, layer);
    }
}

TEST(task_1_7, rotate_EmptyMatrix_EmptyMatrix)
{
    SquareMatrix<std::uint32_t> matrix({});
    rotate(matrix);

    SquareMatrix<std::uint32_t> expected({});

    ASSERT_EQ(matrix, expected);
}

TEST(task_1_7, rotate_MatrixN1_SameMatrix)
{
    SquareMatrix<std::uint32_t> matrix({
        { 42 }
    });
    rotate(matrix);

    SquareMatrix<std::uint32_t> expected({
        { 42 }
    });

    ASSERT_EQ(matrix, expected);
}

TEST(task_1_7, rotate_MatrixN2_RotatedMatrix)
{
    SquareMatrix<std::uint32_t> matrix({
        { 42, 13 },
        { 70, 61 },
    });
    rotate(matrix);

    SquareMatrix<std::uint32_t> expected({
        { 70, 42 },
        { 61, 13 },
    });

    ASSERT_EQ(matrix, expected);
}

TEST(task_1_7, rotate_MatrixN3_RotatedMatrix)
{
    SquareMatrix<std::uint32_t> matrix({
        { 42, 13, 43 },
        { 70, 61, 65 },
        { 50, 51, 55 },
    });
    rotate(matrix);

    SquareMatrix<std::uint32_t> expected({
        { 50, 70, 42 },
        { 51, 61, 13 },
        { 55, 65, 43 },
    });

    ASSERT_EQ(matrix, expected);
}


TEST(task_1_7, rotate_MatrixN4_RotatedMatrix)
{
    SquareMatrix<std::uint32_t> matrix({
        { 42, 13, 43, 80 },
        { 70, 61, 65, 84 },
        { 50, 51, 55, 85 },
        { 22, 21, 25, 28 },
    });
    rotate(matrix);

    SquareMatrix<std::uint32_t> expected({
        { 22, 50, 70, 42 },
        { 21, 51, 61, 13 },
        { 25, 55, 65, 43 },
        { 28, 85, 84, 80 },
    });

    ASSERT_EQ(matrix, expected);
}

TEST(task_1_7, rotate_MatrixN5_RotatedMatrix)
{
    SquareMatrix<std::uint32_t> matrix({
        { 92, 93, 94, 90, 12 },
        { 42, 13, 43, 80, 13 },
        { 70, 61, 65, 84, 14 },
        { 50, 51, 55, 85, 15 },
        { 22, 21, 25, 28, 17 },
    });
    rotate(matrix);

    SquareMatrix<std::uint32_t> expected({
        { 22, 50, 70, 42, 92 },
        { 21, 51, 61, 13, 93 },
        { 25, 55, 65, 43, 94 },
        { 28, 85, 84, 80, 90 },
        { 17, 15, 14, 13, 12 },
    });

    ASSERT_EQ(matrix, expected);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
