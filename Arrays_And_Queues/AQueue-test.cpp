/* -*- C++ -*- */

// Use a Queue to print a name.
#include <iostream>
#include <vector>
#include <assert.h>
#include <cstdio>
#include "AQueue.h"

// typedef AQueue<char, std::vector > AQUEUE;
typedef AQueue<char> AQUEUE;

static const size_t CAR = 0;
static const size_t BIKE = 1;
static const size_t COPY_CAR = 2;
static const size_t COPY_BIKE = 3;

// declare the classes before we define them, so we can refer
// to the class name without any problems. 

template <class T> 
class BadAssignment;

template <class T> 
class BadAssignment
{
public:
  BadAssignment ()
  {
  }

  BadAssignment (const T& new_data)
  {
    data = new_data;
  }

  BadAssignment<T> &operator = (const BadAssignment<T> &rhs)
  {
    if (this != &rhs)
    {
      // constructor will always fail, so we'll never get here, but
      // compilers would give us warnings if we don't use rhs.

      data = rhs.data;
      ++count;

      // On the 6th assignment operation, we blow up

      if (count >= 6)
      {
        throw std::bad_alloc ();
      }
    }
    return *this;
  }

  T data;
  static size_t count;
};

template <class T> size_t BadAssignment<T>::count = 0;

void testConstructors (AQUEUE ** queues)
{
  std::cout << "--Testing constructors (4 total) and enqueues (7 total).--\n\n";

  std::cout << "First test. Basic constructors: ";

  queues[CAR] = new AQUEUE (10);
  queues[BIKE] = new AQUEUE (20);

  std::cout << "done.\n";
  std::cout << "Second test. Enqueue 'car': ";

  queues[CAR]->enqueue ('c');
  queues[CAR]->enqueue ('a');
  queues[CAR]->enqueue ('r');
  
  std::cout << "done.\n";

  std::cout << "Third test. Enqueue 'bike': ";

  queues[BIKE]->enqueue ('b');
  queues[BIKE]->enqueue ('i');
  queues[BIKE]->enqueue ('k');
  queues[BIKE]->enqueue ('e');

  std::cout << "done.\n\n";

  std::cout << "We will see if enqueues were successful during dequeue tests.\n\n";

  std::cout << "Fourth test. Copy constructors: ";
  queues[COPY_CAR] = new AQUEUE (*queues[CAR]);
  std::cout << "car copied. ";
  queues[COPY_BIKE] = new AQUEUE (*queues[BIKE]);
  std::cout << "bike copied. ";

  std::cout << "\n\n--Constructor/enqueue tests have finished--\n";
}

void testDequeue (AQUEUE ** queues)
{
  std::cout << "\n--Testing dequeue--\n";

  AQUEUE car(*queues[CAR]);
  AQUEUE bike(*queues[BIKE]);
  AQUEUE copycar(*queues[COPY_CAR]);
  AQUEUE copybike(*queues[COPY_BIKE]);

  std::cout << "\nFirst, testing sizes.\n";
  std::cout << "Car length should be 3. Queue length is "
    << car.size () << "\n";
  std::cout << "Bike length should be 4. Queue length is "
    << bike.size () << "\n";
  std::cout << "Copy Car length should be 3. Queue length is "
    << copycar.size () << "\n";
  std::cout << "Copy Bike length should be 4. Queue length is "
    << copybike.size () << "\n";

  std::cout << "\nNow, testing contents via dequeue.\n";
  std::cout << "The following should read 'car'. car = '";

  while (car.size ())
  {
    std::cout << car.front ();
    car.dequeue ();
  }

  std::cout << "'\n";

  std::cout << "The following should read 'bike'. bike = '";

  while (bike.size ())
  {
    std::cout << bike.front ();
    bike.dequeue ();
  }

  std::cout << "'\n";

  std::cout << "The following should read 'car'. car = '";

  while (copycar.size ())
  {
    std::cout << copycar.front ();
    copycar.dequeue ();
  }

  std::cout << "'\n";

  std::cout << "The following should read 'bike'. bike = '";

  while (copybike.size ())
  {
    std::cout << copybike.front ();
    copybike.dequeue ();
  }

  std::cout << "'\n";


  std::cout << "\n--Dequeue tests have finished--\n";
  std::cout << "\nPress any key to continue.\n\n";
  
  getchar ();

}

