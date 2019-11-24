///<summary>
/// File containig implementation of functions and data types used for printing colors to console
/// used in logging library
///</summary>
///<remarks>
/// Copyright 2019 Jiri Skoda <skodaji4@fel.cvut.cz>
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
/// http ://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissionsand
/// limitations under the License.
///</remarks>

#include <stdio.h>
#include <stdlib.h>

#include "ConsoleColor.h"
#include "ConsoleColor_utils.h"

//=============================================================================================================================

void console_color_set_foreground(console_color_t color)
{
	console_color_foreground = color;
	char* code = console_color_get_color_code(&console_color_foreground, &console_color_background);
	printf("%s", code);
	
	(code);
}

//=============================================================================================================================

void console_color_reset_colors()
{
	printf("\033[0m");
}

//=============================================================================================================================

console_color_t console_color_get_from_rgb(int red, int green, int blue)
{
	rgb_color_t rgb_color =
	{
		.red = red,
		.blue = blue,
		.green = green
	};
	console_color_data_t data =
	{
		.rgb_color = rgb_color
	};
	console_color_t reti =
	{
		.data = data,
		.type = RGB
	};
	return reti;
}

//=============================================================================================================================

console_color_t console_color_get_from_ansi(ansi_color_t color)
{
	console_color_data_t data =
	{
		.ansi_color = color
	};
	console_color_t reti =
	{
		.type = ANSI,
		.data = data
	};
	return reti;
}

//=============================================================================================================================

void console_color_set_background(console_color_t color)
{
	console_color_background = color;
	char* code = console_color_get_color_code(&console_color_foreground, &console_color_background);
	printf("%s", code);
	//free(code);
}
