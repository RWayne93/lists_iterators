#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>

/**
 * An ebook.
 */
class Book {
private:
  std::string title;
  std::string id;
  std::string authorName;
public:

  Book() {}

  Book (std::string theId, std::string authorInfo, std::string theTitle);

  std::string getID() const  {return id;}
  void setID (std::string ID) {id = ID;}

  std::string getTitle() const {return title;}
  void setTitle (std::string theTitle)  {title = theTitle;}

  std::string getAuthor() const  {return authorName;}
  void setAuthor (std::string name) {authorName = name;}

  bool operator< (const Book&) const;
  bool operator== (const Book&) const;
};

std::ostream& operator<< (std::ostream& out, const Book& b);

std::istream& operator>> (std::istream& in, Book& b);

#endif
