/// @file
/// @brief Задача FizzBuzz. Рішення, в якому результати операції ділення
/// зберігаються у змінні
///
/// Написати програму, яка для кожного числа n від 1 до 100 включно:
///     а) друкує "Fizz", якщо n кратне 3, але не кратне 5;
///     б) друкує "Buzz", якщо n кратне 5, але не кратне 3;
///     в) друкує "FizzBuzz", якщо n кратне 3 і кратне 5;
///     г) друкує n, якщо жодна з умов а-в не виконується.
/// У всіх вараінтах вивід здійснюється з нового рядка.

#include <stdio.h>

int main(void)
{
	const int min_num = 1;
	const int max_num = 100;

	for (int num = min_num; num <= max_num; ++num)
	{
		const int is_multiple_of_3 = num % 3 == 0;
		const int is_multiple_of_5 = num % 5 == 0;

		if (is_multiple_of_3 && is_multiple_of_5)
		{
			printf("FizzBuzz\n");
		}
		else if (is_multiple_of_3)
		{
			printf("Fizz\n");
		}
		else if (is_multiple_of_5)
		{
			printf("Buzz\n");
		}
		else
		{
			printf("%d\n", num);
		}
	}
}
