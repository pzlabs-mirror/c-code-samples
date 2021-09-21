/// @file
/// @brief Задача FizzBuzz. Рішення з використанням бітових масок
///
/// Написати програму, яка для кожного числа n від 1 до 100 включно:
///     а) друкує "Fizz", якщо n кратне 3, але не кратне 5;
///     б) друкує "Buzz", якщо n кратне 5, але не кратне 3;
///     в) друкує "FizzBuzz", якщо n кратне 3 і кратне 5;
///     г) друкує n, якщо жодна з умов а-в не виконується.
/// У всіх вараінтах вивід здійснюється з нового рядка.

#include <stdio.h>

/// Bitmasks for each divisor. We can only use `#define`s since `const int` variables in C
/// aren't constant expressions (but they are in C++, Zig, ...)
#define DIVISIBLE_BY_3 1u
#define DIVISIBLE_BY_5 (1u << 1)

int main(void)
{
	const int min_num = 1;
	const int max_num = 100;

	for (int num = min_num; num <= max_num; ++num)
	{
		const unsigned bitset
			= (unsigned)(num % 3 == 0) * DIVISIBLE_BY_3
			| (unsigned)(num % 5 == 0) * DIVISIBLE_BY_5;

		switch (bitset)
		{
			case DIVISIBLE_BY_3:
				printf("Fizz\n");
				break;
			case DIVISIBLE_BY_5:
				printf("Buzz\n");
				break;
			case DIVISIBLE_BY_3 | DIVISIBLE_BY_5:
				printf("FizzBuzz\n");
				break;
			default:
				printf("%d\n", num);
		}
	}
}
