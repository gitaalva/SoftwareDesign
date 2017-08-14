

/* -*- C++ -*- */

// Use a Queue to print a name.
#include <iostream>
#include <assert.h>
#include <cstdio>
#include "LQueue.h"

typedef LQueue<char> LQUEUE;

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

void 
testConstructors (LQUEUE **queues)
{
  std::cerr << "--Testing constructors (4 total) and enqueues (7 total).--\n\n";

  std::cerr << "First test. Basic constructors: ";

  queues[CAR] = new LQUEUE (10);
  queues[BIKE] = new LQUEUE (20);

  std::cerr << "done.\n";
  std::cerr << "Second test. Enqueue 'car': ";

  queues[CAR]->enqueue ('c');
  queues[CAR]->enqueue ('a');
  queues[CAR]->enqueue ('r');
  
  std::cerr << "done.\n";

  std::cerr << "Third test. Enqueue 'bike': ";

  queues[BIKE]->enqueue ('b');
  queues[BIKE]->enqueue ('i');
  queues[BIKE]->enqueue ('k');
  queues[BIKE]->enqueue ('e');

  std::cerr << "done.\n\n";

  std::cerr << "We will see if enqueues were successful during dequeue tests.\n\n";

  std::cerr << "Fourth test. Copy constructors: ";
  queues[COPY_CAR] = new LQUEUE (*queues[CAR]);
  std::cerr << "car copied. ";
  queues[COPY_BIKE] = new LQUEUE (*queues[BIKE]);
  std::cerr << "bike copied. ";

  std::cerr << "\n\n--Constructor/enqueue tests have finished--\n";
}

void 
testDequeue (LQUEUE **queues)
{
  std::cerr << "\n--Testing dequeue--\n";

  LQUEUE car (*queues[CAR]);
  LQUEUE bike (*queues[BIKE]);
  LQUEUE copycar (*queues[COPY_CAR]);
  LQUEUE copybike (*queues[COPY_BIKE]);

  std::cerr << "\nFirst, testing sizes.\n";
  std::cerr << "Car length should be 3. Queue length is "
            << car.size () << "\n";
  std::cerr << "Bike length should be 4. Queue length is "
            << bike.size () << "\n";
  std::cerr << "Copy Car length should be 3. Queue length is "
            << copycar.size () << "\n";
  std::cerr << "Copy Bike length should be 4. Queue length is "
            << copybike.size () << "\n";

  std::cerr << "\nNow, testing contents via dequeue.\n";
  std::cerr << "The following should read 'car'. car = '";

  while (car.size ())
    {
      std::cerr << car.front ();
      car.dequeue ();
    }

  std::cerr << "'\n";

  std::cerr << "The following should read 'bike'. bike = '";

  while (bike.size ())
    {
      std::cerr << bike.front ();
      bike.dequeue ();
    }

  std::cerr << "'\n";

  std::cerr << "The following should read 'car'. car = '";

  while (copycar.size ())
    {
      std::cerr << copycar.front ();
      copycar.dequeue ();
    }

  std::cerr << "'\n";

  std::cerr << "The following should read 'bike'. bike = '";

  while (copybike.size ())
    {
      std::cerr << copybike.front ();
      copybike.dequeue ();
    }

  std::cerr << "'\n";


  std::cerr << "\n--Dequeue tests have finished--\n";
  std::cerr << "\nPress any key to continue.\n\n";
  
  getchar ();

}

