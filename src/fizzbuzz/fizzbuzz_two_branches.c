/// @file
/// @brief Задача FizzBuzz. Рішення, в якому в тілі циклу виконається лише необхідна
/// кількість умовних переходів
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
		if (num % 3 == 0)
		{
			if (num % 5 == 0)
			{
				puts("FizzBuzz");
			}
			else
			{
				puts("Fizz");
			}
		}
		else
		{
			if (num % 5 == 0)
			{
				puts("Buzz");
			}
			else
			{
				printf("%d\n", num);
			}
		}
	}
}