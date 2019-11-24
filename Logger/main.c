#include <stdlib.h>
#include <stdio.h>

#include "ConsoleColor.h"

int main(int argc, char* argv[])
{
	int reti = EXIT_SUCCESS;
	
	console_color_t color;
	console_color_data_t data;
	data.ansi_color = RED;
	color.type = ANSI;
	color.data = data;

	console_color_t white = console_color_get_from_rgb(255, 255, 255);

	console_color_set_foreground(white);
	console_color_set_background(white);
	printf("Test\n\n\n");


	return reti;
}