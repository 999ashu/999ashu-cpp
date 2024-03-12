#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#define BASE 10
#define M_31 INT32_MAX
#define MODULE UINT16_MAX
#define DIV2(x) (x >> 1)
#define MOD2(x) (x & 1)

uint8_t number_len(int32_t num)
{
	uint8_t num_size = 0;
	do
	{
		num /= BASE;
		++num_size;
	} while (num > 0);
	return num_size;
}

uint8_t biggest_factorial_len(const uint16_t num)
{
	uint8_t counter = 1;
	uint64_t factorial = 1;
	for (uint32_t i = 2; i <= num; i++)
	{
		factorial = factorial * i % M_31;
		const uint8_t len = number_len(factorial);
		counter = len > counter ? len : counter;
		if (counter == 10)
		{
			break;
		}
	}
	return counter;
}

void print_cover(const uint8_t num_width, const uint8_t fact_width)
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

void print_header(const uint8_t num_width, const uint8_t fact_width, const int8_t align)
{
	print_cover(num_width, fact_width);
	if (align)
	{
		printf("| %*c | %*s |\n", align * num_width, 'n', align * fact_width, "n!");
	}
	else
	{
		const uint8_t num_spaces = num_width - 1;
		const uint8_t fact_spaces = fact_width - 2;
		printf(
			"| %*s%c%*s | %*s%s%*s |\n",
			DIV2(num_spaces) + MOD2(num_spaces),
			"",
			'n',
			DIV2(num_spaces),
			"",
			DIV2(fact_spaces) + MOD2(fact_spaces),
			"",
			"n!",
			DIV2(fact_spaces),
			"");
	}
	print_cover(num_width, fact_width);
}

void print_data(const uint16_t start, const uint16_t end, const uint8_t num_width, const uint8_t fact_width, const int8_t align)
{
	uint64_t fact = 1;
	if (start > 0)
	{
		for (uint16_t i = 2; i <= start - 1; i++)
		{
			fact = fact * i % M_31;
		}
	}
	for (uint32_t num = start; num <= end; num++)
	{
		fact = fact * (num == 0 ? 1 : num) % M_31;
		if (align)
		{
			printf("| %*" PRIu16 " | %*" PRIu64 " |\n", align * num_width, num, align * fact_width, fact);
		}
		else
		{
			const uint8_t num_spaces = num_width - number_len(num);
			const uint8_t fact_spaces = fact_width - number_len(fact);
			printf(
				"| %*s%" PRIu16 "%*s | %*s%" PRIu64 "%*s |\n",
				DIV2(num_spaces) + MOD2(num_spaces),
				"",
				num,
				DIV2(num_spaces),
				"",
				DIV2(fact_spaces) + MOD2(fact_spaces),
				"",
				fact,
				DIV2(fact_spaces),
				"");
		}
	}
}

int main(void)
{
	int32_t n_start, n_end;
	int8_t align;
	if (scanf("%d %d %hhd", &n_start, &n_end, &align) < 3)
	{
		return 1;
	}
	if (n_start >= 0 && n_end >= 0 && -1 <= align && align <= 1)
	{
		uint8_t num_width, fact_width;
		if (n_start <= n_end)
		{
			num_width = number_len(n_end);
			const uint8_t temp = biggest_factorial_len(n_end);
			fact_width = temp != 1 ? temp : 2;
			print_header(num_width, fact_width, align);
			print_data(n_start, n_end, num_width, fact_width, align);
		}
		else
		{
			num_width = number_len(MODULE);
			fact_width = biggest_factorial_len(MODULE);
			print_header(num_width, fact_width, align);
			print_data(n_start, MODULE, num_width, fact_width, align);
			print_data(0, n_end, num_width, fact_width, align);
		}
		print_cover(num_width, fact_width);
		return 0;
	}
	if (n_start < 0 || n_end < 0)
	{
		fprintf(stderr, "Impossible to get the factorial of a negative number.\n");
	}
	return 1;
}
