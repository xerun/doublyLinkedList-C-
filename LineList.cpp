#include "LineList.h"
#include<iostream>

using namespace std;

LineList::LineList() :theSize{ 0 }, head(nullptr), tail(nullptr), newNode(nullptr) {}

LineList::LineList(const LineList& rhs) : theSize{ rhs.theSize }, head(rhs.head), tail(rhs.tail), newNode(rhs.newNode)
{
	if (rhs.empty()) return;
	head = new Node(rhs.head->data, nullptr, nullptr);
	tail = new Node(rhs.tail->data, nullptr, nullptr);
	Node* current = rhs.head->next;
	Node* last = head;
	while (current != nullptr)
	{
		last->next = new Node(current->data, nullptr, nullptr);
		last = tail->next;
		current = current->next;
	}
	
	theSize = rhs.theSize;
}

LineList::~LineList()
{
	while (head)
	{
		Node* temp(head);
		head = head->next;
		delete temp;
	}
}

const LineList& LineList::operator=(const LineList& rhs)
{
	if (this == &rhs)     // in case of self-assignment
		return *this;

	delete head;
	delete tail;
	theSize = 0;

	if (rhs.theSize == 0) {
		return *this;
	}
	else                    // similar to copy constructor
	{
		theSize = rhs.theSize;
		head = new Node(*rhs.head);
		Node* curr = rhs.head->next;
		Node* prev = head;
		while (curr != nullptr)
		{
			prev->next = new Node(*curr);
			prev = prev->next;
			curr = curr->next;
		}
		tail = prev;
		delete curr;
		delete prev;
	}
	return *this;
}

void LineList::push_front(const Line& line)
{
	head = new Node(line, nullptr, head);
	if (head->next)
		head->next->prev = head;
	if (empty())
		tail = head;

	theSize++;
}

void LineList::push_back(const Line& line)
{
	tail = new Node(line, tail, nullptr);
	if (tail->prev)
		tail->prev->next = tail;
	if (empty())
		head = tail;

	theSize++;
}

void LineList::pop_front()
{
	if (empty())
		throw("LineList : list empty");
	Node* temp(head);
	Line data(head->data);
	head = head->next; // move head pointer to 2nd node
	if (head != nullptr)
		head->prev = nullptr; // remove the link to previous node

	delete temp; // delete the first node from memory
	theSize--; // update the size of the list
}

void LineList::pop_back()
{
	if (empty())
		throw("LineList : list empty");
	Node* temp(tail);
	Line data(tail->data);
	tail = tail->prev; // move last pointer to 2nd last node
	if (tail)
		tail->next = nullptr; // remove link to of 2nd last node with last node

	delete temp; // delete the last node
	theSize--; // update the size of the list
}

int LineList::size() const
{
	return theSize;
}

bool LineList::empty() const
{
	return (!head || !tail);
}

void LineList::insert(const Line& line, int k)
{
	struct Node** current = &head;

	if (k < 1 || k > theSize + 1) 
		// This condition to check whether 
		//the k position given is valid or not.
		cout << "Invalid position!" << endl;
	else {		
		while (k--) { // Keep looping until the k position is zero 
			if (k == 0) {
				// adding Node at required position 
				// making the new Node to point to  
				// the old Node at the same position 
				Node* temp = new Node(line,nullptr, *current);

				// Changing the pointer of the Node previous  
				// to the old Node to point to the new Node 
				*current = temp;
			}
			else
				// Assign double pointer variable to point to the  
				// pointer pointing to the address of next Node  
				current = &(*current)->next;
		}
		theSize++;
	}
}

void LineList::remove(int k)
{
	struct Node* current;
	int i;

	current = head;
	for (i = 1; i < k && current != nullptr; i++)
	{
		current = current->next;
	}

	if (k == 1)
	// if the is the first poisition then pop first node
	{
		pop_front();
	}
	else if (current == tail)
	// if it is the last position of the node then pop it
	{
		pop_back();
	}
	else if (current != nullptr)
	{
		current->prev->next = current->next;
		current->next->prev = current->prev;

		delete current; // delete the n node
		theSize--;
	}
	else
	{
		cout << "Invalid position!\n" << endl;
	}
}

Line LineList::get(int k) const
{
	struct Node* current = head;
	int count = 0;
	while (current != nullptr)
	{
		count++;
		if (count == k)
			return(current->data); // if line is found return it
		
		current = current->next;
	}
	return nullptr;         // otherwise, return null pointer
}

void LineList::print()
{
	Node* point = head;
	int line = 1;
	while (point != nullptr)
	{
		if(line < 10)
			cout << "( " << line << ") " << point->data << endl;
		else
			cout << "(" << line << ") " << point->data << endl;
		point = point->next;
		line++;
	}
}