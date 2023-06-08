#ifndef READINGLIST_H_
#define READINGLIST_H_

#include <initializer_list>
#include <iostream>
#include <list>
#include <string>

#include "book.h"

class ReadingList {
public:
  typedef std::list<Book>::iterator iterator;
  typedef std::list<Book>::const_iterator const_iterator;

  ReadingList();

  // New constructor implementation
  template <typename Iterator>
  ReadingList(Iterator begin, Iterator end) : theSize(std::distance(begin, end)) {
    books.assign(begin, end);
    books.sort([](const Book& a, const Book& b) {
      return a.getID() < b.getID();
    });
  }

  int size() const;
  void add(Book b);
  void remove(std::string bid);
  bool contains(std::string bookID) const;

  // Constant and non-constant versions of begin and end
  iterator begin() { return books.begin(); }
  iterator end() { return books.end(); }
  iterator find(std::string bookID);
  const_iterator begin() const { return books.begin(); }
  const_iterator find(std::string bookID) const;
  const_iterator end() const { return books.end(); }

private:
  std::list<Book> books;
  int theSize;

public:
  bool sanityCheck() const;
};

std::istream &operator>>(std::istream &in, ReadingList &readingList);
std::ostream &operator<<(std::ostream &out, const ReadingList &readingList);
bool operator==(const ReadingList &left, const ReadingList &right);

#endif 