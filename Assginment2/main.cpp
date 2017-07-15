// Uses a Array to reverse a name and test various properties of class
// Array<>.

#include <assert.h>
#include <stdexcept>
#include <iostream>
#include <functional>
#include <sstream>
#include <iterator>
#include <cstdio>
#include <string>
#include "Array.h"

static const size_t INITIAL_NAME_LEN = 1;

typedef Array<char> ARRAY;

void testDefaults()
{
  ARRAY a1 (10, 'a');
  ARRAY a2 (20, 'b');
  ARRAY a3 (30, 'c');

  size_t i = 0;

  std::cout << "\n-----Entering default value tests-----\n\n";

  std::cout << "Testing defaults for a1 with defaults a (10)\n\n";

  for (i = 0; i < a1.size (); ++i)
    {
      std::cout << a1[i] << ' ';
      if (i % 10 == 9) std::cout << std::endl;
    }

  std::cout << "\nTesting defaults for a2 with defaults b (20)\n\n";

  for (i = 0; i < a2.size (); ++i)
    {
      std::cout << a2[i] << ' ';
      if (i % 10 == 9) std::cout << std::endl;
    }

  std::cout << "\nTesting defaults for a3 with defaults c (30)\n\n";

  for (i = 0; i < a3.size (); ++i)
    {
      std::cout << a3[i] << ' ';
      if (i % 10 == 9) std::cout << std::endl;
    }

  a1.set ('d',19);
  a2.set ('e',29);
  a3.set ('f',39);

  std::cout << "\n-----Performing resize tests via set-----\n\n";

  std::cout << "Testing defaults for a1 with defaults a (set 19=d) (20)\n\n";

  for (i = 0; i < a1.size (); ++i)
    {
      std::cout << a1[i] << ' ';
      if (i % 10 == 9) std::cout << std::endl;
    }

  std::cout << "\nTesting defaults for a2 with defaults b (set 29=e) (30)\n\n";

  for (i = 0; i < a2.size (); ++i)
    {
      std::cout << a2[i] << ' ';
      if (i % 10 == 9) std::cout << std::endl;
    }

  std::cout << "\nTesting defaults for a3 with defaults c (set 39=f) (40)\n\n";

  for (i = 0; i < a3.size (); ++i)
    {
      std::cout << a3[i] << ' ';
      if (i % 10 == 9) std::cout << std::endl;
    }

  std::cout << "\n----- Default values have been tested. Please review results.-----\n\n";

  std::cout << "Press any key to continue\n\n";
  getchar ();

}

void testAssignmentsAndConstructors()
{
  ARRAY a1 (10, 'a');
  ARRAY a2 (20, 'b');
  ARRAY a3 (30, 'c');
  ARRAY c1 (1, 'x');
  ARRAY c2 (1, 'y');
  ARRAY c3 (1, 'z');

  size_t i = 0;

  std::cout << "\n\n-----Performing copy constructor tests-----\n\n";

  ARRAY b1(a1);
  ARRAY b2(a2);
  ARRAY b3(a3);
  ARRAY c4 (30);
  ARRAY c5 (c4);

  std::cout << "\nTesting b1(a1). a1 contained 10 a's.\n\n";

  for (i = 0; i < b1.size (); ++i)
    {
      std::cout << b1[i] << ' ';
      if (i % 10 == 9) std::cout << std::endl;
    }

  std::cout << "\nTesting b2(a2). a2 contained 20 b's.\n\n";

  for (i = 0; i < b2.size (); ++i)
    {
      std::cout << b2[i] << ' ';
      if (i % 10 == 9) std::cout << std::endl;
    }

  std::cout << "\nTesting b3(a3). b3 contained 30 c's.\n\n";

  for (i = 0; i < b3.size (); ++i)
    {
      std::cout << b3[i] << ' ';
      if (i % 10 == 9) std::cout << std::endl;
    }

  std::cout << "\n\n-----Performing assignment operator tests-----\n\n";

  c1 = a1;
  c2 = a2;
  c3 = a3;

  std::cout << "\nTesting c1 = a1. c1 should contain 10 a's.\n\n";

  for (i = 0; i < c1.size (); ++i)
    {
      std::cout << c1[i] << ' ';
      if (i % 10 == 9) std::cout << std::endl;
    }

  std::cout << "\nTesting c2 = a2. c2 should contain 20 b's.\n\n";

  for (i = 0; i < c2.size (); ++i)
    {
      std::cout << c2[i] << ' ';
      if (i % 10 == 9) std::cout << std::endl;
    }

  std::cout << "\nTesting c3 = a3. c3 should contain 30 c's.\n\n";

  for (i = 0; i < c3.size (); ++i)
    {
      std::cout << c3[i] << ' ';
      if (i % 10 == 9) std::cout << std::endl;
    }

  std::cout << "\n*If you see an x, y, or z in the above printout,\n" <<
    "then your assignment operator is not overwriting\n" <<
    "the left hand side properly.*\n";

  std::cout << "\n----- Assignments/constructors" <<
    " have been tested. Please review results.-----\n\n";


  std::cout << "Press any key to continue\n\n";
  getchar ();
}

