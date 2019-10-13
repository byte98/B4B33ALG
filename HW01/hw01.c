#include <stdio.h>
#include <stdlib.h>

#define bool char
#define TRUE 1
#define FALSE 0

static volatile int WIDTH = 0;
static volatile int COUNT = 0;


int main(int argc, char* argv[])
{
	int reti = EXIT_SUCCESS;

	int visible_both = 0;
	int visible_out = 0;
	int visible_in = 0;
	int unvisible = 0;


	int* situation_out;

	char line[32];
	fgets(line, 32, stdin);
	if (sscanf(line, "%d %d", &WIDTH, &COUNT) != 2)
	{
		reti = EXIT_FAILURE;
		fprintf(stderr, "Error (l: %d): Parsing of first line failed!\n Expected: width<int> count<int>\n Get: %s",__LINE__, line);
	}

	if (reti == EXIT_SUCCESS)
	{
		situation_out = (int*)calloc(WIDTH, sizeof(int));
		if (situation_out == NULL)
		{
			reti = EXIT_FAILURE;
			fprintf(stderr, "Error (l: %d): Allocation memory for 'situation_out' failed!", __LINE__);
		}
		else
		{
			for (int i = 0; i < COUNT; i++)
			{
				int distance_left = 0;
				int height = 0;
				int width = 0;
				char data[32];
				fgets(data, 32, stdin);
				if (sscanf(data, "%d %d %d", &distance_left, &height, &width) != 3)
				{
					reti = EXIT_FAILURE;
					fprintf(stderr, "Error (l: %d): parsing line with sticky note failed!\n Expected: distance_from_left<int> height<int> width<int>\n Get: %s\n", __LINE__, data);
					break;
				}
				if (reti == EXIT_SUCCESS)
				{
					bool counted = FALSE;
					for (int d = 0; d < width; d++)
					{
						if (situation_out[distance_left + d] < height)
						{
							situation_out[distance_left + d] = height;
							if (counted == FALSE)
							{
								visible_out++;
								counted == TRUE;
							}
							
						}
					}
				}
			}
			free(situation_out);
			//printf("%d %d %d\n", )
		}		
	}

	return reti;
}