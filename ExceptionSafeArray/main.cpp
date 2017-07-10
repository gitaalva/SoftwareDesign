// Uses a Array to reverse a name and test various properties of class
// Array<>.

#include <assert.h>
#include <stdexcept>
#include <iostream>
#include <string>
#include "Array.h"

static const int INITIAL_NAME_LEN = 80;

typedef Array ARRAY;

int
main (int argc, char *argv[]) 
{
  try
    {
      std::string name;

      ARRAY a1 (INITIAL_NAME_LEN, ' ');
      size_t i;
      assert (a1.size () == INITIAL_NAME_LEN);

      std::cout << "please enter your name..: ";
      std::getline (std::cin, name);

      std::cout << "read in: " << name.length () << std::endl;

      for (i = 0; i < name.length (); ++i)
        a1.set (name[i], i);

      std::cout << "size is " << a1.size () << std::endl << "your name is..: ";

      for (i = 0; i < a1.size (); ++i)
        std::cout << a1[i];

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

      // Test the operator[] for setting and getting.
      a2[0] = 'c';
      assert (a2[0] == 'c');

      // Test for self assignment.
      a3 = a3;

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
  catch (std::out_of_range &)
    {
      std::cout.flush(); 
      std::cerr << std::endl << "index out of range" << std::endl;
    }
  catch (std::bad_alloc &)
    {
      std::cout.flush(); 
      std::cerr << "new failed" << std::endl;
    }

  return 0;     
}

