// readingList.cpp

#include "readingList.h"
#include <algorithm>

using namespace std;

int ReadingList::size() const { return theSize; }

ReadingList::ReadingList() : theSize(0) {}

void ReadingList::add(Book b) {
  // Find the appropriate place to insert the new book to maintain sorted order.
  auto it = std::find_if(books.begin(), books.end(), [&b](const Book &a) {
    return a.getID() >= b.getID();  // We want to find the first book that should come after the new book.
  });

  // Only add the book if it is not already in the list.
  if (it == books.begin() || prev(it)->getID() != b.getID()) {
    books.insert(it, b);
    theSize++;
  }
}
// void ReadingList::add(Book b) {
//   // Find the appropriate place to insert the new book to maintain sorted order.
//   auto it = std::find_if(books.begin(), books.end(), [&b](const Book &a) {
//     return a.getID() > b.getID();  // We want to find the first book that should come after the new book.
//   });

//   // Only add the book if it is not already in the list.
//   if (it == books.begin() || prev(it)->getID() != b.getID()) {
//     books.insert(it, b);
//     theSize++;
//   }
// }

void ReadingList::remove(std::string bid) {
  for (auto it = books.begin(); it != books.end();) {
    if (it->getID() == bid) {
      it = books.erase(it);
      theSize--;
    } else {
      ++it;
    }
  }
}

//Find method for const objects
ReadingList::const_iterator ReadingList::find(std::string bookID) const {
  return std::find_if(books.cbegin(), books.cend(),
                      [&](const Book &b) { return b.getID() == bookID; });
}

//Find method for non-const objects
ReadingList::iterator ReadingList::find(std::string bookID) {
  return std::find_if(books.begin(), books.end(),
                      [&](const Book &b) { return b.getID() == bookID; });
}

bool ReadingList::contains(std::string bookID) const {
  return find(bookID) != books.end();
}

std::istream &operator>>(std::istream &in, ReadingList &readingList) {
  readingList = ReadingList();
  Book b;
  while (in >> b) {
    if (b.getID() != "**END**") {
      readingList.add(b);
    } else {
      break;
    }
  }
  return in;
}

std::ostream &operator<<(std::ostream &out, const ReadingList &readingList) {
  for (const Book &b : readingList) {
    out << b << endl;
  }
  return out;
}

bool operator==(const ReadingList &left, const ReadingList &right) {
  return (left.size() == right.size()) &&
         std::equal(left.begin(), left.end(), right.begin());
}
