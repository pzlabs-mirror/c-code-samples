// Завдання для КР:
// 1) Перевести 128+номер студента по списку в двійкову форму
// 2) Перевести 128+номер студента по списку в вісімкову форму
// 3) Перевести 128+номер студента по списку в шістнадцяткову форму
// 4) Перевести 1001(номер в списку в двійковій формі. 5 двійкових знаків) в десяткову форму.
//    Наприклад, номер в списку=13 (01101), то число для переведення 100101101
// 5) Перевести 47(номер в списку в вісімковій формі. 2 вісімкових цифри) в десяткову форму.
//    Наприклад, номер в списку=7 (07), то число для переведення 4707
// 6) Перевести А8(номер в списку в шістнадцятковій формі. 2 шістнадцяткових цифри) в десяткову форму.
//    Наприклад, номер в списку=10 (0А), то число для переведення А80А
// 7) Написати програму, яка зчитує 4-цифрове число і знаходить середнє арифметичне його цифр.

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

bool is_bin_digit(char digit);
bool is_oct_digit(char digit);
bool is_hex_digit(char digit);

#define BIN_NUM_LEN 32
// Big enough to hold any 32-bit number
typedef struct bin_num
{
	char digits[BIN_NUM_LEN];
} bin_num;

#define OCT_NUM_LEN 11
// Big enough to hold any 32-bit number
typedef struct oct_num
{
	char digits[OCT_NUM_LEN];
} oct_num;

#define HEX_NUM_LEN 8
// Big enough to hold any 32-bit number
typedef struct hex_num
{
	char digits[HEX_NUM_LEN];
} hex_num;

void init_bin_num(bin_num* bin);
void init_oct_num(oct_num* oct);
void init_hex_num(hex_num* hex);

void print_bin(bin_num* bin, unsigned len, FILE* stream);
void print_oct(oct_num* oct, unsigned len, FILE* stream);
void print_hex(hex_num* hex, unsigned len, FILE* stream);

uint32_t bin_to_dec(bin_num* bin);
uint32_t oct_to_dec(oct_num* oct);
uint32_t hex_to_dec(hex_num* hex);

void dec_to_bin(uint32_t dec, bin_num* bin);
void dec_to_oct(uint32_t dec, oct_num* oct);
void dec_to_hex(uint32_t dec, hex_num* hex);

void print_help(void);

static const int stud_num_min = 1;
static const int stud_num_max = 31;

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		print_help();
		return 1;
	}

	unsigned stud_num;
	{
		const char* const arg_str = argv[1];
		const size_t total_length = strlen(arg_str);
		errno = 0;
		char* end;
		const long opt_stud_num = strtol(arg_str, &end, 10);
		if (end != arg_str + total_length)
		{
			puts("Error: failed to parse student number");
			return 2;
		}
		if (errno == ERANGE || opt_stud_num < stud_num_min || opt_stud_num > stud_num_max)
		{
			puts("Error: student number out of range");
			return 2;
		}
		stud_num = (unsigned)opt_stud_num;
	}
	printf("Student number: %u\n", stud_num);

	{ // Task 1
		fputs("Task 1:\n\t", stdout);
		const uint32_t num = UINT32_C(128) + stud_num;
		bin_num binary;
		dec_to_bin(num, &binary);
		print_bin(&binary, 8, stdout);
		putchar('\n');
	}
	{ // Task 2
		// Equivalent to printf("%o\n", 128u + stud_num);
		fputs("Task 2:\n\t", stdout);
		const uint32_t num = UINT32_C(128) + stud_num;
		oct_num octal;
		dec_to_oct(num, &octal);
		print_oct(&octal, 3, stdout);
		putchar('\n');
	}
	{ // Task 3
		// Equivalent to printf("%X\n", 128u + stud_num);
		fputs("Task 3:\n\t", stdout);
		const uint32_t num = UINT32_C(128) + stud_num;
		hex_num hexadecimal;
		dec_to_hex(num, &hexadecimal);
		print_hex(&hexadecimal, 2, stdout);
		putchar('\n');
	}
	{ // Task 4
		fputs("Task 4: 0b", stdout);
		bin_num binary;
		dec_to_bin(stud_num, &binary);
		binary.digits[BIN_NUM_LEN - 9] = '1';
		binary.digits[BIN_NUM_LEN - 8] = '0';
		binary.digits[BIN_NUM_LEN - 7] = '0';
		binary.digits[BIN_NUM_LEN - 6] = '1';
		print_bin(&binary, 9, stdout);
		putchar('\n');
		const uint32_t decimal = bin_to_dec(&binary);
		printf("\t%u\n", (unsigned)decimal);
	}
	{ // Task 5
		fputs("Task 5: 0o", stdout);
		oct_num octal;
		dec_to_oct(stud_num, &octal);
		octal.digits[OCT_NUM_LEN - 4] = '4';
		octal.digits[OCT_NUM_LEN - 3] = '7';
		print_oct(&octal, 4, stdout);
		putchar('\n');
		const uint32_t decimal = oct_to_dec(&octal);
		printf("\t%u\n", (unsigned)decimal);
	}
	{ // Task 6
		fputs("Task 6: 0x", stdout);
		hex_num hexadecimal;
		dec_to_hex(stud_num, &hexadecimal);
		hexadecimal.digits[HEX_NUM_LEN - 4] = 'A';
		hexadecimal.digits[HEX_NUM_LEN - 3] = '8';
		print_hex(&hexadecimal, 4, stdout);
		putchar('\n');
		const uint32_t decimal = hex_to_dec(&hexadecimal);
		printf("\t%u\n", (unsigned)decimal);
	}
}

