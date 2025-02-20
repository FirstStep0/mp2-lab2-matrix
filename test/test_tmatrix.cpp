#include "utmatrix.h"

#include <gtest.h>

TEST(TMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TMatrix<int> m(5));
}

TEST(TMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TMatrix<int> m(-5));
}

TEST(TMatrix, can_create_copied_matrix)
{
  TMatrix<int> m(5);

  ASSERT_NO_THROW(TMatrix<int> m1(m));
}

TEST(TMatrix, copied_matrix_is_equal_to_source_one)
{
	int size = 3;
	TMatrix<int> m(size);
	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
			m[i][j] = i + j;
		}
	}
	TMatrix<int> m1(m);
	EXPECT_EQ(m1, m);
}

TEST(TMatrix, copied_matrix_has_its_own_memory)
{
	int size = 3;
	TMatrix<int> m(size);
	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
			m[i][j] = 5;
		}
	}
	TMatrix<int> m1(m);

	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
			m[i][j] = 2;
		}
	}
	m.~TMatrix();
	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
			EXPECT_EQ(m1[i][j], 5);
		}
	}
}

TEST(TMatrix, can_get_size)
{
	TMatrix<int> m(5);
	EXPECT_EQ(m.GetSize(), 5);
}

TEST(TMatrix, can_set_and_get_element)
{
	TMatrix<int> m(5);
	m[3][4] = 3;
	EXPECT_EQ(m[3][4], 3);
}

TEST(TMatrix, throws_when_set_element_with_negative_index)
{
	TMatrix<int> m(5);
	ASSERT_ANY_THROW(m[-1][-1] = 3);
}

TEST(TMatrix, throws_when_set_element_with_too_large_index)
{
	TMatrix<int> m(5);
	ASSERT_ANY_THROW(m[5][5] = 3);
}

TEST(TMatrix, can_assign_matrix_to_itself)
{
	TMatrix<int> m(5);
	for (int i = 0; i < 5; i++) {
		for (int j = i; j < 5; j++) {
			m[i][j] = i + j;
		}
	}
	ASSERT_NO_THROW(m = m);
	for (int i = 0; i < 5; i++) {
		for (int j = i; j < 5; j++) {
			EXPECT_EQ(m[i][j], i + j);
		}
	}
}

TEST(TMatrix, can_assign_matrices_of_equal_size)
{
	int size = 5;
	TMatrix<int> m1(size), m2(size);
	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
			m1[i][j] = i + j;
		}
	}
	ASSERT_NO_THROW(m2 = m1);
	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
			EXPECT_EQ(m2[i][j], i + j);
		}
	}
}

TEST(TMatrix, assign_operator_change_matrix_size)
{
	TMatrix<int> m1(5), m2(3);
	m2 = m1;
	EXPECT_EQ(m2.GetSize(), 5);
}

TEST(TMatrix, can_assign_matrices_of_different_size)
{
	int size1 = 5, size2 = 7;
	TMatrix<int> m1(size1), m2(size2);
	for (int i = 0; i < size1; i++) {
		for (int j = i; j < size1; j++) {
			m1[i][j] = i + j;
		}
	}
	ASSERT_NO_THROW(m2 = m1);
	for (int i = 0; i < size1; i++) {
		for (int j = i; j < size1; j++) {
			EXPECT_EQ(m2[i][j], i + j);
		}
	}
}

TEST(TMatrix, compare_equal_matrices_return_true)
{
	int size = 5;
	TMatrix<int> m1(size), m2(size);
	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
			m1[i][j] = i + j;
			m2[i][j] = i + j;
		}
	}
	EXPECT_EQ(m1, m2);
}

TEST(TMatrix, compare_matrix_with_itself_return_true)
{
	int size = 5;
	TMatrix<int> m(size);
	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
			m[i][j] = i + j;
		}
	}
	EXPECT_EQ(m, m);
}

TEST(TMatrix, matrices_with_different_size_are_not_equal)
{
	int size1 = 5, size2 = 7;
	TMatrix<int> m1(size1), m2(size2);
	EXPECT_NE(m1, m2);
}

TEST(TMatrix, can_add_matrices_with_equal_size)
{
	int size = 5;
	TMatrix<int> m1(size), m2(size), m(size);
	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
			m1[i][j] = 1;
			m2[i][j] = 2;
		}
	}
	ASSERT_NO_THROW(m = m1 + m2);
	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
			EXPECT_EQ(m[i][j], 3);
		}
	}
}

TEST(TMatrix, cant_add_matrices_with_not_equal_size)
{
	int size1 = 5, size2 = 7;
	TMatrix<int> m1(size1), m2(size2);
	ASSERT_ANY_THROW(m1 + m2);
}

TEST(TMatrix, can_subtract_matrices_with_equal_size)
{
	int size = 5;
	TMatrix<int> m1(size), m2(size), m(size);
	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
			m1[i][j] = 1;
			m2[i][j] = 2;
		}
	}
	ASSERT_NO_THROW(m = m1 - m2);
	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
			EXPECT_EQ(m[i][j], -1);
		}
	}
}

TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	int size1 = 5, size2 = 7;
	TMatrix<int> m1(size1), m2(size2);
	ASSERT_ANY_THROW(m1 - m2);
}

