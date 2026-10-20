#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrixTriangle, can_create_matrix_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicMatrixTriangle<int> m(5));
}

TEST(TDynamicMatrixTriangle, cant_create_too_large_matrix)
{
	ASSERT_ANY_THROW(TDynamicMatrixTriangle<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrixTriangle, throws_when_create_matrix_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicMatrixTriangle<int> m(-5));
}

TEST(TDynamicMatrixTriangle, can_create_copied_matrix)
{
	TDynamicMatrixTriangle<int> m(5);

	ASSERT_NO_THROW(TDynamicMatrixTriangle<int> m1(m));
}

TEST(TDynamicMatrixTriangle, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrixTriangle<int> m(5);
	TDynamicMatrixTriangle<int> m1(m);
	ASSERT_EQ(m, m1);
}

TEST(TDynamicMatrixTriangle, copied_matrix_has_its_own_memory)
{
	TDynamicMatrixTriangle<int> m(5);
	TDynamicMatrixTriangle<int> m1(m);
	ASSERT_NE(&m[0][0], &m1[0][0]);
}

TEST(TDynamicMatrixTriangle, can_get_size)
{
	TDynamicMatrixTriangle<int> m(5);
	ASSERT_NO_THROW(m.size());
}

TEST(TDynamicMatrixTriangle, can_set_and_get_element)
{
	TDynamicMatrixTriangle<int> m(5);
	m[1][1] = 5;
	ASSERT_EQ(m[1][1], 5);
}

TEST(TDynamicMatrixTriangle, throws_when_set_element_with_negative_index)
{
	TDynamicMatrixTriangle<int> m(5);
	ASSERT_ANY_THROW(m[1].at(-5));
}

TEST(TDynamicMatrixTriangle, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrixTriangle<int> m(5);
	ASSERT_ANY_THROW(m[1].at(10));
}

TEST(TDynamicMatrixTriangle, can_assign_matrix_to_itself)
{
	TDynamicMatrixTriangle<int> m(5);
	ASSERT_NO_THROW(m = m);
}

TEST(TDynamicMatrixTriangle, can_assign_matrices_of_equal_size)
{
	TDynamicMatrixTriangle<int> m(5);
	TDynamicMatrixTriangle<int> m1(5);
	ASSERT_NO_THROW(m = m1);
}

TEST(TDynamicMatrixTriangle, assign_operator_change_matrix_size)
{
	TDynamicMatrixTriangle<int> m(5);
	TDynamicMatrixTriangle<int> m1(10);
	m = m1;
	ASSERT_EQ(m.size(), m1.size());
}

TEST(TDynamicMatrixTriangle, can_assign_matrices_of_different_size)
{
	TDynamicMatrixTriangle<int> m(5);
	TDynamicMatrixTriangle<int> m1(10);
	ASSERT_NO_THROW(m = m1);
}

TEST(TDynamicMatrixTriangle, compare_equal_matrices_return_true)
{
	TDynamicMatrixTriangle<int> m(5);
	TDynamicMatrixTriangle<int> m1(5);
	for (int i = 0; i < 5; i++) {
		for (int j = i; j < 5; j++) {
			m[i][j] = i + j;
			m1[i][j] = i + j;
		}
	}
	ASSERT_TRUE(m == m1);
}

TEST(TDynamicMatrixTriangle, compare_matrix_with_itself_return_true)
{
	TDynamicMatrixTriangle<int> m(5);
	for (int i = 0; i < 5; i++) {
		for (int j = i; j < 5; j++) {
			m[i][j] = i + j;
		}
	}
	ASSERT_TRUE(m == m);
}

TEST(TDynamicMatrixTriangle, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrixTriangle<int> m(5);
	TDynamicMatrixTriangle<int> m1(10);
	ASSERT_FALSE(m == m1);
}

TEST(TDynamicMatrixTriangle, can_add_matrices_with_equal_size)
{
	TDynamicMatrixTriangle<int> m(5);
	TDynamicMatrixTriangle<int> m1(5);
	TDynamicMatrixTriangle<int> res;
	for (int i = 0; i < 5; i++) {
		for (int j = i; j < 5; j++) {
			m[i][j] = i + j;
			m1[i][j] = i + j;
		}
	}
	ASSERT_NO_THROW(res = m + m1);
	ASSERT_EQ(res, m + m1);
}

TEST(TDynamicMatrixTriangle, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrixTriangle<int> m(5);
	TDynamicMatrixTriangle<int> m1(10);
	ASSERT_ANY_THROW(m + m1);
}

TEST(TDynamicMatrixTriangle, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrixTriangle<int> m(5);
	TDynamicMatrixTriangle<int> m1(5);
	TDynamicMatrixTriangle<int> res;
	for (int i = 0; i < 5; i++) {
		for (int j = i; j < 5; j++) {
			m[i][j] = i + j;
			m1[i][j] = i + j;
		}
	}
	ASSERT_NO_THROW(res = m - m1);
	ASSERT_EQ(res, m - m1);
}

TEST(TDynamicMatrixTriangle, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrixTriangle<int> m(5);
	TDynamicMatrixTriangle<int> m1(10);
	ASSERT_ANY_THROW(m - m1);
}

