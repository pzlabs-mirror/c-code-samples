#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H

#include "search/search_common.h"

/// @brief Find the first integer equal to value in a sorted array using binary search.
/// Loop-based implementation
/// @param arr Pointer to the first element of an array of ints sorted in ascending order
/// @return Index of the first element equal to value or SEARCH_NPOS if no such element is found
size_t find_int_binary_loop(const int* arr, size_t size, int value);

/// @brief Find the first integer equal to value in a sorted array using binary search.
/// Recursion-based implementation
/// @param arr Pointer to the first element of an array of ints sorted in ascending order
/// @return Index of the first element equal to value or SEARCH_NPOS if no such element is found
size_t find_int_binary_rec(const int* arr, size_t size, int value);

#endif // include guard
