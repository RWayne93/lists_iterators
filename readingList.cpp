/*
 * readingList.cpp
 *
 *  Created on: May 11, 2021
 *      Author: zeil
 */

#include "readingList.h"
#include <algorithm>

using namespace std;

/**
 * A list of books, identified by Gutenberg ID.
 */



/**
 * Check to see if a book is contained in the reading list.
 *
 * @param bookID the ID string of a potential book
 * @returns true iff a book with that ID is in the reading list.
 */
bool ReadingList::contains(std::string bookID) const
{
	return find(bookID) != books.end();
}


/**
 * Read a reading list from the input stream, terminating at
 * end of stream or at a book with ID "**END**".
 *
 * @param in the stream to read from.
 * @param readingList the reading list variable to hold the input.
 * @return the stream from which the data was read.
 */
std::istream &operator>>(std::istream &in, ReadingList &readingList)
{
	readingList = ReadingList();
	Book b;
	while (in >> b)
	{
		if (b.getID() != "**END**")
		{
			readingList.add(b);
		}
		else
		{
			break;
		}
	}
	return in;
}

/**
 * Write a reading list to an output stream.
 *
 * @param out the stream to print to.
 * @param readingList the reading list to be printed.
 * @return the stream to which the data was written.
 *
 */
std::ostream &operator<<(std::ostream &out, const ReadingList &readingList)
{
	for (const Book &b : readingList)
	{
		out << b << endl;
	}
	return out;
}

/**
 * Compare two reading lists.
 * @param left a reading list
 * @param right a reading list
 * @return True iff both reading lists are of the same length and all corresponding
 *    elements are equal.
 */
bool operator==(const ReadingList &left, const ReadingList &right)
{
	if (left.size() != right.size())
		return false;
	else
	{
		auto it1 = left.begin();
		auto it2 = right.begin();
		while (it1 != left.end())
		{
			if (!(*it1 == *it2))
				return false;
			++it1;
			++it2;
		}
		return true;
	}
}
