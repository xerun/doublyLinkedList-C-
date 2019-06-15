#pragma once
#ifndef SRC_LINE_H_
#define SRC_LINE_H_
#include <iostream>

class Line
{
private:
	char* linePtr; // stores a pointer to the first character in a dynamically created array
					// of char, effectively representing the underlying line of text
	int lineLength; // Length of this line
	int capacity; // Storage capacity of this line

public:
	Line(const char* text); // Constructs this line, assigning linePtr a pointer to a deep
							// copy of the supplied C-string text
	Line(const Line&); // Copy Constructor
	virtual ~Line(); // Deconstructor
	const Line& operator =(const Line& rhs); // Assignment operator overload

	const char* cstr() const; // Returns C-style version of this line
	int length() const; // Returns length of this line
	bool empty() const; // return whether this line is empty
	bool full() const; // returns whether this line is full
	int getCapacity() const; // returns capacity of this line
	void resize(); // Doubles the capacity if this line is full
	void push_back(const char& ch); // Appends ch to the end of this line
	void pop_back(); // removes the last character in this line
	
	friend std::ostream& operator<<(std::ostream& out, const Line& line); //Overloads operator << as a friend
	friend std::istream& operator>>(std::istream& in, Line& line); //Overloads operator >> as a friend
};
bool operator== (const Line&, const Line&); //Overloads a non member operator ==
bool operator!= (const Line&, const Line&); //Overloads a non member operator !=
#endif /* SRC_LINE_H_ */