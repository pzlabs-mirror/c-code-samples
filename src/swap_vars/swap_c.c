/// @file
/// @brief Приклад обміну значень двох змінних. Рішення 3: без додаткових змінних
/// за допомогою оператора побітового виключного АБО (XOR)
///
/// Завдання: обміняти значення двох цілочисельних змінних `a` та `b`.

#include <stdio.h>

int main(void)
{
	int a = 3;
	int b = 5;

	printf("Before swap: a = %i; b = %i\n", a, b);

	a = a ^ b;
	b = a ^ b;
	a = a ^ b;

	printf("After swap : a = %i; b = %i\n", a, b);
}
