///<summary>
/// File containig configuration which can change run of program
/// which is first homework for subject B4B33ALG - Algorithms
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
#pragma once

///<summary>
///SAFE MODE sets, if program should check inputs and errors or not
///</summary>
///<example> For turn on SAFE MODE:
///<code>
///#define SAFE_MODE
///</code>
///</example>
///<remarks>
/// If not defined, SAFE MODE is turned off
///</remarks>
//#define SAFE_MODE


///<summary>
///Sets, if program prints debug messages or not
///</summary>
///<example> For show debug messages:
///<code>
///#define DEBUG
///</code>
///</example>
///<remarks>
///If not defined, messages will be NOT printed
///</remarks>
//#define DEBUG

///<summary>
///Defines maximal length of input
///</summary>
///<remarks>
///It has no effect, when SAFE MODE is turned off
///</remarks>
#define INPUT_BUFFER_SIZE 32