void testIterators()
{
  const ARRAY a1 (20,'t');
  ARRAY::const_iterator i1 = a1.begin ();
  ARRAY::const_iterator i2 = a1.end ();
  size_t i = 0;

  std::cout << "\n-----Performing iterator test.-----\n\n";
  std::cout << "Test i1 = a1.begin(). Should print 20 t's.\n\n";

  for (i = 0; i1 != a1.end (); ++i1, ++i)
  {
    std::cout << *i1 << ' ';
    if (i % 10 == 9) std::cout << std::endl;
  }

  std::cout << "\nTest i2 = a1.end(). Should print 20 t's.\n\n";

  for (i = 0; i2 != a1.begin (); ++i)
  {
    std::cout << *--i2 << ' ';
    if (i % 10 == 9) std::cout << std::endl;
  }

  if (i % 10 == 9) std::cout << std::endl;

  std::cout << "\n-----Iterator tests complete. " <<
               "Please review results.\n\n";

  std::cout << "Press any key to continue\n\n";
  getchar ();


}

void testSetDefault()
{
  ARRAY a1 (10);
  ARRAY a2 (10,'e');
  ARRAY a3 (20);
  a3 = a2; // test if the assignment operator takes over the default settings

  std::cout << "\n-----Performing test for default set values.-----\n\n";

  std::fill(a1.begin (), a1.end (), 'e');
  a1.set ('u', 15);
  a2.set ('u', 15);
  a3.set ('u', 15);

  std::copy (a1.begin (),
             a1.end (),
             std::ostream_iterator<char>(std::cout, " "));

  std::cout << std::endl << std::endl;

  std::copy (a2.begin (),
             a2.end (),
             std::ostream_iterator<char>(std::cout, " "));

  std::cout << std::endl << std::endl;

  std::copy (a3.begin (),
             a3.end (),
             std::ostream_iterator<char>(std::cout, " "));

  std::cout << std::endl << std::endl
            << " * line 1: Test of set without default value, " << std::endl
	    << "           should contain 10 'e's 5 non 'e's and 1 u." << std::endl
            << " * line 2: Test of set with default value, " << std::endl
	    << "           should contain 15 'e's and 1 u." << std::endl
            << " * line 3: Test if assignment takes over the default value, " << std::endl
	    << "           should contain 15 'e's and 1 u." << std::endl
            << "\n-----test for default set values complete. " <<
    "Please review results.\n\n";

  std::cout << "Press any key to continue\n\n";
  getchar ();
}

void
testSwap (void)
{
  ARRAY a1 (10, 'a');
  ARRAY a2 (10, 'b');
  ARRAY a3 (10, 'a');
  ARRAY a4 (10, 'b');

  assert (a1 == a3);
  assert (a2 == a4);
  a1.swap (a2);
  assert (a1 == a4);
  assert (a2 == a3);
}

int main (int, char *[])
{
  try
    {
      std::string name;
      const ARRAY::value_type DEFAULT_VALUE = 'D';

      testDefaults ();
      testAssignmentsAndConstructors ();
      testIterators ();
      testSetDefault ();
      testSwap ();

      ARRAY a1 (INITIAL_NAME_LEN, DEFAULT_VALUE);
      size_t i;
      assert (a1.size () == INITIAL_NAME_LEN);

      std::cout << "please enter your name..: ";
      std::getline (std::cin, name);

      assert (a1.size () == 1);
      std::cout << "size is " << a1.size () << std::endl
                << "read in: " << name.length () << std::endl;

      for (i = 0; i < name.length (); ++i)
        // Note that this call should trigger a resize () whenever i exceeds a1.size().
        a1.set (name[i], i);

      // Test to make sure that a1.size () is assigned properly after
      // the series of set () calls.
      assert (a1.size () == name.length ());

      std::cout << "size is " << a1.size () << std::endl << "your name is..: ";

      for (i = 0; i < a1.size (); ++i)
        std::cout << a1[i];

      std::cout << std::endl << "your name is..: ";

      for (ARRAY::iterator iterator (a1.begin ());
           iterator != a1.end ();
           iterator++)
        std::cout << *iterator;

      std::cout << std::endl;

      // Test initialization with the copy constructor.
      ARRAY a2 (a1);
      ARRAY a3 (a1.size () + a2.size (), -1);

      // Test the assignment operator.
      a1 = a2;
      assert (a1.size () == a2.size ());
      assert (a1 == a2);
      assert (!(a1 != a2));

      a2 = a3;
      assert (a1.size () != a2.size ());
      assert (a1 != a2);

      // Test for self assignment.
      a3 = a3;

      // Checking for error in assignment/equality operator when
      // copying cur_size - 1 chars instead of cur_size.
      ARRAY a4 (name.length ());

      for (i = 0; i < name.length (); i++)
        a4.set (name[i], i);

      ARRAY a5 (INITIAL_NAME_LEN, DEFAULT_VALUE);
      a5 = a4;

      assert (a4 == a5);

      a4 [name.length () - 1] = 'x';
      assert (! (a4 == a5));

      std::cout << "your name backwards is..: ";

      // Note that we're "off by one here" so we'll get a range error.
      for (int j = name.length (); j >= 0; --j)
        {
          ARRAY::value_type c;

          a1.get (c, j - 1);
          std::cout << c;
        }

      std::cout << "\n";
    }
  catch (std::out_of_range &e)
    {
      std::cout.flush();
      std::cerr << std::endl << "index " << e.what () << " out of range" << std::endl;
    }
  catch (std::bad_alloc &)
    {
      std::cout.flush();
      std::cerr << "new failed" << std::endl;
    }

  return 0;
}

#if defined (__GNUC__) || defined (_MSC_VER)
template class Array<char>;
#endif /* __GNUC__ || _MSC_VER */