void 
testIterators (LQUEUE **queues)
{
  std::cerr << "\n--Testing iterators--\n";

  LQUEUE *car = queues[CAR];
  LQUEUE *bike = queues[BIKE];
  LQUEUE *cars = queues[COPY_CAR];
  LQUEUE *bikes = queues[COPY_BIKE];

  std::cerr << "\nTesting begin()/rbegin(), end()/rend(), operator++, and operator-- for iterators.\n";

  std::cerr << "\nThe following should print out 'car': ";
  for (LQUEUE::iterator i (car->begin ()); i != car->end (); ++i)
    std::cerr << *i;

  std::cerr << "\nThe following should print out 'bike': "; 
  for (LQUEUE::iterator i (bike->begin ()); i != bike->end (); ++i)
    std::cerr << *i;

  std::cerr << "\nThe following should print out 'cars': ";
  for (LQUEUE::iterator i (cars->begin ()); i != cars->end (); ++i)
    std::cerr << *i;

  std::cerr << "\nThe following should print out 'bikes': "; 
  for (LQUEUE::iterator i (bikes->begin ()); i != bikes->end (); ++i)
    std::cerr << *i;

  std::cerr << "\nThe following should print out 'rac': ";
  for (LQUEUE::reverse_iterator i (car->rbegin ()); i != car->rend (); ++i)
    std::cerr << *i;

  std::cerr << "\nThe following should print out 'ekib': "; 
  for (LQUEUE::reverse_iterator i (bike->rbegin ()); i != bike->rend (); ++i)
    std::cerr << *i;

  std::cerr << "\nThe following should print out 'srac': ";
  for (LQUEUE::reverse_iterator i (cars->rbegin ()); i != cars->rend (); ++i)
    std::cerr << *i;

  std::cerr << "\nThe following should print out 'sekib': "; 
  for (LQUEUE::reverse_iterator i (bikes->rbegin ()); i != bikes->rend (); ++i)
    std::cerr << *i;

  std::cerr << "\nTesting begin(), end() and -- operator for iterators.\n";

  std::cerr << "\nThe following should print out 'rac': ";
  for (LQUEUE::iterator i (car->end ()); ; )
    {
      std::cerr << *--i;
      if (i == car->begin ())
        break;
    }

  std::cerr << "\nThe following should print out 'ekib': ";
  for (LQUEUE::iterator i (bike->end ()); ;)
    {
      std::cerr << *--i;
      if (i == bike->begin ())
        break;
    }

  std::cerr << "\nThe following should print out 'srac': ";
  for (LQUEUE::iterator i (cars->end ()); ; )
    {
      std::cerr << *--i;
      if (i == cars->begin ())
        break;
    }

  std::cerr << "\nThe following should print out 'sekib': ";
  for (LQUEUE::iterator i (bikes->end ()); ; )
    {
      std::cerr << *--i;
      if (i == bikes->begin ())
        break;
    }

  std::cerr << "\n\n--Iterator tests have finished--\n";
  std::cerr << "\nPress any key to continue.\n\n";
  
  getchar ();
}

