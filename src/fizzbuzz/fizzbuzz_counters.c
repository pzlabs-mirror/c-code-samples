/// @file
/// @brief Задача FizzBuzz. Рішення на основі лічильників без використання операторів % та / (у тілі циклу)
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

	int counter_3 = 3 - min_num % 3;
	int counter_5 = 5 - min_num % 5;

	for (int num = min_num; num <= max_num; ++num, --counter_3, --counter_5)
	{
		if (counter_3 != 0 && counter_5 != 0)
		{
			printf("%d", num);
		}
		if (counter_3 == 0)
		{
			printf("Fizz");
			counter_3 = 3;
		}
		if (counter_5 == 0)
		{
			printf("Buzz");
			counter_5 = 5;
		}
		printf("\n");
	}
}
