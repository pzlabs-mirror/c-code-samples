/// @file
/// @brief Лабораторна 1. Приклад рішення завдання 1
///
/// Написати програму для обчислення заданих арифметичних виразів. Вважати, що `x`, `y` -- змінні,
/// значення яких слід вводити з клавіатури, всі інші величини виразу описати як константи.
/// z = x^0.5 / (1 + a^3.2) + acos(y)^2 / 2, де x = 3, y = 0.605, a = 9.8

#include <stdio.h>
#include <math.h>

int main(void)
{
	double x;
	double y;

	printf("Enter x, y: ");
	scanf("%lf %lf", &x, &y);

	if (x < 0.)
	{
		printf("Domain error: value of 'x' must be non-negative!\n");
	}
	else if (y < -1. || y > 1.)
	{
		printf("Domain error: value of 'y' must be in the [-1; 1] interval!\n");
	}
	else
	{
		const double a = 9.8;
		const double z = sqrt(x) / (1. + pow(a, 3.2)) + pow(acos(y), 2.) / 2.;
		printf("z = %f\n", z);
	}
}
