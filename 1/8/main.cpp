#include <iostream>
#include <string>
#include <cstdint>
#include <algorithm>

#include <gtest/gtest.h>

// Write an algorithm such that if an element in an MxN matrix is 0, its entire
// row and column are set to O.

template <class T>
using Row = std::vector<T>;

template <class T>
using Matrix = std::vector<Row<T>>;

void zeroRow(Matrix<std::uint32_t> &matrix, std::size_t row)
{
    std::fill(matrix[row].begin(), matrix[row].end(), 0);
}

void zeroCol(Matrix<std::uint32_t> &matrix, std::size_t col)
{
    for (std::vector<std::uint32_t> &row : matrix) {
        row[col] = 0;
    }
}

void zero(Matrix<std::uint32_t> &matrix)
{
    if (matrix.empty()) {
        return;
    }

    const bool firstRowHasZero = std::any_of(matrix[0].begin(), matrix[0].end(),
    [](std::uint32_t value) {
        return value == 0;
    });

    const bool firstColHasZero = std::any_of(matrix.begin(), matrix.end(),
    [](const Row<std::uint32_t> &row) {
        return row[0] == 0;
    });

    const std::size_t rowCount = matrix.size();
    const std::size_t colCount = matrix[0].size();

    for (std::size_t row = 1; row < rowCount; ++row) {
        for (std::size_t col = 1; col < colCount; ++col) {
            if (matrix[row][col] == 0) {
                matrix[0][col] = 0;
                matrix[row][0] = 0;
            }
        }
    }

    for (std::size_t row = 1; row < rowCount; ++row) {
        if (matrix[row][0] == 0) {
            zeroRow(matrix, row);
        }
    }

    for (std::size_t col = 1; col < colCount; ++col) {
        if (matrix[0][col] == 0) {
            zeroCol(matrix, col);
        }
    }

    if (firstColHasZero) {
        zeroCol(matrix, 0);
    }

    if (firstRowHasZero) {
        zeroRow(matrix, 0);
    }
}

TEST(task_1_8, zero_EmptyMatrix_EmptyMatrix)
{
    Matrix<std::uint32_t> matrix({});
    zero(matrix);

    Matrix<std::uint32_t> expected({});

    ASSERT_EQ(matrix, expected);
}

TEST(task_1_8, zero_MatrixN1M1Without0_SameMatrix)
{
    Matrix<std::uint32_t> matrix({
        { 42 }
    });
    zero(matrix);

    Matrix<std::uint32_t> expected({
        { 42 }
    });

    ASSERT_EQ(matrix, expected);
}

TEST(task_1_8, zero_MatrixN1M1With0_AlteredMatrix)
{
    Matrix<std::uint32_t> matrix({
        { 0 }
    });
    zero(matrix);

    Matrix<std::uint32_t> expected({
        { 0 }
    });

    ASSERT_EQ(matrix, expected);
}

TEST(task_1_8, zero_MatrixN2M2With0_AlteredMatrix)
{
    Matrix<std::uint32_t> matrix({
        { 0, 13 },
        { 70, 61 },
    });
    zero(matrix);

    Matrix<std::uint32_t> expected({
        { 0, 0 },
        { 0, 61 },
    });

    ASSERT_EQ(matrix, expected);
}

TEST(task_1_8, zero_MatrixN5M5Without0_SameMatrix)
{
    Matrix<std::uint32_t> matrix({
        { 92, 93, 94, 90, 12 },
        { 42, 13, 43, 80, 13 },
        { 70, 61, 65, 84, 14 },
        { 50, 51, 55, 85, 15 },
        { 22, 21, 25, 28, 17 },
    });
    zero(matrix);

    Matrix<std::uint32_t> expected({
        { 92, 93, 94, 90, 12 },
        { 42, 13, 43, 80, 13 },
        { 70, 61, 65, 84, 14 },
        { 50, 51, 55, 85, 15 },
        { 22, 21, 25, 28, 17 },
    });

    ASSERT_EQ(matrix, expected);
}

TEST(task_1_8, zero_MatrixN5M5With0_AlteredMatrix)
{
    Matrix<std::uint32_t> matrix({
        { 92, 93, 94, 90, 12 },
        { 42, 0,  0,  80, 13 },
        { 70, 15, 65, 84, 14 },
        { 50, 51, 55, 13, 0 },
        { 22, 21, 25, 28, 0 },
    });
    zero(matrix);

    Matrix<std::uint32_t> expected({
        { 92, 0, 0, 90, 0 },
        { 0, 0, 0, 0, 0 },
        { 70, 0, 0, 84, 0 },
        { 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0 },
    });

    ASSERT_EQ(matrix, expected);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
