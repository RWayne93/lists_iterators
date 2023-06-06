#include <cassert>
#include "readingList.h"
#include <list>

using namespace std;


bool constCheck (const Book&)
{
    return true;
}

bool constCheck (Book&)
{
    return false;
}


bool ReadingList::sanityCheck() const
{
    const unsigned& n = theSize;
    const list<Book> bookList = books;
    if (n > 1)
    {
        const_iterator start = begin();
        const_iterator next = start;
        ++next;
        while (next != end())
        {
            if (*next < *start)
                return false;
            start = next;
            next++;
        }
    }
    ReadingList& fac = (ReadingList&)(*this);
    ReadingList::iterator iter = fac.begin();
    Book s;
    decltype(*iter) x = s;
    return constCheck(x);
}

