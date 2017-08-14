#include <iostream>
#include <string>
#include <queue>
#include <cstdio>
#include <assert.h>

#include "Queue.h"
#include "LQueue.h"
#include "AQueue.h"
#include "STLQueue.h"

// This part of the solution uses the Adapter pattern.  Note that
// LQUEUE_ADAPTER, AQUEUE_ADAPTER, and STLQUEUE_ADAPTER are all
// children of the Queue abstract base class.
typedef Queue_Adapter<char, LQueue<char> > LQUEUE_ADAPTER;
typedef Queue_Adapter<char, AQueue<char> > AQUEUE_ADAPTER;
typedef Queue_Adapter<char, STLQueue_Adapter<char> > STLQUEUE_ADAPTER;

typedef Queue<char> QUEUE;

// declare the classes before we define them, so we can refer
// to the class name without any problems. 

template <class T> 
class BadAssignment;

template <class T> 
class BadAssignment
{
public:
  class OutOfResources {};

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
            throw OutOfResources ();
          }
      }
    return *this;
  }

  T data;
  static size_t count;
};

template <class T> size_t BadAssignment<T>::count = 0;

static const size_t DEFAULT_QUEUE_SIZE = 100;

void testBasicFunctions ()
{
  std::cout << "--A. Testing basic functions\n\n";
  std::cout << "----1. Creating LQueue Adapter (size=10)\n";

  LQUEUE_ADAPTER lq (12);

  std::cout << "----2. Creating AQueue Adapter (size=10)\n\n";

  AQUEUE_ADAPTER aq (10);

  std::cout << "----3. Testing AQueue Adapter is_empty\n";
  std::cout << "    AQueue should be empty. AQueue is " ;
  std::cout << (aq.is_empty () ? "empty.\n\n" : "not empty.\n\n");

  std::cout << "----4. Testing LQueue Adapter is_empty\n";
  std::cout << "    LQueue should be empty. LQueue is " ;
  std::cout << (lq.is_empty () ? "empty.\n\n" : "not empty.\n\n");

  std::cout << "----5. Enqueueing AQueue Adapter\n";
  std::cout << "    AQueue is being enqueued with 'testing123'\n";

  aq.enqueue ('t');
  aq.enqueue ('e');
  aq.enqueue ('s');
  aq.enqueue ('t');
  aq.enqueue ('i');
  aq.enqueue ('n');
  aq.enqueue ('g');
  aq.enqueue ('1');
  aq.enqueue ('2');
  aq.enqueue ('3');

  std::cout << "    5a. AQueue front() should be 't'. AQueue front() is '";
  std::cout << aq.front () << "'.\n\n";

  std::cout << "----6. Enqueueing LQueue Adapter\n";
  std::cout << "    LQueue is being enqueued with 'another test'\n";

  lq.enqueue ('a');
  lq.enqueue ('n');
  lq.enqueue ('o');
  lq.enqueue ('t');
  lq.enqueue ('h');
  lq.enqueue ('e');
  lq.enqueue ('r');
  lq.enqueue (' ');
  lq.enqueue ('t');
  lq.enqueue ('e');
  lq.enqueue ('s');
  lq.enqueue ('t');

  std::cout << "    6a. LQueue front() should be 'a'. LQueue front() is '";
  std::cout << lq.front () << "'.\n\n";

  std::cout << "----7. Testing AQueue Adapter is_full\n";
  std::cout << "    AQueue should be full. AQueue is " ;
  std::cout << (aq.is_full () ? "full.\n\n" : "not full.\n\n");

  std::cout << "----8. Testing LQueue Adapter is_full\n";
  std::cout << "    LQueue shouldn't be full. LQueue is " ;
  std::cout << (lq.is_full () ? "full.\n\n" : "not full.\n\n");

  std::cout << "----9. Testing AQueue Adapter size\n";
  std::cout << "    AQueue size should be 10. AQueue size is " ;
  std::cout << aq.size () << ".\n\n";

  std::cout << "----10. Testing LQueue Adapter size\n";
  std::cout << "    LQueue size should be 12. LQueue is " ;
  std::cout << lq.size () << ".\n\n";

  
  std::cout << "----11. Testing AQueue Adapter dequeue\n";
  std::cout << "    AQueue should be 'testing123'. AQueue is '" ;

  while (!aq.is_empty ())
    {
      std::cout << aq.front ();
      aq.dequeue ();
    }

  std::cout << "'.\n\n";

  std::cout << "----12. Testing LQueue Adapter dequeue\n";
  std::cout << "    LQueue should be 'another test'. LQueue is '" ;

  while (!lq.is_empty ())
    {
      std::cout << lq.front ();
      lq.dequeue ();
    }

  std::cout << "'.\n\n";
    
  lq.enqueue('a');
  lq.enqueue('b');
  lq.enqueue('c');
   
  aq.enqueue('1');
  aq.enqueue('2');
  aq.enqueue('3');

  std::cout << "----13. Testing copy constructor\n";
  std::cout << "    13a. LQueue should be 'abc'. LQueue is '" ;

  LQUEUE_ADAPTER lq2 (lq);

  while (!lq2.is_empty ())
    {
      std::cout << lq2.front ();
      lq2.dequeue ();
    }

  std::cout << "'.\n";
  std::cout << "    13b. AQueue should be '123'. AQueue is '" ;
  
  AQUEUE_ADAPTER aq2 (aq);

  while (!aq2.is_empty ())
    {
      std::cout << aq2.front ();
      aq2.dequeue ();
    }
  std::cout << "'.\n\n";
    
  
  std::cout << "----14. Testing assignment operator\n";
  std::cout << "    14a. LQueue should be 'abc'. LQueue is '" ;

  LQUEUE_ADAPTER lq3(10);
  lq3 = lq;

  while (!lq3.is_empty ())
    {
      std::cout << lq3.front ();
      lq3.dequeue ();
    }

  std::cout << "'.\n";
  std::cout << "    14b. AQueue should be '123'. AQueue is '" ;
  
  AQUEUE_ADAPTER aq3(10);
  aq3 = aq;

  while (!aq3.is_empty ())
    {
      std::cout << aq3.front ();
      aq3.dequeue ();
    }
  std::cout << "'.\n";

  std::cout << "\n--Testing basic functions finished\n\n";

  std::cout << "  Review your results and press enter to continue.\n  ";

  getchar ();
}

