#include "search/binary_search.h"

static size_t find_int_binary_rec_impl(const int* arr, size_t begin, size_t end, int value);

size_t find_int_binary_loop(const int* arr, size_t size, int value)
{
	size_t begin = 0;
	size_t end = size;

	while (begin < end)
	{
		size_t mid = begin + (end - begin) / 2;
		if (arr[mid] < value)
		{
			begin = mid + 1;
		}
		else if (value < arr[mid])
		{
			end = mid;
		}
		else
		{
			// Make sure the first occurrence is returned
			while (mid > begin && arr[mid - 1] == value)
			{
				--mid;
			}
			return mid;
		}
	}
	return SEARCH_NPOS;
}

size_t find_int_binary_rec(const int* arr, size_t size, int value)
{
	return find_int_binary_rec_impl(arr, 0, size, value);
}

static size_t find_int_binary_rec_impl(const int* arr, size_t begin, size_t end, int value)
{
	if (begin >= end)
	{
		return SEARCH_NPOS;
	}

	size_t mid = begin + (end - begin) / 2; // (begin + end) / 2 may cause overflow
	if (arr[mid] < value)
	{
		return find_int_binary_rec_impl(arr, mid + 1, end, value);
	}
	else if (value < arr[mid])
	{
		return find_int_binary_rec_impl(arr, begin, mid, value);
	}

	// Make sure the first occurrence is returned
	while (mid > begin && arr[mid - 1] == value)
	{
		--mid;
	}
	return mid;
}
