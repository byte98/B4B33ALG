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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ConsoleColor.h"
#include "ConsoleColor_utils.h"

//=============================================================================================================================

char* console_color_get_background_from_rgb(console_color_data_t color)
{
	char* reti = malloc(32 * sizeof(char));
	sprintf(reti, "\033[48;2;%i;%i;%im", color.rgb_color.red, color.rgb_color.green, color.rgb_color.blue);
	return reti;
}

//=============================================================================================================================

char* console_color_get_foreground_from_rgb(console_color_data_t color)
{
	char* reti = malloc(32 * sizeof(char));
	sprintf(reti, "\033[38;2;%i;%i;%im", color.rgb_color.red, color.rgb_color.green, color.rgb_color.blue);
	return reti;
}

//=============================================================================================================================

char* console_color_get_background_from_ansi(console_color_data_t color)
{
	char* reti = malloc(32 * sizeof(char));
	sprintf(reti, "\033[;%im", color.ansi_color + 10);
	return reti;
}

//=============================================================================================================================

char* console_color_get_foreground_from_ansi(console_color_data_t color)
{
	char* reti = malloc(32 * sizeof(char));
	sprintf(reti, "\033[%im", color.ansi_color);
	return reti;
}

//=============================================================================================================================

char* console_color_get_background(console_color_t* color)
{
	switch (color->type)
	{
	case ANSI:
		return console_color_get_background_from_ansi(color->data);
		break;
	case RGB:
		return console_color_get_background_from_rgb(color->data);
		break;
	}
}

//=============================================================================================================================

char* console_color_get_foreground(console_color_t* color)
{
	switch (color->type)
	{
	case ANSI:
		return console_color_get_foreground_from_ansi(color->data);
		break;
	case RGB:
		return console_color_get_foreground_from_rgb(color->data);
		break;
	}
}

//=============================================================================================================================

char* console_color_get_color_code(console_color_t* foreground, console_color_t* background)
{
	char* reti = malloc(32 * sizeof(char));
	
	if (foreground->type == ANSI && background->type == ANSI) //Both colors are defined by ANSI code
	{
		sprintf(reti, "\033[%i;%im", foreground->data.ansi_color, background->data.ansi_color + 10);
	}
	else if (foreground->type == ANSI && background->type == RGB)
	{
		sprintf(reti, "\033[%i;m", foreground->data.ansi_color);
		sprintf(reti + strlen(reti), "\033[48;2;%i;%i;%im", background->data.rgb_color.red, background->data.rgb_color.green, background->data.rgb_color.blue);
	}
	else if (foreground->type == RGB && background->type == ANSI)
	{
		sprintf(reti, "\033[%i;m", background->data.ansi_color);
		sprintf(reti + strlen(reti), "\033[38;2;%i;%i;%im", foreground->data.rgb_color.red, foreground->data.rgb_color.green, foreground->data.rgb_color.blue);
	}
	else if (foreground->type == RGB && background->type == RGB)
	{
		char* fg = console_color_get_foreground_from_rgb(foreground->data);
		char* bg = console_color_get_background_from_rgb(background->data);
		strcpy(reti, fg);
		strcpy(reti + strlen(reti), bg);
		free(fg);
		free(bg);
	}
	return reti;
}

//=============================================================================================================================

