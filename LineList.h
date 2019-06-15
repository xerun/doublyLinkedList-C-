#pragma once
#ifndef SRC_LINELIST_H_
#define SRC_LINELIST_H_
#include "Line.h"
//template<typename Line>
class LineList
{
	struct  Node
	{
	public:
		Line data; // this node's data object
		Node* prev; // pointer to previous node
		Node* next; // pointer to next node
		Node(const Line& ln, Node* prv, Node* nxt) :data(ln), prev(prv), next(nxt) {} // Constructor
	};
	private:	
		int theSize; // Number of elements in this list
		Node* head; // Pointer to the first node in this list
		Node* tail; // Pointer of the last node in this list
		Node* newNode; // A private member type (an inner class)

	public:
		LineList(); // Default constructor
		LineList(const LineList& rhs); // copy constructor
		const LineList& operator=(const LineList& rhs); //copy assignment
		virtual ~LineList(); //destructor

		void push_front(const Line& line); // Inserts line at the front of the list
		void push_back(const Line& line); // inserts line at the end of the list
		void pop_front(); // remove the first node in the list
		void pop_back(); // remove the last node in the list
		int size() const; // return the size of the list
		bool empty() const; // return whether this list is empty
		void insert(const Line& line, int k); // inserts a new line at position k in the list
		void remove(int k); // removes node at posistion k in the list
		Line get(int k) const; // returns the list at position k in the list
		void print(); // print the list
};

#endif /* SRC_LINELIST_H_ */