void testQueueExceptions ()
{
  std::cout << "\n--B. Testing Queue Exceptions\n\n";

  LQUEUE_ADAPTER lq (10);
  AQUEUE_ADAPTER aq (1);

  std::cout << "----1. Testing enqueue on AQueue\n";
  std::cout << "    Adding 2 elements to an AQueue of max size 1.\n";
  std::cout << "      Test status: ";

  aq.enqueue('b');

  try
    {
      aq.enqueue ('b');
      std::cout << "FAIL. Didn't catch anything.\n\n";
    }
  catch (QUEUE::Overflow &)
    {
      std::cout << "SUCCESS. You correctly threw Queue::Overflow().\n\n";
    }
  catch (...)
    {
      std::cout << "FAIL. Didn't rethrow as Queue::Overflow().\n\n";
    }

  aq.dequeue ();

  std::cout << "----2. Testing dequeue\n";
  std::cout << "    2a. Removing element from empty AQueue\n";
  std::cout << "      Test status: ";

  try
    {
      aq.dequeue ();
      std::cout << "FAIL. Didn't catch anything.\n\n";
    }
  catch (QUEUE::Underflow &)
    {
      std::cout << "SUCCESS. You correctly threw Queue::Underflow().\n\n";
    }
  catch (...)
    {
      std::cout << "FAIL. Didn't rethrow as Queue::Underflow().\n\n";
    }

  std::cout << "    2b. Removing element from empty LQueue\n";
  std::cout << "      Test status: ";

  try
    {
      lq.dequeue ();
      std::cout << "FAIL. Didn't catch anything.\n\n";
    }
  catch (QUEUE::Underflow &)
    {
      std::cout << "SUCCESS. You correctly threw Queue::Underflow().\n\n";
    }
  catch (...)
    {
      std::cout << "FAIL. Didn't rethrow as Queue::Underflow().\n\n";
    }

  std::cout << "----3. Testing front\n";
  std::cout << "    3a. Checking front element in empty AQueue\n";
  std::cout << "      Test status: ";

  try
    {
      aq.front ();
      std::cout << "FAIL. Didn't catch anything.\n\n";
    }
  catch (QUEUE::Underflow &)
    {
      std::cout << "SUCCESS. You correctly threw Queue::Underflow().\n\n";
    }
  catch (...)
    {
      std::cout << "FAIL. Didn't rethrow as Queue::Underflow().\n\n";
    }

  std::cout << "    3b. Checking front element in empty LQueue\n";
  std::cout << "      Test status: ";

  try
    {
      lq.front ();
      std::cout << "FAIL. Didn't catch anything.\n\n";
    }
  catch (QUEUE::Underflow &)
    {
      std::cout << "SUCCESS. You correctly threw Queue::Underflow().\n\n";
    }
  catch (...)
    {
      std::cout << "FAIL. Didn't rethrow as Queue::Underflow().\n\n";
    }


  std::cout << "\n--Testing Queue Exceptions finished\n\n";

  std::cout << "  Review your results and press enter to continue.\n  ";

  getchar ();
}

