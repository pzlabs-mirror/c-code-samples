#include <math.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

// Remove annoying macros defined by Microsoft in <stdlib.h> for some reason.
// Unfortunately, NOMINMAX doesn't protect against this "feature".
#undef max
#undef min

double add(double a, double b);
double multiply(double a, double b);
double max(double a, double b);

double fold_count(double (*operation)(double, double), double init, int count, ...);
double fold_sentinel(double (*operation)(double, double), double init, ...);
double fold_ptr(double (*operation)(double, double), double init, ...);

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		fputs("Error: Expected one argument\n", stderr);
		return 1;
	}

	errno = 0;
	char* end = NULL;
	const long choice = strtol(argv[1], &end, 10);
	if (end != argv[1] + strlen(argv[1]))
	{
		fputs("Error: Argument is not a number\n", stderr);
		return 2;
	}

	if (errno == ERANGE)
	{
		fputs("Error: Argument out of range\n", stderr);
		return 3;
	}

	double nums[4] = {0};
	const size_t nums_size = sizeof(nums) / sizeof(nums[0]);

	printf("Enter %zu numbers: ", nums_size);
	for (size_t i = 0; i < nums_size; ++i)
	{
		scanf("%lf", &nums[i]);
	}

	switch (choice)
	{
		case 1:
			printf("Sum: %g\n", fold_count(&add, 0, 4, nums[0], nums[1], nums[2], nums[3]));
			break;
		case 2:
			printf("Product: %g\n", fold_sentinel(&multiply, 1, nums[0], nums[1], nums[2],
				nums[3], nan("")));
			break;
		case 3:
			printf("Max: %g\n", fold_ptr(&max, -(double)INFINITY, &nums[0], &nums[1], &nums[2],
				&nums[3], (const double*)NULL));
			break;
		default:
			fputs("Error: Argument out of range\n", stderr);
			return 3;
	}

	return 0;
}

double add(double a, double b)
{
	return a + b;
}

double multiply(double a, double b)
{
	return a * b;
}

double max(double a, double b)
{
	return a > b ? a : b;
}

double fold_count(double (*operation)(double, double), double init, int count, ...)
{
	va_list args;
	va_start(args, count);

	double accum = init;
	for (int i = 0; i < count; ++i)
	{
		accum = operation(accum, va_arg(args, double));
	}

	va_end(args);
	return accum;
}

double fold_sentinel(double (*operation)(double, double), double init, ...)
{
	va_list args;
	va_start(args, init);

	double value = 0.;
	double accum = init;
	while (!isnan(value = va_arg(args, double)))
	{
		accum = operation(accum, value);
	}

	va_end(args);
	return accum;
}

double fold_ptr(double (*operation)(double, double), double init, ...)
{
	va_list args;
	va_start(args, init);

	double accum = init;
	const double* value = NULL;
	while ((value = va_arg(args, const double*)) != NULL)
	{
		accum = operation(accum, *value);
	}

	va_end(args);
	return accum;
}
