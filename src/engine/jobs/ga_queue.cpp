/*
** RPI Game Architecture Engine
**
** Portions adapted from:
** Viper Engine - Copyright (C) 2016 Velan Studios - All Rights Reserved
**
** This file is distributed under the MIT License. See LICENSE.txt.
*/

#include "ga_queue.h"


//structure queue t {Head: pointer to node t, Tail: pointer to node t, H lock: lock type, T lock: lock type}
ga_queue::ga_queue(int node_count)
{
	// TODO:
	// Initialize the queue.
	// For extra credit, preallocate 'node_count' elements (instead of
	// allocating on push).
	// See https://www.research.ibm.com/people/m/michael/podc-1996.pdf

	//My Code
	Node* t = new Node();
	t->next = nullptr;
	head = tail = t;

	//headLock.unlock(); 
	//tailLock.unlock();
}

ga_queue::~ga_queue()
{
	// TODO:
	// Free any resources held by the queue.
	// See https://www.research.ibm.com/people/m/michael/podc-1996.pdf

	//My Code
	Node* ptr = head;
	while (ptr)
	{
		Node* n = ptr->next;
		free(ptr);
		ptr = n;
	}
	
	//free(tail);
	return;
}

void ga_queue::push(void* data)
{
	// TODO:
	// Push 'data' onto the queue in a thread-safe manner.
	// If you preallocated 'node_count' elements, and if the queue is full when
	// this function is called, you must block until another thread pops an
	// element off the queue.
	// See https://www.research.ibm.com/people/m/michael/podc-1996.pdf

	//My Code
	Node* newN = new Node();	//Create new node
	newN->data = data;			//Set node->data to parameter data
	newN->next = nullptr;		//Set node->next to null

	tailLock.lock();			//Using tailLock lock tail and tail->next
		tail->next = newN;		//Set tail->next to new node
		tail = newN;			//Set new node as tail
	tailLock.unlock();			//Unlock tail and tail->

	return;
}

bool ga_queue::pop(void** data)
{
	// TODO:
	// Pop one element off the queue in a thread-safe manner and place it in
	// the memory pointed to by 'data'.
	// If the queue is empty when this function is called, return false.
	// Otherwise return true.
	// See https://www.research.ibm.com/people/m/michael/podc-1996.pdf

	//My Code

	//Lock vairables
	headLock.lock();
		Node* popN = head;			//create new Node to store old head
		Node* newH = popN->next;	//Set new head to old head's next
		//If head->next points to null
		if (newH == nullptr)
		{
			headLock.unlock();	//Free variables
			return false;
		}

		*data = newH->data;	//point data to newH->data
		head = newH;		//Set new head
	headLock.unlock();		//Unlock variables,
	free(popN);				//Free memory of popN
	return true;
}

int ga_queue::get_count() const
{
	// TODO:
	// Get the number of elements currently in the queue.


	//My code

	//Loop through next values of node starting from tail, 
	//increment count until ptr reaches null, 
	//return count.
	int count = 0;
	Node* ptr = head;
	while (ptr->next)
	{
		Node* n = ptr->next;
		ptr = n;

		count += 1;
	}

	return count;
}
