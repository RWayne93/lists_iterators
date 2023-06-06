#include "unittest.h"
#include "readingList.h"
#include <algorithm>
#include <sstream>
#include <vector>
#include <list>
#include <set>
#include <array>

using namespace std;

struct Setup {
    Book b1;
    Book b2;
    Book b3;

    Book expected[3]; // expected order in which books will be stored

    Setup()
    {
        b1 = Book("etext13", "Carroll, Lewis", "The Hunting of the Snark");
        b2 = Book("etext11792", "Poe, Edgar Allan", "The Raven");
        b3 = Book("etext9038", "Twain, Mark", "The Adventures of Tom Sawyer");
		expected[0] = b2;
		expected[1] = b1;
		expected[2] = b3;
    }
};

UnitTest(testRLDefaultConstructor)
{
    ReadingList rl;
    assertThat (rl.size(), isEqualTo(0));
    assertThat (rl, isEqualTo(ReadingList()));
    assertTrue (rl.sanityCheck());
}




UnitTest(testRLConsRange)
{
    Setup s;
	vector<Book> inputv {s.b1, s.b2, s.b3};
	list<Book> inputl {s.b1, s.b2, s.b3};
	set<Book> inputs {s.b1, s.b2, s.b3};
	array<Book, 3> inputa {s.b1, s.b2, s.b3};

	// All of these constructor calls should invoke the same constructor.
    ReadingList rl(s.expected, s.expected+3);
    ReadingList rlv(inputv.begin(), inputv.end());
    ReadingList rll(inputl.begin(), inputl.end());
    ReadingList rls(inputs.begin(), inputs.end());
    ReadingList rla(inputa.begin(), inputa.end());


    assertThat (rl.size(), isEqualTo(3));
    assertThat (rl, isNotEqualTo(ReadingList()));

    assertThat(contentsOf(rl), matches(range(s.expected, s.expected+3)));
    assertThat(contentsOf(rlv), matches(range(s.expected, s.expected+3)));
    assertThat(contentsOf(rla), matches(range(s.expected, s.expected+3)));

	assertThat(rl, isEqualTo(rlv));
	assertThat(rl, isEqualTo(rll));
	assertThat(rl, isEqualTo(rls));
	assertThat(rl, isEqualTo(rla));

    assertTrue(rl.contains(s.b1.getID()));
    assertTrue(rl.contains(s.b2.getID()));
    assertTrue(rl.contains(s.b3.getID()));
    assertFalse(rl.contains(s.b1.getID() + "x"));

    assertThat(rl.find(s.b2.getID()), isEqualTo(rl.begin()));
    assertThat(rl.find(s.b3.getID()+"0"), isEqualTo(rl.end()));

    ReadingList rl2;
    rl2.add(s.b3);
    rl2.add(s.b2);
    rl2.add(s.b1);

    assertThat(rl, isEqualTo(rl2));
    
    assertTrue (rl.sanityCheck());

}




UnitTest(testRLAddDiscrete)
{
    Setup s;
    ReadingList rl;
    rl.add(s.b1);
    rl.add(s.b2);
    rl.add(s.b3);

    assertThat (rl.size(), isEqualTo(3));
    assertThat (rl, isNotEqualTo(ReadingList()));

    assertTrue(rl.contains(s.b1.getID()));
    assertTrue(rl.contains(s.b2.getID()));
    assertTrue(rl.contains(s.b3.getID()));
    assertFalse(rl.contains(s.b1.getID() + "x"));

    assertThat(rl.find(s.b1.getID()), isNotEqualTo(rl.end()));
    assertThat(rl.find(s.b2.getID()), isEqualTo(rl.begin()));
    assertThat(rl.find(s.b3.getID()+"0"), isEqualTo(rl.end()));

    assertThat(contentsOf(rl), matches(range(s.expected, s.expected+3)));

    ReadingList rl2;
    rl2.add(s.b3);
    rl2.add(s.b2);
    rl2.add(s.b1);

    assertThat(rl, isEqualTo(rl2));
    
    assertTrue (rl.sanityCheck());

}


