#include "search/linear_search.h"

static size_t find_int_linear_rec_impl(const int* arr, size_t size, size_t index, int value);

size_t find_int_linear_loop(const int* arr, size_t size, int value)
{
	for (size_t i = 0; i != size; ++i)
	{
		if (arr[i] == value)
		{
			return i;
		}
	}
	return SEARCH_NPOS;
}

size_t find_int_linear_rec(const int* arr, size_t size, int value)
{
	return find_int_linear_rec_impl(arr, size, 0, value);
}

static size_t find_int_linear_rec_impl(const int* arr, size_t size, size_t index, int value)
{
	if (index == size)
	{
		return SEARCH_NPOS;
	}

	return arr[index] == value
		? index
		: find_int_linear_rec_impl(arr, size, index + 1, value);
}
