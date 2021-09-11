/// @file
/// @brief Лабораторна 1. Приклад рішення завдання 2
///
/// Не використовуючи оператор циклу, скласти програму, яка у п'ятизначному числі,
/// введеному з клавіатури, знаходить мінімальну цифру та її номер.

#include <stdio.h>

int main(void)
{
    int num;

    printf("Please enter a five-digit number: ");
    scanf("%d", &num);

    if (num < 10000 || num > 99999)
    {
        printf("Invalid number!\n");
    }
    else
    {
        const int digit1 = num / 10000 % 10;
        const int digit2 = num / 1000 % 10;
        const int digit3 = num / 100 % 10;
        const int digit4 = num / 10 % 10;
        const int digit5 = num % 10;

        int min_digit = digit1;
        int min_index = 1;

        if (digit2 < min_digit)
        {
            min_digit = digit2;
            min_index = 2;
        }

        if (digit3 < min_digit)
        {
            min_digit = digit3;
            min_index = 3;
        }

        if (digit4 < min_digit)
        {
            min_digit = digit4;
            min_index = 4;
        }

        if (digit5 < min_digit)
        {
            min_digit = digit5;
            min_index = 5;
        }

        printf("The minimum digit has value %d and index %d\n", min_digit, min_index);
    }
}
