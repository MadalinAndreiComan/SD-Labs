#include "../../utils.h"

int main()
{
	int **matrix;
	int nr_lines, nr_columns;
	int i, j;
	scanf("%d %d ", &nr_lines, &nr_columns);

	matrix = malloc(nr_lines * sizeof(int *));
	DIE(!matrix, "malloc() failed");
	matrix[0] = malloc(nr_lines * nr_columns * sizeof(int));
	DIE(!matrix[0], "malloc() failed");
	for (i = 1; i < nr_lines; i++)
		matrix[i] = matrix[0] + i * nr_columns;

//	There are no tests to see if the input is a valid number

//	The input has each digit separated by space
//	for (i = 0; i < nr_lines; i++)
//		for (j = 0; j < nr_columns; j++)
//			scanf("%d ", &matrix[i][j]);

//	The input takes the whole number
//	char *number = malloc(nr_columns * sizeof(char));
//	DIE(!number, "malloc() failed");
//	for (i = 0; i < nr_lines; i++) {
//		scanf("%s ", number);
//		for (j = 0; j < nr_columns; j++)
//			matrix[i][j] = number[j] - '0';
//	}
//	free(number);

	int nr_sum = 0;
	for (i = 0; i < nr_lines; i++) {
		int nr = 0;
		for (j = 0; j < nr_columns; j++)
			nr = nr * 10 + matrix[i][j];
		nr_sum += nr;
	}

	printf("Sum of numbers = %d", nr_sum);
	return 0;
}
