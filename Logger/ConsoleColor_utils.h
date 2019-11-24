///<summary>
/// File containig declarations of utility functions and data types used for printing colors to console
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

#ifndef __CONSOLE_COLOR_UTILS_H__
#define __CONSOLE_COLOR_UTILS_H__
#include "ConsoleColor.h"

///<summary>
///Last used foreground color
///</summary>
static console_color_t console_color_foreground;

///<summary>
///Last used background
///</summary>
static console_color_t console_color_background;

///<summary>
///Gets printable ansi escape code for color as background
///</summary>
///<param name="color">Color which code will be got</param>
char* console_color_get_background(console_color_t* color);

///<summary>
///Gets printable ansi escape code for color as foreground
///</summary>
///<param name="color">Color which code will be got</param>
char* console_color_get_foreground(console_color_t* color);

///<summary>
///Gets printable ansi escape code for color as background
///</summary>
///<param name="color">Color in rgb model which code will be got</param>
char* console_color_get_background_from_rgb(console_color_data_t color);

///<summary>
///Gets printable ansi escape code for color as foreground
///</summary>
///<param name="color">Color in rgb model which code will be got</param>
char* console_color_get_foreground_from_rgb(console_color_data_t color);

///<summary>
///Gets printable ansi escape code for color as background
///</summary>
///<param name="color">Color as ansi escape code model which code will be got</param>
char* console_color_get_background_from_ansi(console_color_data_t color);

///<summary>
///Gets printable ansi escape code for color as foreground
///</summary>
///<param name="color">Color as ansi escape code model which code will be got</param>
char* console_color_get_foreground_from_rgb(console_color_data_t color);

///<summary>
///Gets printable ansi escape code for color for both foreground and background
///</summary>
///<param name="foreground">Color which will be foruground</param>
///<param name="background">Color which will be background</param>
char* console_color_get_color_code(console_color_t* foreground, console_color_t* background);

#endif // !__CONSOLE_COLOR_UTILS_H__
