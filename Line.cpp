#pragma warning(disable:4996)
#include "Line.h"
#include<cstring>

Line::Line(const char* text)
{
	lineLength = 0;
	capacity = sizeof(text);
	linePtr = new char[capacity];
	for (int k = 0; k < capacity + 1; ++k)
	{
		if (strlen(text) == k)
		{		
			push_back('\0');
			break;
		}
		else
		{
			push_back(text[k]);
		}
	}		
}

Line::Line(const Line& ln) :linePtr { ln.linePtr }, lineLength{ ln.lineLength }, capacity{ ln.capacity }
{ 
	*this = ln;
}

const Line& Line::operator =(const Line& rhs)
{
	// handle self-assignment
	if(this == &rhs) return *this;
	// determine size of line stored in inputted Line
	int i{ 0 };
	while (rhs.cstr()[i] != '\0') ++i;

	// create stored line array and copy inputted Lines
	linePtr = new char[i+1];
	strcpy(linePtr, rhs.linePtr);

	return *this;
}

Line::~Line()
{
	pop_back();
	linePtr = nullptr;
	delete[] linePtr;	
}

const char* Line::cstr() const
{
	// return the lines
	return linePtr;
}

int Line::length() const
{
	// return the length of the line
	return lineLength;
}

bool Line::empty() const
{
	// check if the line length is empty or not
	return lineLength == 0;
}

bool Line::full() const
{
	// check if the line is full or not
	return (getCapacity() == length());
}

int Line::getCapacity() const
{
	return capacity;
}

void Line::resize()
{
	// copy current values into a temporary array
	char* temp = new char[lineLength+1];
	for (int k = 0; k < lineLength+1; ++k)
		temp[k] = linePtr[k];

	// double the capacity and refill the values from temp array
	capacity *= 2;
	linePtr = new char[capacity];
	for (int k = 0; k < lineLength+1; ++k)
		linePtr[k] = temp[k];

	delete[] temp;
	//if (capacity < lineLength)resize();
}

void Line::push_back(const char& ch)
{
	if (full()) // check if the capacity is full
		resize(); // increase the capacity of the array
	
	linePtr[lineLength] = ch;
	if(ch != '\0')lineLength++; 
	// do not incrase the linelength 
	// if the char mark the end of line
}

void Line::pop_back()
{
	if (!empty()) // check if the line is empty
	{
		int i = 0;
		while (linePtr[i] != '\0')
		{
			linePtr[i] = '\0';
			i++;
			lineLength--;
		}
	}
}
bool operator==(const Line& line1, const Line& line2)
{
	if (strlen(line1.cstr()) == strlen(line2.cstr()))
	// enter IF condition if both line length same
	{
		for (int i = 0; i < strlen(line1.cstr()); ++i)
		// through all the character by character of each 
		// line to check if both has same character
		{
			if (line1.cstr()[i] != line2.cstr()[i]) return false;
		}
	}
	else
	{
		return false;
	}
	return true;
}

bool operator!=(const Line & line1, const Line & line2)
{
	return !(line1 == line2);
}
std::ostream& operator<<(std::ostream& out, const Line& line)
{
	// write obj to stream
	out << line.linePtr;
	return out;
}
std::istream& operator>>(std::istream& in, Line& line)
{
	// read obj from stream
	in >> line.linePtr;
	return in;
}