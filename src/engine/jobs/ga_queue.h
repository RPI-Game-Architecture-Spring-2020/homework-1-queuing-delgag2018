#pragma once

/*
** RPI Game Architecture Engine
**
** Portions adapted from:
** Viper Engine - Copyright (C) 2016 Velan Studios - All Rights Reserved
**
** This file is distributed under the MIT License. See LICENSE.txt.
*/

/*
** Thread-safe queue.
** https://www.research.ibm.com/people/m/michael/podc-1996.pdf
*/


#include <mutex>          // std::mutex

//structure node t {value: data type, next: pointer to node t}
struct Node
{
	//Node() : data{ nullptr }, next { nullptr } {}
	void* data = nullptr;
	Node* next = nullptr;
};

class ga_queue
{
public:
	ga_queue(int node_count);
	~ga_queue();

	void push(void* data);
	bool pop(void** data);

	int get_count() const;

	//My Code

	//Define head and tail
	Node* head;
	Node* tail;

	std::mutex headLock;
	std::mutex tailLock;
};
