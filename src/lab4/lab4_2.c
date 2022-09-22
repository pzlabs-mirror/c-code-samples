/// @file
///
/// @brief Лабораторна 4. Приклад рішення завдання 2
///
/// Вважаючи, що введене речення з клавіатури складається з довільної кількості слів, між
/// якими є довільна кількість пробілів, і закінчується речення крапкою, написати програму для
/// розв’язання завдання:
///   Вилучити з введеного речення всі слова, які починаються з заданого користувачем префікса.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SENTENCE_LEN_MAX 1023
#define PREFIX_LEN_MAX 511

char* skip_whitespace(char* begin);
char* find_word_end(char* word_begin);
char* find_word_starting_with(char* sentence, const char* prefix, size_t prefix_len);
void remove_words_starting_with(char* sentence, const char* prefix);

int main(void)
{
	char sentence[SENTENCE_LEN_MAX + 1] = {0};

	puts("Enter sentence:");
	// gets is unsafe and has been removed since C11. gets_s is not available in many
	// implementations, notably glibc. fgets is a C99 alternative
	if (fgets(sentence, SENTENCE_LEN_MAX, stdin) == NULL)
	{
		fputs("Error: Failed to read sentence!\n", stderr);
		return EXIT_FAILURE;
	}
	size_t sentence_len = strlen(sentence);
	if (sentence_len > 0 && sentence[sentence_len - 1] == '\n')
	{
		// fgets copies the whole line including the newline character
		sentence[sentence_len - 1] = '\0';
		--sentence_len;
	}
	if (sentence_len == 0 || sentence[sentence_len - 1] != '.')
	{
		fputs("Error: Sentence must end with a period!\n", stderr);
		return EXIT_FAILURE;
	}

	// fgets reads everything except newline characters, so it's not suitable for parsing a single
	// word of prefix (unless we manually split the string buffer after the fgets call).
	// scanf_s is de facto non-portable. As a replacement we manually construct
	// the format string for scanf in the form of "%<buffer_length>s".
	// NOTE: Unlike fgets, scanf requires the buffer to have room for at least width+1 characters
	char prefix_fmt_str[16] = {0};
	snprintf(prefix_fmt_str, sizeof(prefix_fmt_str), "%%%us", PREFIX_LEN_MAX);
	puts("Enter prefix:");

	char prefix[PREFIX_LEN_MAX + 1] = {0};
	if (scanf(prefix_fmt_str, prefix) == EOF)
	{
		fputs("Error: Failed to read prefix!\n", stderr);
		return EXIT_FAILURE;
	}

	remove_words_starting_with(sentence, prefix);
	printf("Sentence without words starting with \"%s\":\n%s\n", prefix, sentence);

	return EXIT_SUCCESS;
}

char* skip_whitespace(char* begin)
{
	char* end = begin;
	while (isspace(*end))
	{
		++end;
	}
	return end;
}

char* find_word_end(char* word_begin)
{
	char* word_end = word_begin;
	while (*word_end && !isspace(*word_end) && *word_end != '.')
	{
		++word_end;
	}
	return word_end;
}

char* find_word_starting_with(char* sentence, const char* prefix, size_t prefix_len)
{
	char* current = sentence;
	if (prefix_len > 0)
	{
		while (*current)
		{
			// Find the next prefix occurrence
			char* const word_begin = strstr(current, prefix);
			if (!word_begin)
			{
				break;
			}
			// Check whether the occurrence is at the beginning of a word
			if (word_begin == sentence || isspace(*(word_begin - 1)))
			{
				return word_begin;
			}
			// It is not a prefix. Keep looking
			current = word_begin + prefix_len;
		}
	}

	// No words found: return pointer to '\0'. Makes handling return value simpler
	while (*current)
	{
		++current;
	}
	return current;
}

void remove_words_starting_with(char* sentence, const char* prefix)
{
	const size_t prefix_len = strlen(prefix);
	char* cursor = sentence;
	char* chunk_begin = skip_whitespace(sentence);
	while (*chunk_begin)
	{
		char* chunk_end = find_word_starting_with(chunk_begin, prefix, prefix_len);

		const size_t chunk_size = (size_t)(chunk_end - chunk_begin); // guaranteed to not undeflow
		// Shift characters in place skipping one word that starts with the prefix
		memmove(cursor, chunk_begin, chunk_size);
		cursor += chunk_size;

		chunk_begin = skip_whitespace(find_word_end(chunk_end));
	}

	// Trim whitespace at the end
	if (cursor > sentence)
	{
		--cursor;
		while (cursor > sentence)
		{
			if (isspace(*cursor) || *cursor == '.')
			{
				--cursor;
			}
			else
			{
				// Overshoot. Step one character back
				++cursor;
				break;
			}
		}
	}
	*cursor = '.';
	*++cursor = '\0';
}