void init_bin_num(bin_num* bin)
{
	memset(bin->digits, '0', BIN_NUM_LEN);
}

void init_oct_num(oct_num* oct)
{
	memset(oct->digits, '0', OCT_NUM_LEN);
}

void init_hex_num(hex_num* hex)
{
	memset(hex->digits, '0', HEX_NUM_LEN);
}

void print_bin(bin_num* bin, unsigned len, FILE* stream)
{
	assert(0 < len && len <= BIN_NUM_LEN);
	fwrite(&bin->digits[BIN_NUM_LEN - len], 1, len, stream);
}

void print_oct(oct_num* oct, unsigned len, FILE* stream)
{
	assert(0 < len && len <= OCT_NUM_LEN);
	fwrite(&oct->digits[OCT_NUM_LEN - len], 1, len, stream);
}

void print_hex(hex_num* hex, unsigned len, FILE* stream)
{
	assert(0 < len && len <= HEX_NUM_LEN);
	fwrite(&hex->digits[HEX_NUM_LEN - len], 1, len, stream);
}

bool is_bin_digit(char digit)
{
	return digit == '0' || digit == '1';
}

bool is_oct_digit(char digit)
{
	return digit >= '0' && digit <= '7';
}

bool is_hex_digit(char digit)
{
	return ('0' <= digit && digit <= '9')
		|| ('A' <= digit && digit <= 'F');
}

uint32_t bin_to_dec(bin_num* bin)
{
	uint32_t result = 0;
	for (unsigned i = 0; i < BIN_NUM_LEN; ++i)
	{
		const char digit = bin->digits[BIN_NUM_LEN - i - 1];
		assert(is_bin_digit(digit));
		const uint32_t value = digit == '1';
		result += value * (UINT32_C(1) << i);
	}
	return result;
}

uint32_t oct_to_dec(oct_num* oct)
{
	// 8^n = (2^3)^n = 2^(3n)
	// TODO: check that the number doesn't get too big
	uint32_t result = 0;
	for (unsigned i = 0; i < OCT_NUM_LEN; ++i)
	{
		const char digit = oct->digits[OCT_NUM_LEN - i - 1];
		assert(is_oct_digit(digit));
		const uint32_t value = (uint32_t)(digit - '0');
		result += value * (UINT32_C(1) << (3u * i));
	}
	return result;
}

uint32_t hex_to_dec(hex_num* hex)
{
	// 16^n = (2^4)^n = 2^(4n)
	uint32_t result = 0;
	for (unsigned i = 0; i < HEX_NUM_LEN; ++i)
	{
		const char digit = hex->digits[HEX_NUM_LEN - i - 1];
		assert(is_hex_digit(digit));
		const uint32_t value = (uint32_t)(digit <= '9' ? digit - '0' : ((char)10 + digit - 'A'));
		result += value * (UINT32_C(1) << (4u * i));
	}
	return result;
}

void dec_to_bin(uint32_t dec, bin_num* bin)
{
	for (unsigned i = 0; i < BIN_NUM_LEN; ++i)
	{
		bin->digits[BIN_NUM_LEN - i - 1] = '0' + ((dec >> i) & 1);
	}
}

void dec_to_oct(uint32_t dec, oct_num* oct)
{
	init_oct_num(oct);
	uint32_t remained = dec;
	for (unsigned idx = 0; idx < OCT_NUM_LEN && remained > 0u; ++idx)
	{
		oct->digits[OCT_NUM_LEN - idx - 1] = '0' + remained % 8;
		remained /= 8;
	}
}

void dec_to_hex(uint32_t dec, hex_num* hex)
{
	memset(hex->digits, '0', HEX_NUM_LEN);
	uint32_t remained = dec;
	for (unsigned idx = 0; idx < HEX_NUM_LEN && remained > 0u; ++idx)
	{
		const unsigned value = remained % 16;
		hex->digits[HEX_NUM_LEN - idx - 1] = (char)(value < 10 ? '0' + value : 'A' + (value - 10));
		remained /= 16;
	}
}

void print_help(void)
{
	puts(
		"Usage:"
		"  test1 <stud_num>"
	);
}
