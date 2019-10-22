///<summary>
/// File containing declaration of queue
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
#include "simple_bool.h"
#include "sorted.h"

///<summary>
///Definition of structure Queue
///</summary>
struct Queue
{
	///<summary>
	/// Data stored in queue
	///</summary>
	int* data;

	///<summary>
	///	Index of first item in queue
	///</summary>
	int head;

	///<summary>
	///Index of last item in queue
	///</summary>
	int tail;

	///<summary>
	///Count of items in queue
	///</summary>
	int count;

	///<summary>
	///Maximal length of queue
	///</summary>
	int length;

	///<summary>
	///Index of data for "next" function
	///</summary>
	int next_head;
};

///<summary>
/// Definition of queue as new data type;
///</summary>
typedef struct Queue queue_t;

///<summary>
///Creates static length queue
///</summary>
///<param name="length">Maximal length of queue</param>
queue_t* queue_create_static(int length);

///<summary>
///Adds data to queue
///</summary>
///<param name="queue">Queue where to add data</param>
///<param name="data"> Data to be added to queue</param>
///<returns>Returns <c>TRUE</c> if data was stored into queue, <c>FALSE</c> otherwise</returns>
bool queue_push(queue_t* queue, int data);

///<summary>
///Gets data from queue
///</summary>
///<param name="queue">Queue from which gets data</param>
///<returns>Data or <c>NULL</c> if queue is empty</returns>
int queue_pop(queue_t* queue);

///<summary>
///Checks if queue is empty
///</summary>
///<param name="queue">Queue which will be checked</param>
///<returns><c>TRUE</c> if queue is empty, <c>FALSE</c> otherwise</returns>
bool queue_is_empty(queue_t* queue);

///<summary>
///Checks if queue is full
///</summary>
///<param name="queue">Queue which will be checked</param>
///<returns><c>TRUE</c> if queue is full, <c>FALSE</c> otherwise</returns>
bool queue_is_full(queue_t* queue);

///<summary>
///Gets count of elements in queue
///</summary>
///<param name="queue"> Queue which will be checked</param>
///<returns>Count of elements stored in queue</returns>
int queue_count(queue_t* queue);

///<summary>
///Gets element from queue at index
///</summary>
///<param name="queue">Queue from which will be data got</param>
///<param name="index">Index of data from which will be got</param>
///<returns>Selected data or <c>NULL</c> if there is nothing at index</returns>
int queue_at(queue_t* queue, int index);

///<summary>
///Checks, whether there is at least one element in queue
///</summary>
///<param name="queue">Queue which will be checked</param>
///<returns><c>TRUE</c> if there is any element, <c>FALSE</c> otherwise</returns>
bool queue_is_not_empty(queue_t* queue);

///<summary>
/// Gets data from queue without removing it
///</summary>
///<param name="queue">Queue with data</param>
///<returns>Selected data or <c>NULL</c></returns>
int queue_next(queue_t* queue);

///<summary>
/// Checks, whether there is some data for "next" function
///</summary>
///<param name="queue">Queue which will be checked</param>
///<returns><c>TRUE</c> if there is at least one element, <c>FALSE</c> otherwise</returns>
bool queue_next_not_empty(queue_t* queue);

///<summary>
///Resets index of "next" function
///</summary>
///<param name="queue">Queue which next index will be reseted</param>
void queue_reset_next_index(queue_t* queue);

///<summary>
///Reverses data in queue
///</summary>
///<param name="queue">Queue, which data will be copied reversed</param>
///<returns>New queue with reversed data</returns>
queue_t* queue_reverse_data(queue_t* queue);

///<summary>
///Deletes all data associated with queue
///</summary>
///<param name="queue">Queue which will be deleted</param>
void queue_delete(queue_t* queue);

#ifdef DEBUG
///<summary>
///Prints data stored in queue
///</summary>
///<param name="queue">Queue which data will be printed</param>
void queue_print(queue_t* queue);
#endif // DEBUG

///<summary>
///Checks, whether queue contains element
///</summary>
///<param name="queue">Queue where will be element searched</param>
///<param name="element">Element, which will be searched</param>
///<param name="sort">Flag of sortation of data in queue</param>
///<returns><c>TRUE</c> if queue contains element, <c>FALSE</c> otherwise</returns>
bool queue_contains(queue_t* queue, int element, sort_t sort);

///<summary>
///Checks, whether queue contains element using binar search
///</summary>
///<param name="queue">Queue where will be element searched</param>
///<param name="element">Element, which will be searched</param>
///<param name="sort">Flag of sortation of data in queue</param>
///<returns><c>TRUE</c> if queue contains element, <c>FALSE</c> otherwise</returns>
bool queue_binary_search(queue_t* queue, int element, sort_t sort);

///<summary>
///Recursive implementation of binary search
///</summary>
///<param name="queue">Queue with data</param>
///<param name="element">Searched element</param>
///<param name="sort">Flag of sortation of data in queue</param>
///<param name="start_index">Start of actually searched interval of indexes</param>
///<param name="end_index">End of actually searched interval of indexes</param>
///<returns><c>TRUE</c> if queue contains element, <c>FALSE</c> otherwise</returns>
bool queue_binary_search_recursive(queue_t* queue, int element, sort_t sort, int start_index, int end_index);

///<summary>
/// Computes next index between indexes
///</summary>
///<param name="start_index">Starting index</param>
///<param name="end_index">Ending index</param>
///<param name="queue">Queue with data</param>
///<returns>Computed index between two indexes or <c>-1</c> if there is no such an index
int queue_binary_search_next_index(int start_index, int end_index, queue_t* queue);

///<summary>
///Checks, whether there is index in queue data
///</summary>
///<param name="index">Index which will be checked</param>
///<param name="queue">Queue with data</param>
///<returns><c>TRUE</c> If there are data with index in queue, <c>FALSE</c> otherwise
bool queue_index_in_queue(int index, queue_t* queue);

