#include <stdint.h>
#include <stdio.h>

#define BASE 10
#define M_31 INT32_MAX;
#define MODULE UINT16_MAX

int32_t n_start, n_end;
uint16_t num_width, fact_width;
int8_t align;

uint32_t get_factorial(const uint32_t num)
{
	uint64_t factorial = 1;
	for (uint64_t i = 2; i <= num; i++)
	{
		factorial = factorial * i % M_31;
	}
	return factorial;
}

uint8_t count_digits(uint32_t num)
{
	uint8_t num_size = 0;
	do
	{
		num /= BASE;
		++num_size;
	} while (num > 0);
	return num_size;
}

void paste_spaces(const uint8_t amount)
{
	for (int i = 0; i < amount; i++)
	{
		printf(" ");
	}
}

void print_cover(void)
{
	printf("+");
	for (uint8_t i = 0; i < num_width + 2; i++)
	{
		printf("-");
	}
	printf("+");
	for (uint8_t i = 0; i < fact_width + 2; i++)
	{
		printf("-");
	}
	printf("+\n");
}

void print_header(void)
{
	print_cover();
	if (align)
	{
		printf("| %*c | %*s |\n", align * num_width, 'n', align * fact_width, "n!");
	}
	else
	{
		const uint8_t num_spaces = num_width - 1;
		const uint8_t fact_spaces = fact_width - 2;
		printf("| ");
		paste_spaces(num_spaces / 2 + num_spaces % 2);
		printf("%c", 'n');
		paste_spaces(num_spaces / 2);
		printf(" | ");
		paste_spaces(fact_spaces / 2 + fact_spaces % 2);
		printf("%s", "n!");
		paste_spaces(fact_spaces / 2);
		printf(" |\n");
	}
	print_cover();
}

void print_data(const uint16_t start, const uint16_t end)
{
	uint64_t fact = start > 0 ? get_factorial(start - 1) : 1;
	for (uint32_t num = start; num <= end; num++)
	{
		fact = fact * (num == 0 ? 1 : num) % M_31;
		if (align)
		{
			printf("| %*d | %*ld |\n", align * num_width, num, align * fact_width, fact);
		}
		else
		{
			const uint8_t num_spaces = num_width - count_digits(num);
			const uint8_t fact_spaces = fact_width - count_digits(fact);
			printf("| ");
			paste_spaces(num_spaces / 2 + num_spaces % 2);
			printf("%d", num);
			paste_spaces(num_spaces / 2);
			printf(" | ");
			paste_spaces(fact_spaces / 2 + fact_spaces % 2);
			printf("%ld", fact);
			paste_spaces(fact_spaces / 2);
			printf(" |\n");
		}
	}
}

int main(void)
{
	scanf("%d %d %hhd", &n_start, &n_end, &align);
	if (n_start >= 0 && n_end >= 0 && -1 <= align && align <= 1)
	{
		if (n_start <= n_end)
		{
			num_width = count_digits(n_end);
			const uint8_t temp = count_digits(get_factorial(n_end));
			fact_width = temp != 1 ? temp : 2;
			print_header();
			print_data(n_start, n_end);
			print_cover();
		}
		else
		{
			num_width = count_digits(MODULE);
			fact_width = count_digits(get_factorial(MODULE));
			print_header();
			print_data(n_start, MODULE);
			print_data(0, n_end);
			print_cover();
		}
		return 0;
	}
	if (n_start < 0 || n_end < 0)
	{
		fprintf(stderr, "Impossible to get the factorial of a negative number.\n");
	}
	return 1;
}
