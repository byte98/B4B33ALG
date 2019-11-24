///<summary>
/// File containig declarations of functions and data types used for printing colors to console
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

#ifndef __CONSOLE_COLOR_H__
#define __CONSOLE_COLOR_H__

///<summary>
///Defines colors by ANSI escape codes
///</summary>
enum AnsiColor
{
	///<summary>
	///Black color
	///</summary>
	BLACK = 30,

	///<summary>
	///Red color
	///</summary>
	RED,

	///<summary>
	///Green color
	///</summary>
	GREEN,

	///<summary>
	///Yellow color
	///</summary>
	YELLOW,

	///<summary>
	///Blue color
	///</summary>
	BLUE,

	///<summary>
	///Magenta color
	///</summary>
	MAGENTA,

	///<summary>
	///Cyan color
	///</summary>
	CYAN,

	///<summary>
	///White color
	///</summary>
	WHITE,

	///<summary>
	///Bright black color
	///</summary>
	BLACK_BRIGHT = 90,

	///<summary>
	///Bright red color
	///</summary>
	RED_BRIGHT,

	///<summary>
	///Bright green color
	///</summary>
	GREEN_BRIGHT,

	///<summary>
	///Bright yellow color
	///</summary>
	YELLOW_BRIGHT,

	///<summary>
	///Bright blue color
	///</summary>
	BLUE_BRIGHT,

	///<summary>
	///Bright magenta color
	///</summary>
	MAGENTA_BRIGHT,

	///<summary>
	///Bright cyan color
	///</summary>
	CYAN_BRIGHT,

	///<summary>
	///Bright white color
	///</summary>
	WHITE_BRIGHT
};

///<summary>
///Type definition of ansi escape codes for colors
///</summary>
typedef enum AnsiColor ansi_color_t;

///<summary>
///Structure holding information about color in rgb
///</summary>
struct RGBColor
{
	///<summary>
	///Red part of color
	///</summary>
	int red;

	///<summary>
	///Green part of color
	///</summary>
	int green;

	///<summary>
	///Blue part of color
	///</summary>
	int blue;
};
///<summary>
///Type definiton of color in RGB model
///</summary>
typedef struct RGBColor rgb_color_t;

///<summary>
///Identifies type of color
///</summary>
enum ColorType
{
	///<summary>
	///Color defined by ANSI escape code
	///</summary>
	ANSI,

	///<summary>
	///Color defined by RGB model
	///</summary>
	RGB
};

///<summary>
///Type definition of identifier of type of color
///</summary>
typedef enum ColorType color_type_t;

///<summary>
///Space for data defining color
///</summary>
union ConsoleColorData
{
	///<summary>
	///Space for color defined by ansi escape code
	///</summary>
	ansi_color_t ansi_color;

	///<summary>
	///Space for color defined by rgb model
	///</summary>
	rgb_color_t rgb_color;
};

///<summary>
///Type definition for space for data defining color
///</summary>
typedef union ConsoleColorData console_color_data_t;

///<summary>
///Structure holding information about color usable in console
///</summary>
struct ConsoleColor
{
	///<summary>
	///Identifier of used type of color
	///</summary>
	color_type_t type;

	///<summary>
	///Data defining color
	///</summary>
	console_color_data_t data;
};

///<summary>
///Type definition of colors usable in console
///</summary>
typedef struct ConsoleColor console_color_t;

///<summary>
///Function which sets background of standart output
///</summary>
///<param name="color">Color which will be set as background</param>
void console_color_set_background(console_color_t color);

///<summary>
///Function which sets foreground of standart output
///</summary>
///<param name="color">Color which will be set as background</param>
void console_color_set_foreground(console_color_t color);

///<summary>
///Function which sets default foreground and background
///</summary>
void console_color_reset_colors();

///<summary>
///Function which gets console color from parts of its RGB model
///</summary>
///<param name="red">Red part of color</param>
///<param name="green">Green part of color</param>
///<param name="blue">Blue part of color</param>
console_color_t console_color_get_from_rgb(int red, int green, int blue);

///<summary>
///Gets color from its ANSI escape code
///</summary>
///<param name="color">ANSI escape code of color</param>
console_color_t console_color_get_from_ansi(ansi_color_t color);
#endif // !__CONSOLE_COLOR_H__