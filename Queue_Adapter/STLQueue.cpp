/* -*- C++ -*- */

#if !defined (_STLQUEUE_CPP)
#define _STLQUEUE_CPP

#include "STLQueue.h"

template <typename T, typename QUEUE>
STLQueue_Adapter<T, QUEUE>::STLQueue_Adapter (size_t s) :  size_(s)
{
}

template <typename T, typename QUEUE>
STLQueue_Adapter<T, QUEUE>::STLQueue_Adapter (const STLQueue_Adapter<T, QUEUE> &rhs)
 : size_(rhs.size_), adaptee (rhs.adaptee)
{
}

template <typename T, typename QUEUE> STLQueue_Adapter<T, QUEUE> &
STLQueue_Adapter<T, QUEUE>::operator= (const STLQueue_Adapter &rhs)
{
  STLQueue_Adapter<T, QUEUE> temp(rhs);
  std::swap (rhs.size_, size_);
  std::swap (rhs.adaptee,adaptee);
}

// Place a <new_item> at the tail of the queue.  Throws the
// <Overflow> exception if the queue is full, e.g., if memory is
// exhausted.
template <typename T, typename QUEUE>
void 
STLQueue_Adapter<T, QUEUE>::enqueue (const T &new_item)
{
  if (adaptee.size() == size_) throw Overflow();
  adaptee.push(new_item);
}

// Remove the front item on the queue.  Throws the <Underflow>
// exception if the queue is empty.
template <typename T, typename QUEUE>
void 
STLQueue_Adapter<T, QUEUE>::dequeue (void)
{
  if (adaptee.empty()) throw Underflow();
  adaptee.pop();
}  

// Returns the front queue item without removing it. 
// Throws the <Underflow> exception if the queue is empty. 
template <typename T, typename QUEUE>
T 
STLQueue_Adapter<T, QUEUE>::front (void) const
{
  if (!adaptee.empty()) throw Underflow();
  return adaptee.front();
}

// = Check boundary conditions for Queue operations. 

// Returns 1 if the queue is empty, otherwise returns 0. 
template <typename T, typename QUEUE>
bool 
STLQueue_Adapter<T, QUEUE>::is_empty (void) const
{
	return adaptee.empty();
}

// Returns 1 if the queue is full, otherwise returns 0. 
template <typename T, typename QUEUE>
bool 
STLQueue_Adapter<T, QUEUE>::is_full (void) const
{
   return adaptee.size() == size_;
}

// Returns the current number of elements in the queue.
template <typename T, typename QUEUE>
size_t 
STLQueue_Adapter<T, QUEUE>::size (void) const
{
   return adaptee.size();
}

#endif /* _STLQUEUE_CPP */
