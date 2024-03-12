#include <stdio.h>
#include <stdlib.h>
#include "../../utils.h"

typedef struct {
	int x;
	int y;
} point;

typedef struct {
	point center;
	int radius;
} circle;

int main()
{
	int n, total_touching_circles = 0;
	int i, j;
	scanf("%d ", &n);

	circle *circles;
	circles = malloc(n * sizeof(*circles));
	DIE(!circles, "malloc() failed");

	for (i = 0; i < n; i++)
		scanf("%d %d %d ", &circles[i].center.x, &circles[i].center.y,
			  &circles[i].radius);

//	for (i = 0; i < n; i++)
//		printf("%d %d %d %d\n", i, circles[i].center.x, circles[i].center.y,
//			   circles[i].radius);

	for (i = 0; i < n; i++) {
		for (j = i + 1; j < n; j++) {
			int radius_sum = (circles[j].radius + circles[i].radius);
			radius_sum *= radius_sum;

			int x_diff = circles[j].center.x - circles[i].center.x;
			x_diff *= x_diff;
			int y_diff = circles[j].center.y - circles[i].center.y;
			y_diff *= y_diff;

			int coordonates_sum = x_diff + y_diff;

//			printf("(%d) v (%d):\n", i, j);
//			printf("SUM: %d\n", radius_sum);
//			printf("COORD: %d\n\n", coordonates_sum);

			// sqrt((x2 - x1) ^ 2 + (y2 - y1) ^ 2) <= r1 + r2
			// raised everything to power to not use sqrt
			if (coordonates_sum <= radius_sum) {
				total_touching_circles++;
//				printf("circles %d and %d touch\n", i, j);
			}
		}
	}

	printf("Total: %d\n", total_touching_circles);
	free(circles);
	return 0;
}