void testIterators (AQUEUE ** queues)
{
  std::cout << "\n--Testing iterators--\n";

  AQUEUE *car = queues[CAR];
  AQUEUE *bike = queues[BIKE];
  AQUEUE *cars = queues[COPY_CAR];
  AQUEUE *bikes = queues[COPY_BIKE];

  std::cout << "\nTesting begin()/rbegin(), end()/rend(), operator++, and operator-- for iterators.\n";

  std::cout << "\nThe following should print out 'car': ";
  for (AQUEUE::iterator i (car->begin ()); i != car->end (); ++i)
    std::cout << *i;

  std::cout << "\nThe following should print out 'bike': "; 
  for (AQUEUE::iterator i (bike->begin ()); i != bike->end (); ++i)
    std::cout << *i;

  std::cout << "\nThe following should print out 'cars': ";
  for (AQUEUE::iterator i (cars->begin ()); i != cars->end (); ++i)
    std::cout << *i;

  std::cout << "\nThe following should print out 'bikes': "; 
  for (AQUEUE::iterator i (bikes->begin ()); i != bikes->end (); ++i)
    std::cout << *i;

  std::cout << "\nThe following should print out 'rac': ";
  for (AQUEUE::reverse_iterator i (car->rbegin ()); i != car->rend (); ++i)
    std::cout << *i;

  std::cout << "\nThe following should print out 'ekib': "; 
  for (AQUEUE::reverse_iterator i (bike->rbegin ()); i != bike->rend (); ++i)
    std::cout << *i;

  std::cout << "\nThe following should print out 'srac': ";
  for (AQUEUE::reverse_iterator i (cars->rbegin ()); i != cars->rend (); ++i)
    std::cout << *i;

  std::cout << "\nThe following should print out 'sekib': "; 
  for (AQUEUE::reverse_iterator i (bikes->rbegin ()); i != bikes->rend (); ++i)
    std::cout << *i;

  std::cout << "\n\n--Iterator tests have finished--\n";
  std::cout << "\nPress any key to continue.\n\n";
  
  getchar ();
}

void
testSwap (void)
{
  std::cout << "--Testing swap.--\n\n";

  AQUEUE a1 (10);
  AQUEUE a2 (10);
  AQUEUE a3 (10);
  AQUEUE a4 (10);

  size_t count = 0;

  while (!a1.is_full ())
    {
      a1.enqueue ('a');
      count++;
    }

  assert (count == a1.size ());

  while (!a2.is_full ())
    a2.enqueue ('b');

  a3 = a1;
  a4 = a2;

  assert (a1 == a3);  
  assert (a2 == a4);
  a1.swap (a2);
  assert (a1 == a4);
  assert (a2 == a3);
}

