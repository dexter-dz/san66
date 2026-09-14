#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	if (argc > 1 && atoi(argv[1]) > 0)
	{
		char *pipRow = "000100010001101111", *pipCol = "020103123404424444";
		int i, j, k, number = atoi(argv[1]), dice[number];
		srand(time(NULL));
		for (i = 0; i < number; i++) dice[i] = rand() % 6;
		for (i = 0; i < number; i++) printf("   __________ ");
		printf("\n");
		for (i = 0; i < number; i++) printf("  |          |");
		printf("\n");
		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < number; j++)
			{
				printf("  |  ");
				for (k = 0; k < 3; k++)
				{
					if (pipRow[(3 * (pipCol[3 * dice[j] + i] - '0')) + k] - '0') printf("* ");
					else printf("  ");
				}
				printf("  |");
			}
			printf("\n");
		}
		for (i = 0; i < number; i++) printf("  |__________|");
		printf("\n\n");
	}
	else printf("Usage: roll <integer 1..>\n");
	return 0;
}
