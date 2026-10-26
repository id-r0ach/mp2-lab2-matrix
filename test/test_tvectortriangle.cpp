#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVectorTriangle, can_create_vector_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicVectorTriangle<int> v(5));
}

TEST(TDynamicVectorTriangle, cant_create_too_large_vector)
{
	ASSERT_ANY_THROW(TDynamicVectorTriangle<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVectorTriangle, throws_when_create_vector_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicVectorTriangle<int> v(-5));
}

TEST(TDynamicVectorTriangle, can_create_copied_vector)
{
	TDynamicVectorTriangle<int> v(10);

	ASSERT_NO_THROW(TDynamicVectorTriangle<int> v1(v));
}

TEST(TDynamicVectorTriangle, copied_vector_is_equal_to_source_one)
{
	TDynamicVectorTriangle<int> v(10);
	TDynamicVectorTriangle<int> v1(v);
	ASSERT_EQ(v, v1);
}

TEST(TDynamicVectorTriangle, copied_vector_has_its_own_memory)
{
	TDynamicVectorTriangle<int> v(10);
	TDynamicVectorTriangle<int> v1(v);
	ASSERT_NE(&v[0], &v1[0]);
}

TEST(TDynamicVectorTriangle, can_get_size)
{
	TDynamicVectorTriangle<int> v(4);

	EXPECT_EQ(4, v.size());
}

TEST(TDynamicVectorTriangle, can_set_and_get_element)
{
	TDynamicVectorTriangle<int> v(4);
	v[0] = 4;

	EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVectorTriangle, throws_when_set_element_with_negative_index)
{
	TDynamicVectorTriangle<int> v(4);
	ASSERT_ANY_THROW(v.at(-1));
}

TEST(TDynamicVectorTriangle, throws_when_set_element_with_too_large_index)
{
	TDynamicVectorTriangle<int> v(4);
	ASSERT_ANY_THROW(v.at(10));
}

TEST(TDynamicVectorTriangle, can_assign_vector_to_itself)
{
	TDynamicVectorTriangle<int> v(4);
	ASSERT_NO_THROW(v = v);
}

TEST(TDynamicVectorTriangle, can_assign_vectors_of_equal_size)
{
	TDynamicVectorTriangle<int> v(4);
	TDynamicVectorTriangle<int> v1(4);
	ASSERT_NO_THROW(v = v1);
	ASSERT_EQ(v, v1);
}

TEST(TDynamicVectorTriangle, assign_operator_change_vector_size)
{
	TDynamicVectorTriangle<int> v(4);
	TDynamicVectorTriangle<int> v1(6);
	ASSERT_NO_THROW(v = v1);
	ASSERT_EQ(v.size(), 6);
}

TEST(TDynamicVectorTriangle, can_assign_vectors_of_different_size)
{
	TDynamicVectorTriangle<int> v(3);
	TDynamicVectorTriangle<int> v1(6);
	for (int i = 0; i < 3; i++) {
		v[i] = i * 10;
	}
	for (int i = 0; i < 6; i++) {
		v1[i] = i;
	}
	ASSERT_NO_THROW(v = v1);
	ASSERT_EQ(v, v1);
}

TEST(TDynamicVectorTriangle, compare_equal_vectors_return_true)
{
	TDynamicVectorTriangle<int> v(3);
	TDynamicVectorTriangle<int> v1(3);
	ASSERT_TRUE(v == v1);
}

TEST(TDynamicVectorTriangle, compare_vector_with_itself_return_true)
{
	TDynamicVectorTriangle<int> v(3);
	ASSERT_TRUE(v == v);
}

TEST(TDynamicVectorTriangle, vectors_with_different_size_are_not_equal)
{
	TDynamicVectorTriangle<int> v(3);
	TDynamicVectorTriangle<int> v1(6);
	ASSERT_FALSE(v == v1);
}

TEST(TDynamicVectorTriangle, can_add_scalar_to_vector)
{
	TDynamicVectorTriangle<int> v(3);
	for (int i = 0; i < 3; i++) {
		v[i] = i;
	}
	TDynamicVectorTriangle<int> res;
	ASSERT_NO_THROW(res = v + 3);
	ASSERT_EQ(v + 3, res);
}

TEST(TDynamicVectorTriangle, can_subtract_scalar_from_vector)
{
	TDynamicVectorTriangle<int> v(3);
	for (int i = 0; i < 3; i++) {
		v[i] = i;
	}
	TDynamicVectorTriangle<int> res;
	ASSERT_NO_THROW(res = v - 3);
	ASSERT_EQ(v - 3, res);
}

TEST(TDynamicVectorTriangle, can_multiply_scalar_by_vector)
{
	TDynamicVectorTriangle<int> v(3);
	for (int i = 0; i < 3; i++) {
		v[i] = i;
	}
	TDynamicVectorTriangle<int> res;
	ASSERT_NO_THROW(res = v * 3);
	ASSERT_EQ(v * 3, res);
}

TEST(TDynamicVectorTriangle, can_add_vectors_with_equal_size)
{
	TDynamicVectorTriangle<int> v(3);
	TDynamicVectorTriangle<int> v1(3);
	TDynamicVectorTriangle<int> res;
	ASSERT_NO_THROW(res = v + v1);
	ASSERT_EQ(v + v1, res);
}

TEST(TDynamicVectorTriangle, cant_add_vectors_with_not_equal_size)
{
	TDynamicVectorTriangle<int> v(3);
	TDynamicVectorTriangle<int> v1(6);
	ASSERT_ANY_THROW(v + v1);
}

TEST(TDynamicVectorTriangle, can_subtract_vectors_with_equal_size)
{
	TDynamicVectorTriangle<int> v(3);
	TDynamicVectorTriangle<int> v1(3);
	TDynamicVectorTriangle<int> res;
	ASSERT_NO_THROW(res = v - v1);
	ASSERT_EQ(v - v1, res);
}

TEST(TDynamicVectorTriangle, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVectorTriangle<int> v(3);
	TDynamicVectorTriangle<int> v1(6);
	ASSERT_ANY_THROW(v - v1);
}

TEST(TDynamicVectorTriangle, can_multiply_vectors_with_equal_size)
{
	TDynamicVectorTriangle<int> v(3);
	TDynamicVectorTriangle<int> v1(3);
	int res;
	ASSERT_NO_THROW(res = v * v1);
	ASSERT_EQ(v * v1, res);
}

TEST(TDynamicVectorTriangle, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVectorTriangle<int> v(3);
	TDynamicVectorTriangle<int> v1(6);
	ASSERT_DEATH(v * v1, "");
}