int
main (int argc, char *argv[])
{
  // using pointers to pointers so constructors aren't
  // called until inside of the testConstructors function.

  LQUEUE ** queues = new LQUEUE *[4];

  testConstructors (queues);
   
  testDequeue (queues);

  std::cerr << "Adding an s to the 3rd and 4th queues.\n";

  queues[COPY_CAR]->enqueue ('s');
  queues[COPY_BIKE]->enqueue ('s');

  testIterators (queues);

  // clean up the queues

  delete queues[0];
  delete queues[1];
  delete queues[2];
  delete queues[3];
  delete [] queues;

  // you can comment out the following trycatch block to isolate
  // problems to the above tests (constructors, dequeues, and iterators).
  
  try
    {
      const int MAX_NAME_LEN = 80;
      LQUEUE::value_type name[MAX_NAME_LEN];

      LQUEUE q1 (MAX_NAME_LEN);
      try
        {
          LQUEUE::value_type c = q1.front ();
          std::cerr << c;
          assert (!"shouldn't be here since exception should have been thrown\n");
        }
      catch (LQUEUE::Underflow &)
        {
          std::cerr << "dequeueing from empty queue" << std::endl;
        }

      for (LQUEUE::iterator iterator (q1.begin ());
           iterator != q1.end ();
           iterator++)
        {
          assert (!"shouldn't be here since queue is empty!\n");
        }

      std::cerr << "Please enter your name..: ";
      std::cin.getline (name, MAX_NAME_LEN);
      size_t readin = std::cin.gcount () - 1;
	
      for (size_t i = 0; i < readin && !q1.is_full (); i++)
        q1.enqueue (name[i]);

      // Test the copy constructor.
      LQUEUE q2 (q1);
      LQUEUE q10 (q1);
      assert (q1 == q2);

      // Test the assignment operator
      size_t size = q2.size ();
      q1 = q2;
      assert (q1 == q2);
      assert (q1.size () == size);

      std::cerr << std::endl << "your name is..: ";
  
      for (LQUEUE::iterator iterator (q1.begin ());
           iterator != q1.end ();
           iterator++)
        {
          size--;
          std::cerr << *iterator;
        }

      assert (size == 0);

      std::cerr << std::endl;

      std::cerr << "your name is..: ";

      try
        {
          for (;;)
            {
              LQUEUE::value_type c = q1.front ();
              std::cerr << c;
              q1.dequeue ();
            }

          assert (!"shouldn't be here since exception should have been thrown\n");

        }
      catch (LQUEUE::Underflow &)
        {
          std::cerr << std::endl << "dequeueing from empty queue" << std::endl;
        }

      std::cerr << std::endl;
      assert (q1.is_empty ());
      assert (!q2.is_empty ());
      assert (q1 != q2);

      LQUEUE q6 (2);

      q6.enqueue ('a');
      q6.enqueue ('b');
      LQUEUE::value_type c = q6.front ();
      assert (c == 'a');
      q6.dequeue ();
      q6.enqueue ('c');

      size_t i = 0;

      for (LQUEUE::iterator iterator (q6.begin ());
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

      LQUEUE q7 (2);

      q7.enqueue ('a');
      q7.enqueue ('b');
      LQUEUE::value_type d = q7.front ();
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

      const LQUEUE q8 (q7);

      i = 0;
      for (LQUEUE::const_iterator iterator (q8.begin ());
           iterator != q8.end ();
           iterator++)
        {
          assert (*iterator == 'd');
          i++;
        }

      assert (i == 1);

      q7.enqueue ('A');
      q7.dequeue ();

      // Check to ensure that dequeue() updates prev_ properly.

      for (LQUEUE::reverse_iterator i (q7.rbegin ()); i != q7.rend (); ++i)
        assert (*i == 'A');

      // test for basic exception guarantees

      std::cerr << "--Testing basic exception guarantees--\n\n";
      std::cerr << "If your code doesn't leak memory in Valgrind or Purify\n"
                << "then you are doing this correctly.\n\n";

      std::cerr << "Testing copy constructor: ";

      BadAssignment<char> temp;
      LQueue< BadAssignment<char> > ba(8);
    
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
          LQueue< BadAssignment<char> > baCopy(ba);
        }
      catch (LQueue< BadAssignment<char> >::Overflow &)
        {
          std::cerr << "done.\n";
        }
      catch (std::bad_alloc &)
        {
          std::cerr << "didn't catch Overflow instead of bad_alloc.\n";
        }

      // Test the basic exception guarantees in enqueue

      std::cerr << "Testing enqueue: ";

      try
        {
          temp.data = 'r';
          ba.enqueue(temp);
        }
      catch (LQueue< BadAssignment<char> >::Overflow &)
        {
          std::cerr << "done.\n";
        }
      catch (std::bad_alloc &)
        {
          std::cerr << "didn't catch Overflow instead of bad_alloc.\n";
        }

      std::cerr << "\n--Exception guarantees tests have finished--\n\n";
    }
  catch (std::bad_alloc)
    {
      std::cerr << "allocation failed" << std::endl;
    }

  // grad students. free_list_release should delete a total of 120 nodes here.

  LQueue_Node<char>::free_list_release();
  LQueue_Node<BadAssignment<char> >::free_list_release();
    
    std::cerr << "We are done with all tests" << std::endl;
    
  return 0;	
}
