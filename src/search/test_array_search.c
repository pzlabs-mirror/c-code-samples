#include <stdbool.h>
#include <limits.h>
#include <assert.h>
#include <stdio.h>

#include "search/linear_search.h"
#include "search/binary_search.h"

/// @brief Find the size of an array at compile time
/// @warning Doesn't work on pointers
#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

typedef size_t (*fn_find_int)(const int*, size_t, int);

static bool test_sorted_array_search(const char* algo_name, fn_find_int algo_func);
static void print_array_index(size_t index);
static bool assert_search(
	fn_find_int algo_func,
	const int* array, size_t array_size,
	int value, size_t expected_pos);
static bool assert_search_all(fn_find_int algo_func, const int* array, size_t array_size);

int main(void)
{
	// Bitwise AND doesn't short-circuit. Make sure to run all the tests even if some of them fail
	bool ok = true;
	ok &= test_sorted_array_search("find_int_linear_loop", &find_int_linear_loop);
	ok &= test_sorted_array_search("find_int_linear_rec", &find_int_linear_rec);
	ok &= test_sorted_array_search("find_int_binary_loop", &find_int_binary_loop);
	ok &= test_sorted_array_search("find_int_binary_rec", &find_int_binary_rec);

	if (ok)
	{
		puts("Summary: SUCCESS, all tests passed");
		return 0;
	}
	else
	{
		puts("Summary: FAILURE, some tests failed");
		return 1;
	}

}

static bool test_sorted_array_search(const char* algo_name, fn_find_int algo_func)
{
	printf("Testing \"%s\"...\n", algo_name);

	bool ok = true;

	{
		static const int normal_arr[] = { -41, -3, 0, 2, 2, 2, 3, 5, 5, 33, 59, 82 };
		// Even number of elements
		ok &= assert_search_all(algo_func, normal_arr, ARRAY_SIZE(normal_arr));
		// Invalid keys
		ok &= assert_search(algo_func, normal_arr, ARRAY_SIZE(normal_arr), 4, SEARCH_NPOS);
		ok &= assert_search(algo_func, normal_arr, ARRAY_SIZE(normal_arr), -90, SEARCH_NPOS);
		ok &= assert_search(algo_func, normal_arr, ARRAY_SIZE(normal_arr), 100, SEARCH_NPOS);
		ok &= assert_search(algo_func, normal_arr, ARRAY_SIZE(normal_arr), INT_MIN, SEARCH_NPOS);
		ok &= assert_search(algo_func, normal_arr, ARRAY_SIZE(normal_arr), INT_MAX, SEARCH_NPOS);
		// Odd number of elements
		ok &= assert_search_all(algo_func, normal_arr, ARRAY_SIZE(normal_arr) - 1);
	}
	{
		static const int small_arr[] = { 2, 6, 9 };
		ok &= assert_search_all(algo_func, small_arr, ARRAY_SIZE(small_arr));
		ok &= assert_search(algo_func, small_arr, ARRAY_SIZE(small_arr), 0, SEARCH_NPOS);
	}
	{
		static const int single_elem_arr[] = { 4 };
		ok &= assert_search_all(algo_func, single_elem_arr, ARRAY_SIZE(single_elem_arr));
	}
	{
		static const int same_vals_arr[] = { 5, 5, 5, 5, 5 };
		ok &= assert_search_all(algo_func, same_vals_arr, ARRAY_SIZE(same_vals_arr));
	}
	{
		static const int min_max_arr[] = {
			INT_MIN, INT_MIN + 1, INT_MIN + 2,
			INT_MAX - 2, INT_MAX - 1, INT_MAX };
		ok &= assert_search_all(algo_func, min_max_arr, ARRAY_SIZE(min_max_arr));
	}

	printf("\"%s\" result: %s\n\n", algo_name, ok ? "SUCCESS" : "FAILURE");
	return ok;
}

static void print_array_index(size_t index)
{
	if (index == SEARCH_NPOS)
	{
		fputs("NOT_FOUND", stdout);
	}
	else
	{
		printf("%zu", index);
	}
}

static bool assert_search(
	fn_find_int algo_func,
	const int* array, size_t array_size,
	int value, size_t expected_pos)
{
	assert(expected_pos == SEARCH_NPOS || array[expected_pos] == value);

	const size_t actual_pos = algo_func(array, array_size, value);

	printf("Position of %d is ", value);
	print_array_index(actual_pos);
	fputs(". ", stdout);

	if (actual_pos == expected_pos)
	{
		fputs("OK\n", stdout);
		return true;
	}
	else
	{
		fputs("ERROR: Expected ", stdout);
		print_array_index(expected_pos);
		putchar('\n');
		return false;
	}
}

static bool assert_search_all(fn_find_int algo_func, const int* array, size_t array_size)
{
	bool ok = true;
	for (size_t i = 0; i < array_size; ++i)
	{
		if (i > 0 && array[i - 1] == array[i])
		{
			continue;
		}
		ok &= assert_search(algo_func, array, array_size, array[i], i);
	}
	return ok;
}
