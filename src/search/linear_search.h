#ifndef LINEAR_SEARCH_H
#define LINEAR_SEARCH_H

#include "search/search_common.h"

/// @brief Find the first integer equal to value in an array using linear search.
/// Loop-based implementation
/// @return Index of the first element equal to value or SEARCH_NPOS if no such element is found
size_t find_int_linear_loop(const int* arr, size_t size, int value);

/// @brief Find the first integer equal to value in an array using linear search.
/// Recursion-based implementation
/// @return Index of the first element equal to value or SEARCH_NPOS if no such element is found
size_t find_int_linear_rec(const int* arr, size_t size, int value);

#endif // include guard