static QUEUE *
make_queue (const std::string &queue_type)
{
  if (queue_type == "LQueue")
    return new LQUEUE_ADAPTER (DEFAULT_QUEUE_SIZE);
  else if (queue_type == "AQueue")
    return new AQUEUE_ADAPTER (DEFAULT_QUEUE_SIZE);
  else if (queue_type == "STLQueue")
    return new STLQUEUE_ADAPTER (DEFAULT_QUEUE_SIZE);
  else
    {
      assert (!"must pass LQueue, AQueue, or STLQueue!");
      return 0;
    }
}

int 
main (int argc, char *argv[])
{

  testBasicFunctions ();
  testQueueExceptions ();

  // Hold of on testing for a command line argument.

  if (argc == 1)
    {
      std::cerr << "usage: " << argv[0] << " [LQueue|AQueue|STLQueue]\n\n";
      std::cerr << "For Visual Studio Users, try changing your Project Settings\n" <<
        "to include command line arguments. This can be found in \n" <<
        "Project->Properties->Configuration Properties->Debugging->Command Arguments\n";
      
      LQueue_Node<char>::free_list_release();
      LQueue_Node<BadAssignment<char> >::free_list_release();

      
      return 1;
    }

  try
    {
      const int MAX_NAME_LEN = 80;
      QUEUE::value_type name[MAX_NAME_LEN];

      std::auto_ptr<QUEUE> q1 (make_queue (argv[1]));

      try
        {
          QUEUE::value_type c = q1->front ();
          std::cout << c;
          assert (!"shouldn't be here since exception should have been thrown\n");
        }
      catch (QUEUE::Underflow &)
        {
          std::cout << "dequeueing from empty queue" << std::endl;
        }

      std::cout << "Please enter your name..: ";
      std::cin.getline (name, MAX_NAME_LEN);
      size_t readin = std::cin.gcount () - 1;
	
      for (size_t i = 0; i < readin && !q1->is_full (); i++)
        q1->enqueue (name[i]);

      std::cout << "Your name is..: ";

      while (q1->is_empty () == 0)
        {
          std::cout << q1->front ();
          q1->dequeue ();
        }

      std::cout << std::endl;
    }
  catch (std::bad_alloc &)
    {
      std::cerr << "allocation failed" << std::endl;
    }

  // clean up the nodes

  LQueue_Node<char>::free_list_release();
  LQueue_Node<BadAssignment<char> >::free_list_release();

  // uncomment the following if you want to see a memory leak in Purify
  //char * p = new char[1000];

  return 0;	
}
