/// @file
///
/// @brief Лабораторна 2. Приклад рішення завдання 2
///
/// За допомогою операторів циклу, протабулювати на відрізку від А до В з області визначення
/// функцію, задану розкладом у ряд Тейлора. Для порівняння обчислити також у кожній точці
/// табуляції значення функції задане формулою. Результати подати у виді таблиці з коментарями.
/// Функція:
///     cos(x)^2 = 1 - 2^1*x^2/2! + 2^3*x^4/4! - 2^5*x^6/6! + 2^7*x^8/8! - 2^9*x^10/10! + ...

#include <stdio.h>
#include <math.h>
#include <limits.h>

double cos2(double x);
double cos2_taylor(double x, double eps);

int main(void)
{
	double range_begin = -1.;
	double range_end = 1.;
	double step = 0.1;
	double eps = 1e-4;
	printf("Please enter A, B, step, epsilon: ");
	scanf("%lf %lf %lf %lf", &range_begin, &range_end, &step, &eps);

	if (range_end < range_begin)
	{
		printf("Error: Invalid range!\n");
		return 1;
	}

	if (step < 0. || step > (range_end - range_begin))
	{
		printf("Error: Invalid step!\n");
		return 2;
	}

	if (eps <= 0.)
	{
		printf("Error: Invalid epsilon!\n");
		return 3;
	}

	printf("%12s %11s %11s %11s\n", "x", "cos(x)^2", "taylor", "delta");
	unsigned long num_iters = (unsigned long)((range_end - range_begin) / step) + 1ul;
	if (fabs(range_begin + step * (double)(num_iters - 1ul) - range_end) > 1e-3 * step)
	{
		// Make sure that that range_end is always included
		++num_iters;
	}
	for (unsigned long iter = 0ul; iter < num_iters; ++iter)
	{
		const double x = iter == num_iters - 1ul ? range_end : range_begin + step * (double)iter;
		const double cos2_val = cos2(x);
		const double taylor_val = cos2_taylor(x, eps);
		const double delta = fabs(cos2_val - taylor_val);
		printf("%12.8f %11.8f %11.8f %11.8f\n", x, cos2_val, taylor_val, delta);
	}

	return 0;
}

double cos2(double x)
{
	const double cos_val = cos(x);
	return cos_val * cos_val;
}

double cos2_taylor(double x, double eps)
{
	const unsigned long max_iters = 10000ul; // Make sure we don't loop forever
	const double x2 = x * x;

	double sum = 1.;
	double twos = 0.5;
	double factorial = 1.;
	double power = 1.;
	unsigned long i = 0;
	double term = 0.;
	double sign = 1.;

	do {
		twos *= 4.;
		i += 2;
		factorial *= (double)(i - 1) * (double)(i);
		power *= x2;
		sign = -sign;
		term = sign * twos * power / factorial;
		sum += term;
	}
	while (fabs(term) > eps && i < 2ul * max_iters);

	return sum;
}
