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


	/*
	headLock.lock(); 
	tailLock.lock();
	*/
}

ga_queue::~ga_queue()
{
	// TODO:
	// Free any resources held by the queue.
	// See https://www.research.ibm.com/people/m/michael/podc-1996.pdf

	
	Node* ptr = head;
	while (ptr)
	{
		Node* n = ptr->next;
		free(ptr->data);
		free(ptr);
		ptr = n;
	}
	
	//free(tail);


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

	//Create new node, set data to parameter data, and set its next to null
	Node* newN = new Node();
	newN->data = data;
	newN->next = nullptr;

	//Using tailLock to get tail, setting its next to new node, setting new node as tail, and than locking tailLock
	tailLock.lock();
		tail->next = newN;
		tail = newN;
	tailLock.unlock();

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

	//Get headLock to access head
	headLock.lock();
		Node* popN = head;
		Node* newH = popN->next;
		//If head->next points to null
		if (newH == nullptr)
		{
			headLock.unlock();
			return false;
		}
		//Set new head
		head = newH;

	headLock.unlock();	//Unlock headLock,
	*data = popN->data;	//point data to popN->data
	free(popN);			//Free memory of popN
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
