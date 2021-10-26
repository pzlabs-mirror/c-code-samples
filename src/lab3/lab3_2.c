/// @file
///
/// @brief Лабораторна 3. Приклад рішення завдання 2
///
/// Ввести прямокутну матрицю дійсних чисел.
/// Відсортувати рядки матриці у порядку зростання їхніх діапазонів
/// (різниці між максимальним і мінімальним значеннями).

#include <stdio.h>

#define NUM_ROWS_MAX 25
#define NUM_COLS_MAX 15

void read_matrix(double matrix[NUM_ROWS_MAX][NUM_COLS_MAX], int num_rows, int num_cols);
void print_matrix_with_col(
	double matrix[NUM_ROWS_MAX][NUM_COLS_MAX],
	const double* col, int num_rows, int num_cols);
void vector_min_max(const double* vec, int size, const double** min, const double** max);
void swap(double* a, double* b);
void swap_vectors(double* vec_a, double* vec_b, int size);

int main(void)
{
	int num_rows = NUM_ROWS_MAX;
	int num_cols = NUM_COLS_MAX;
	printf("Enter height and width of the matrix: ");
	scanf("%d %d", &num_rows, &num_cols);
	if (num_rows < 1 || num_rows > NUM_ROWS_MAX)
	{
		printf("Error: Matrix height out of allowed range from 1 to %d!\n", NUM_ROWS_MAX);
		return 1;
	}

	if (num_cols < 1 || num_cols > NUM_COLS_MAX)
	{
		printf("Error: Matrix width out of allowed range from 1 to %d!\n", NUM_COLS_MAX);
		return 2;
	}

	double matrix[NUM_ROWS_MAX][NUM_COLS_MAX] = {0};
	read_matrix(matrix, num_rows, num_cols);

	double row_ranges[NUM_ROWS_MAX];
	for (int row = 0; row < num_rows; ++row)
	{
		const double* min = NULL;
		const double* max = NULL;
		vector_min_max(matrix[row], num_cols, &min, &max);
		row_ranges[row] = *max - *min;
	}

	printf("\nBefore sorting:\n");
	print_matrix_with_col(matrix, row_ranges, num_rows, num_cols);

	// Selection sort
	for (int commit_idx = 0; commit_idx < num_rows - 1; ++commit_idx)
	{
		int smallest_idx = commit_idx;
		for (int select_idx = commit_idx + 1; select_idx < num_rows; ++select_idx)
		{
			if (row_ranges[select_idx] < row_ranges[smallest_idx])
			{
				smallest_idx = select_idx;
			}
		}

		if (commit_idx != smallest_idx)
		{
			swap(&row_ranges[commit_idx], &row_ranges[smallest_idx]);
			swap_vectors(matrix[commit_idx], matrix[smallest_idx], num_cols);
		}
	}

	printf("\nAfter sorting:\n");
	print_matrix_with_col(matrix, row_ranges, num_rows, num_cols);
}

void read_matrix(double matrix[NUM_ROWS_MAX][NUM_COLS_MAX], int num_rows, int num_cols)
{
	for (int row = 0; row < num_rows; ++row)
	{
		printf("Enter row #%d: ", row + 1);
		for (int col = 0; col < num_cols; ++col)
		{
			scanf("%lf", &matrix[row][col]);
		}
	}
}

void print_matrix_with_col(
	double matrix[NUM_ROWS_MAX][NUM_COLS_MAX],
	const double* col, int num_rows, int num_cols)
{
	for (int i = 0; i < num_rows; ++i)
	{
		for (int j = 0; j < num_cols; ++j)
		{
			printf("%12.3f ", *(*(matrix + i) + j));
		}
		printf(" | %12.3f\n", col[i]);
	}
}

void vector_min_max(const double* vec, int size, const double** min, const double** max)
{
	const double* current_min = vec;
	const double* current_max = vec;
	for (const double* elem = vec + 1; elem < vec + size; ++elem)
	{
		if (*elem < *current_min)
		{
			current_min = elem;
		}
		else if (*elem > *current_max)
		{
			current_max = elem;
		}
	}
	*min = current_min;
	*max = current_max;
}

void swap(double* a, double* b)
{
	const double tmp = *a;
	*a = *b;
	*b = tmp;
}

void swap_vectors(double* vec_a, double* vec_b, int size)
{
	for (int i = 0; i < size; ++i)
	{
		swap(vec_a + i, vec_b + i);
	}
}
