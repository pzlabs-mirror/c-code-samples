/// @file
/// @brief Приклад обміну значень двох змінних. Рішення 1: з використанням третьої змінної
///
/// Завдання: обміняти значення двох цілочисельних змінних `a` та `b`.

#include <stdio.h>

int main(void)
{
	int a = 3;
	int b = 5;

	printf("Before swap: a = %i; b = %i\n", a, b);

	int c = a;
	a = b;
	b = c;

	printf("After swap : a = %i; b = %i\n", a, b);
}