UnitTest(testRLAddDuplicates)
{
    Setup s;
    ReadingList rl;
    rl.add(s.b3);
    rl.add(s.b2);
    rl.add(s.b1);
    rl.add(s.b2);

    assertThat (rl.size(), isEqualTo(3));
    assertThat (rl, isNotEqualTo(ReadingList()));

    assertTrue(rl.contains(s.b1.getID()));
    assertTrue(rl.contains(s.b2.getID()));
    assertTrue(rl.contains(s.b3.getID()));
    assertFalse(rl.contains(s.b1.getID() + "x"));

    assertThat(rl.find(s.b2.getID()), isEqualTo(rl.begin()));
    assertThat(rl.find(s.b3.getID()+"0"), isEqualTo(rl.end()));

    assertThat(contentsOf(rl), matches(range(s.expected, s.expected+3)));

    assertTrue (rl.sanityCheck());
}

UnitTest(testRLRemove)
{
    Setup s;
    ReadingList rl;
    rl.add(s.b1);
    rl.add(s.b2);
    rl.add(s.b3);
    rl.remove(s.b1.getID());

    assertThat (rl.size(), isEqualTo(2));
    assertThat (rl, isNotEqualTo(ReadingList()));

    assertFalse(rl.contains(s.b1.getID()));
    assertTrue(rl.contains(s.b2.getID()));
    assertTrue(rl.contains(s.b3.getID()));
    assertFalse(rl.contains(s.b1.getID() + "x"));

    assertThat(rl.find(s.b1.getID()), isEqualTo(rl.end()));
    assertThat(rl.find(s.b2.getID()), isEqualTo(rl.begin()));
    assertThat(rl.find(s.b3.getID()), isNotEqualTo(rl.end()));
    assertThat(rl.find(s.b3.getID()+"0"), isEqualTo(rl.end()));

	auto it = rl.begin();
    assertThat(*it, isEqualTo(s.b2));
	++it;
    assertThat(*it, isEqualTo(s.b3));

    assertTrue (rl.sanityCheck());
}


UnitTest(testRLAssign)
{
    Setup s;
    ReadingList rl;
    rl.add(s.b1);
    rl.add(s.b2);


    ReadingList rl2;
    ReadingList rl3(rl2 = rl);

    assertThat(rl2, isEqualTo(rl));
    assertThat(rl3, isEqualTo(rl));
    
    assertThat(rl2.size(), isEqualTo(2));
    assertThat (rl2, isNotEqualTo(ReadingList()));

    assertThat(contentsOf(rl), matches(range(s.expected, s.expected+2)));

    rl2.add(s.b3);

    assertThat(rl2, isNotEqualTo(rl));
    assertThat(rl3, isEqualTo(rl));
    
    assertThat(rl.size(), isEqualTo(2));
    assertThat(rl2.size(), isEqualTo(3));
    assertThat(rl3.size(), isEqualTo(2));
    
    assertThat (rl2, isNotEqualTo(ReadingList()));
}


UnitTest(testRLCopy)
{
    Setup s;
    ReadingList rl;
    rl.add(s.b1);
    rl.add(s.b2);


    ReadingList rl2 (rl);

    assertThat(rl2, isEqualTo(rl));
    
    assertThat(rl2.size(), isEqualTo(2));

    assertThat(contentsOf(rl), matches(range(s.expected, s.expected+2)));

    rl2.add(s.b3);

    assertThat(rl2, isNotEqualTo(rl));
    
    assertThat(rl.size(), isEqualTo(2));
    assertThat(rl2.size(), isEqualTo(3));
    
}




UnitTest(testRLInput)
{
    ReadingList rl;

    string instring = string()
        + "etext29662\tLeiber, Fritz, 1910-1992\tThe Moon is Green\n"
        + "etext1195\tJames, Henry, 1843-1916\tGlasses\n"
        + "etext14784\tWade, Mary Hazelton Blanchard, 1860-1936\tTimid Hare\n";

    istringstream in(instring);
    in >> rl;

    assertThat (rl.size(), isEqualTo(3));

    assertTrue(rl.contains("etext1195"));
    assertTrue(rl.contains("etext14784"));
    
    assertThat(rl.find("etext1195")->getAuthor(), isEqualTo("James, Henry, 1843-1916"));
    assertThat(rl.find("etext1195")->getTitle(), isEqualTo("Glasses"));
}



