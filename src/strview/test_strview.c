#include <stdio.h>

#include "strview.h"

static void print_tokens(cstrview sentence, cstrview delim);

int main(void)
{
	char data[] = "   The quick brown--fox jumps over the lazy -dog\t! ";
	cstrview long_sentence = cstrview_from(data);

	puts("Testing long sentence...");
	print_tokens(long_sentence, CSTRVIEW_LIT(" -\t"));

	puts("Testing long sentence with no delimiters...");
	print_tokens(long_sentence, CSTRVIEW_LIT(""));

	puts("Testing long sentence with wrong delimiters...");
	print_tokens(long_sentence, CSTRVIEW_LIT("@#"));

	puts("Testing short sentence..");
	print_tokens(cstrview_from_n(data, sizeof(data) / 3), CSTRVIEW_LIT(" \t"));

	puts("Testing single word...");
	print_tokens(CSTRVIEW_LIT("abcd"), CSTRVIEW_LIT(" -"));

	puts("Testing single word with no delimiters...");
	print_tokens(CSTRVIEW_LIT("abcd"), CSTRVIEW_LIT(""));

	puts("Testing empty string...");
	print_tokens(CSTRVIEW_LIT(""), cstrview_empty());
}

static void print_tokens(cstrview sentence, cstrview delim)
{
	printf("  Sentence: [%.*s]. Delimiters: [%.*s]\n",
		CSTRVIEW_ARGS(sentence), CSTRVIEW_ARGS(delim));
	cstrview rest = sentence;
	cstrview token;
	fputs("  Tokens: ", stdout);
	while (!cstrview_is_empty(token = cstrview_tok(&rest, delim)))
	{
		printf("[%.*s] ", CSTRVIEW_ARGS(token));
	}
	putchar('\n');
}
