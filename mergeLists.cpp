#include <fstream>
#include <iostream>
#include <string>

#include "book.h"
#include "readingList.h"

using namespace std;

ReadingList readList(const string &fileName) {
  ReadingList c;
  ifstream in(fileName);
  in >> c;
  in.close();
  return c;
}

ReadingList mergeReadingLists(const ReadingList &cat1,
                              const ReadingList &cat2) {
  ReadingList result;
  ReadingList::const_iterator i = cat1.begin();
  ReadingList::const_iterator j = cat2.begin();
  while (i != cat1.end() && j != cat2.end()) {
    const Book &b1 = *i;
    const Book &b2 = *j;
    if (b1.getID() < b2.getID()) {
      result.add(b1);
      ++i;
    } else {
      result.add(b2);
      ++j;
    }
  }
  while (i != cat1.end()) {
    result.add(*i);
    ++i;
  }
  while (j != cat2.end()) {
    result.add(*j);
    ++j;
  }
  return result;
}

void mergeReadingListFiles(const string &readingListFile1,
                           const string &readingListFile2) {
  ReadingList c1, c2;
  c1 = readList(readingListFile1);
  cout << readingListFile1 << " contained " << c1.size() << " books." << endl;
  c2 = readList(readingListFile2);
  cout << readingListFile2 << " contained " << c2.size() << " books." << endl;
  ReadingList c3 = mergeReadingLists(c1, c2);
  cout << "Their merge contains " << c3.size() << " books." << endl;
  cout << c3 << flush;
}

int main(int argc, char **argv) {
  if (argc != 3) {
    cerr << "Usage: " << argv[0] << "readingListFile1 readingListFile2" << endl;
    return -1;
  }
  string file1 = argv[1];
  string file2 = argv[2];
  mergeReadingListFiles(file1, file2);
}