int
main (int argc, char *argv[])
{
  // using pointers to pointers so constructors aren't
  // called until inside of the testConstructors function.

  AQUEUE **queues = new AQUEUE *[4];

  testConstructors (queues);
  testDequeue (queues);

  std::cout << "Adding an s to the 3rd and 4th queues.\n";

  queues[COPY_CAR]->enqueue ('s');
  queues[COPY_BIKE]->enqueue ('s');

  testIterators (queues);
  // clean up the queues

  delete queues[0];
  delete queues[1];
  delete queues[2];
  delete queues[3];
  delete [] queues;

  testSwap ();

  // you can comment out the following trycatch block to isolate
  // problems to the above tests (constructors, dequeues, and iterators).

  try
    {
      const int MAX_NAME_LEN = 80;
      AQUEUE::value_type name[MAX_NAME_LEN];

      AQUEUE q1 (MAX_NAME_LEN);
      try
        {
          AQUEUE::value_type c = q1.front ();
          std::cout << c;
          assert (!"shouldn't be here since exception should have been thrown\n");
        }
      catch (AQUEUE::Underflow &)
        {
          std::cout << "dequeueing from empty queue" << std::endl;
        }

      for (AQUEUE::iterator iterator (q1.begin ());
           iterator != q1.end ();
           iterator++)
        {
          assert (!"shouldn't be here since queue is empty!\n");
        }

      std::cout << "Please enter your name..: ";
      std::cin.getline (name, MAX_NAME_LEN);
      size_t readin = std::cin.gcount () - 1;
        
      for (size_t i = 0; i < readin && !q1.is_full (); i++)
        q1.enqueue (name[i]);

      // Test the copy constructor.
      AQUEUE q2 (q1);
      AQUEUE q10 (q1);
      assert (q1 == q2);

      // Test the assignment operator
      size_t size = q2.size ();
      q1 = q2;
      assert (q1 == q2);
      assert (q1.size () == size);

      std::cout << std::endl << "your name is..: ";
  
      for (AQUEUE::iterator iterator (q1.begin ());
           iterator != q1.end ();
           iterator++)
        {
          size--;
          std::cout << *iterator;
        }

      assert (size == 0);

      std::cout << std::endl;

      std::cout << "your name is..: ";

      try
        {
          for (;;)
            {
              AQUEUE::value_type c = q1.front ();
              q1.dequeue ();
              std::cout << c;
            }

          assert (!"shouldn't be here since exception should have been thrown\n");

        }
      catch (AQUEUE::Underflow &)
        {
          std::cerr << std::endl << "dequeueing from empty queue" << std::endl;
        }

      std::cout << std::endl;
      assert (q1.is_empty ());
      assert (!q2.is_empty ());
      assert (q1 != q2);

      AQUEUE q6 (2);

      q6.enqueue ('a');
      q6.enqueue ('b');
      AQUEUE::value_type c = q6.front ();
      assert (c == 'a');
      q6.dequeue ();
      q6.enqueue ('c');

      AQUEUE qq(q6);
      assert(qq == q6);

      size_t i = 0;

      for (AQUEUE::iterator iterator (q6.begin ());
           iterator != q6.end ();
           iterator++)
        {
          if (i == 0)
            assert (*iterator == 'b');
          else if (i == 1)
            assert (*iterator == 'c');
          i++;
        }

      assert (i == 2);

      i = 0;

      AQUEUE q7 (2);

      q7.enqueue ('a');
      q7.enqueue ('b');
      AQUEUE::value_type d = q7.front ();
      assert (d == 'a');
      q7.dequeue ();
      q7.enqueue ('c');
      d = q7.front ();
      assert (d == 'b');
      q7.dequeue ();
      d = q7.front ();
      assert (d == 'c');
      q7.dequeue ();
      q7.enqueue ('d');

      const AQUEUE q8 (q7);

      i = 0;
      for (AQUEUE::const_iterator iterator (q8.begin ());
           iterator != q8.end ();
           iterator++)
        {
          assert (*iterator == 'd');
          i++;
        }

      assert (i == 1);

      // test for basic exception guarantees

      std::cout << "--Testing basic exception guarantees--\n\n";
      std::cout << "If your code doesn't leak memory in Valgrind or Purify\n"
                << "then you are doing this correctly.\n\n";

      std::cout << "Testing copy constructor: ";

      BadAssignment<char> temp;
      AQueue< BadAssignment<char> > ba(8);
    
      temp.data = 'c';
      ba.enqueue(temp);

      temp.data = 'a';
      ba.enqueue(temp);

      temp.data = 'r';
      ba.enqueue(temp);

      // makes 3 assignments so far.

      // Test the basic exception guarantees in copy constructor

      try
      {
        AQueue< BadAssignment<char> > baCopy(ba);
      }
      catch (std::bad_alloc &)
      {
        std::cout << "done.\n";
      }

      // Test the basic exception guarantees in enqueue

      std::cout << "Testing enqueue: ";

      try
      {
        temp.data = 'r';
        ba.enqueue(temp);
      }
      catch (std::bad_alloc &)
      {
        std::cout << "done.\n";
      }

      std::cout << "\n--Exception guarantees tests have finished--\n\n";
    }
  catch (std::bad_alloc &)
    {
      std::cerr << "allocation failed" << std::endl;
    }

  return 0;     
}
