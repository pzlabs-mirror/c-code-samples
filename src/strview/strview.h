#ifndef STRVIEW_H
#define STRVIEW_H

#include <stddef.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#define NPOS SIZE_MAX

/// @brief A constant contiguous sequence of chars that is not necessarily null-terminated
typedef struct cstrview
{
	const char* data;
	size_t size;
} cstrview;

/// @brief Construct cstrview from a string literal
/// @note "" literal "" construct protects from accidental usage on anything but a string literal
#define CSTRVIEW_LIT(literal) (cstrview){"" literal "", sizeof(literal) - 1}

/// @brief A pair of printf arguments to print a non-terminated string.
/// Use with "%.*s" format specifier
#define CSTRVIEW_ARGS(str) (int)(str).size,(str).data

inline cstrview cstrview_empty(void)
{
	return (cstrview){NULL, 0};
}

inline bool cstrview_is_empty(cstrview str)
{
	return str.size == 0;
}

inline cstrview cstrview_from(const char* str)
{
	assert(str);
	return (cstrview) {.data = str, .size = strlen(str)};
}

inline cstrview cstrview_from_n(const char* str, size_t size)
{
	assert(str);
	return (cstrview) {.data = str, .size = size};
}

inline bool cstrview_contains(cstrview str, char c)
{
	for (size_t i = 0; i < str.size; ++i)
	{
		if (str.data[i] == c)
		{
			return true;
		}
	}
	return false;
}

cstrview cstrview_tok(cstrview* sentence, cstrview delim);

#endif // include guard
