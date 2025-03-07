/**
	CS280 linked list header file
	@file linked-list.h
	@author Sam Micka
	@version 9/11/2020
*/
#ifndef LL_H_
#define LL_H_
#include <iostream>
using namespace std;

// must use this struct
struct city
{
	string name;
	string message;
	city* next;
	city* previous;
};

class linkedList {
private:
	city* head;
	city* tail;
public:
	linkedList(); //constructor
	void addCity(string prev, string name); //method for inserting a new node
	void deleteCity(string name); //method for removing a node
	void sendMessage(string message, string cityName); //message function
	void deleteList(); //method to delete all of the cities you've created
	void printList(); // method (already implemented) that will print the cities
	void printListBack(); // method for printing the list backwards (you implement)
};

// Add your implementations for each member function below here (above the endif)
linkedList::linkedList()
{
	this->head = NULL;
	this->tail = NULL;
}

void linkedList::addCity(string prev, string name)
{
	city* currentNode = head;
	if(head == NULL && tail == NULL)
	{
		city* newNode = new city();
		newNode->name = name;
		newNode->previous = NULL;
		newNode->next = NULL;
		this->head = newNode;
		this->tail = newNode;
		return;
	}
	while(currentNode != NULL)
	{
		if(currentNode->name == prev)
		{
			city* newNode = new city();
			newNode->name = name;
			// cout << currentNode->previous << endl;
			if(currentNode->next == NULL)
			{
				// cout << "First" << endl;
				this->tail = newNode;
				currentNode->next = newNode;
				newNode->previous = currentNode;
				newNode->next = NULL;
			}else if(currentNode->previous == NULL)
			{
				// cout << "second" << endl;
				// this->head = newNode;
				newNode->next = currentNode->next;
				currentNode->next->previous = newNode;
				currentNode->next = newNode;
				newNode->previous = currentNode;
			}else
			{
				// cout << "third" << endl;
				// cout << currentNode->previous << endl;
				newNode->previous = currentNode;
				newNode->next = currentNode->next;
				currentNode->next->previous = newNode;
				currentNode->next = newNode;
				// cout << currentNode->previous << endl;
			}
			return;
		}
		currentNode = currentNode->next;
	}
}

void linkedList::deleteCity(string name)
{
	city* currentNode = head;
	while(currentNode != NULL)
	{
		if(currentNode->name == name)
		{
			if(currentNode->previous == NULL)
			{
				currentNode->next->previous = NULL;
				this->head = currentNode->next;
				delete currentNode;
				return;
			}else if(currentNode->next == NULL)
			{
				currentNode->previous->next = NULL;
				this->tail = currentNode->previous;
				delete currentNode;
				return;
			}
			currentNode->next->previous = currentNode->previous;
			currentNode->previous->next = currentNode->next;
			delete currentNode;
			return;
		}
		currentNode = currentNode->next;
	}
}

void linkedList::sendMessage(string message, string cityName)
{
	city* currentNode = head;
	while(head != NULL)
	{
		if(currentNode->name == cityName)
		{
			currentNode->message = message + " from: " + cityName;
			if(currentNode->previous != NULL)
			{
				currentNode->previous->message = message + " from: " + cityName;
			}
			if(currentNode->next != NULL)
			{
				currentNode->next->message = message + " from: " + cityName;
			}
			return;
		}
		currentNode = currentNode->next;
	}
}

void linkedList::deleteList()
{
	city* currentNode = head->next;

	while(true)
	{
		// cout << "something" << currentNode->name << endl;
		delete currentNode->previous;
		if(currentNode->next == NULL)
		{
			break;
		}
		currentNode = currentNode->next;	
	}
}

void linkedList::printList()
{
	city* currentNode = head;
	while(currentNode != NULL)
	{
		cout << currentNode->name << " messages: " << currentNode->message << endl;
		currentNode = currentNode->next;
	}
}

void linkedList::printListBack()
{
	city* currentNode = tail; 
	while(currentNode != NULL)
	{
		cout << currentNode ->name << " messages: " << currentNode->message << endl;
		currentNode = currentNode->previous;
	}
}

#endif
