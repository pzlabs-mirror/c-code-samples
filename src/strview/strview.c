#include "strview/strview.h"

extern inline cstrview cstrview_empty(void);
extern inline bool cstrview_is_empty(cstrview str);
extern inline cstrview cstrview_from(const char* str);
extern inline cstrview cstrview_from_n(const char* str, size_t size);
extern inline bool cstrview_contains(cstrview str, char c);

cstrview cstrview_tok(cstrview* sentence, cstrview delim)
{
	assert(sentence);
	if (cstrview_is_empty(*sentence))
	{
		return cstrview_empty();
	}

	const char* const sentence_end = sentence->data + sentence->size;
	const char* begin = sentence->data;
	while (begin != sentence_end && cstrview_contains(delim, *begin))
	{
		++begin;
	}

	const char* end = begin;
	while (end != sentence_end && !cstrview_contains(delim, *end))
	{
		++end;
	}

	sentence->size -= (size_t)(end - sentence->data);
	sentence->data = end;
	return (cstrview){.data = begin, .size = (size_t)(end - begin)};
}
