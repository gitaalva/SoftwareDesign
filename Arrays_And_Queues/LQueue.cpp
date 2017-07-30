
#if !defined (_LQUEUE_CPP)
#define _LQUEUE_CPP

#include <functional>
#include <algorithm>
#include "LQueue.h"

/* static */
template <typename T> LQueue_Node<T> *
LQueue_Node<T>::free_list_ = 0;

// Allocate a new <LQueue_Node>, trying first from the
// <free_list_> and if that's empty try from the global <::operator
// new>.

template <typename T> void *
LQueue_Node<T>::operator new (size_t)
{
}

// Return <ptr> to the <free_list_>.

template <typename T> void
LQueue_Node<T>::operator delete (void *ptr)
{
}

// Returns all dynamic memory on the free list to the free store.

template <typename T> void
LQueue_Node<T>::free_list_release (void)
{
}

// Preallocate <n> <LQueue_Nodes> and store them on the
// <free_list_>.

template <typename T> void
LQueue_Node<T>::free_list_allocate (size_t n)
{
}

template <typename T>
LQueue_Node<T>::LQueue_Node (LQueue_Node<T> *next,
                             LQueue_Node<T> *prev)
  : next_ (next),
    prev_ (prev)
{
  next_->prev_ = this;
  prev_->next_ = this;
}

template <typename T>
LQueue_Node<T>::LQueue_Node (void)
  // this is helpful to implement the dummy node in a concise way.
  : next_ (this),
    prev_ (this)
{
}

template <typename T>
LQueue_Node<T>::~LQueue_Node (void)
{
  next_->prev_ = prev_;
  prev_->next_ = next_;
}

// Returns the current size.
template<typename T, typename LQUEUE_NODE> size_t
LQueue<T, LQUEUE_NODE>::size (void) const
{
  return count_;
}

// Constructor.

template<typename T, typename LQUEUE_NODE> 
LQueue<T, LQUEUE_NODE>::LQueue (size_t size_hint)
  // Initialize fields here.
  : tail_ (0),
    count_ (0)
{
}

template<typename T, typename LQUEUE_NODE> void
LQueue<T, LQUEUE_NODE>::swap (LQueue<T, LQUEUE_NODE> &new_queue)
{
}

// Copy constructor.

template <typename T, typename LQUEUE_NODE>
LQueue<T, LQUEUE_NODE>::LQueue (const LQueue<T, LQUEUE_NODE> &rhs)
  // Initialize fields here.
  : tail_ (0), // tail_ will be set correctly by swap().
    count_ (0) // count_ will be set correctly by swap().
{
}

// Assignment operator.
template <typename T, typename LQUEUE_NODE> LQueue<T, LQUEUE_NODE> &
LQueue<T, LQUEUE_NODE>::operator= (const LQueue<T, LQUEUE_NODE> &rhs) 
{
}

// Perform actions needed when queue goes out of scope.

template <typename T, typename LQUEUE_NODE>
LQueue<T, LQUEUE_NODE>::~LQueue (void)
{
}

// Compare this queue with <rhs> for equality.  Returns true if the
// size()'s of the two queues are equal and all the elements from 0
// .. size() are equal, else false.

template <typename T, typename LQUEUE_NODE> bool 
LQueue<T, LQUEUE_NODE>::operator== (const LQueue<T, LQUEUE_NODE> &rhs) const
{
}

// Compare this queue with <rhs> for inequality such that <*this> !=
// <s> is always the complement of the boolean return value of
// <*this> == <s>.

template <typename T, typename LQUEUE_NODE> bool 
LQueue<T, LQUEUE_NODE>::operator!= (const LQueue<T, LQUEUE_NODE> &rhs) const
{
}

// Returns true if the queue is empty, otherwise returns false.

template <typename T, typename LQUEUE_NODE> bool
LQueue<T, LQUEUE_NODE>::is_empty (void) const 
{
}

// Returns true if the queue is full, otherwise returns false.

template <typename T, typename LQUEUE_NODE> bool
LQueue<T, LQUEUE_NODE>::is_full (void) const 
{
}

// Place a <new_item> at the tail of the queue.  Throws
// the <Overflow> exception if the queue is full.

template <typename T, typename LQUEUE_NODE> void
LQueue<T, LQUEUE_NODE>::enqueue (const T &new_item)
{
}

// Remove the front item on the queue without checking if the queue is empty.

template <typename T, typename LQUEUE_NODE> void
LQueue<T, LQUEUE_NODE>::dequeue_i (void)
{
}

// Throws the <Underflow> exception if the queue is empty. 
template <typename T, typename LQUEUE_NODE> void
LQueue<T, LQUEUE_NODE>::dequeue (void)
{
}

// Returns the front queue item without removing it. 
// Throws the <Underflow> exception if the queue is empty. 

template <typename T, typename LQUEUE_NODE> T 
LQueue<T, LQUEUE_NODE>::front (void) const
{
}

// Get an iterator to the begining of the queue
template <typename T, typename LQUEUE_NODE> typename LQueue<T, LQUEUE_NODE>::iterator
LQueue<T, LQUEUE_NODE>::begin (void)
{
}

// Get an iterator pointing past the end of the queue
template <typename T, typename LQUEUE_NODE> typename LQueue<T, LQUEUE_NODE>::iterator
LQueue<T, LQUEUE_NODE>::end (void)
{
}

// Get an iterator to the begining of the queue
template <typename T, typename LQUEUE_NODE> typename LQueue<T, LQUEUE_NODE>::const_iterator
LQueue<T, LQUEUE_NODE>::begin (void) const
{
}

// Get an iterator pointing past the end of the queue
template <typename T, typename LQUEUE_NODE> typename LQueue<T, LQUEUE_NODE>::const_iterator
LQueue<T, LQUEUE_NODE>::end (void) const
{
}

// Get an iterator to the begining of the queue
template <typename T, typename LQUEUE_NODE> typename LQueue<T, LQUEUE_NODE>::reverse_iterator
LQueue<T, LQUEUE_NODE>::rbegin (void)
{
}

// Get an iterator pointing past the end of the queue
template <typename T, typename LQUEUE_NODE> typename LQueue<T, LQUEUE_NODE>::reverse_iterator
LQueue<T, LQUEUE_NODE>::rend (void)
{
}

// Get an iterator to the begining of the queue
template <typename T, typename LQUEUE_NODE> typename LQueue<T, LQUEUE_NODE>::const_reverse_iterator
LQueue<T, LQUEUE_NODE>::rbegin (void) const
{
}

// Get an iterator pointing past the end of the queue
template <typename T, typename LQUEUE_NODE> typename LQueue<T, LQUEUE_NODE>::const_reverse_iterator
LQueue<T, LQUEUE_NODE>::rend (void) const
{
}

template <typename T, typename LQUEUE_NODE> T &
LQueue_Iterator<T, LQUEUE_NODE>::operator* (void)
{
}

template <typename T, typename LQUEUE_NODE> const T &
LQueue_Iterator<T, LQUEUE_NODE>::operator* (void) const
{
}

template <typename T, typename LQUEUE_NODE> LQueue_Iterator<T, LQUEUE_NODE> &
LQueue_Iterator<T, LQUEUE_NODE>::operator++ (void) 
{
}

// Post-increment.
template <typename T, typename LQUEUE_NODE> LQueue_Iterator<T, LQUEUE_NODE> 
LQueue_Iterator<T, LQUEUE_NODE>::operator++ (int) 
{
}

template <typename T, typename LQUEUE_NODE> LQueue_Iterator<T, LQUEUE_NODE> &
LQueue_Iterator<T, LQUEUE_NODE>::operator-- (void)
{
}

// Post-increment.
template <typename T, typename LQUEUE_NODE> LQueue_Iterator<T, LQUEUE_NODE> 
LQueue_Iterator<T, LQUEUE_NODE>::operator-- (int) 
{
}

template <typename T, typename LQUEUE_NODE> bool
LQueue_Iterator<T, LQUEUE_NODE>::operator== (const LQueue_Iterator<T, LQUEUE_NODE> &rhs) const
{
}

template <typename T, typename LQUEUE_NODE> bool
LQueue_Iterator<T, LQUEUE_NODE>::operator!= (const LQueue_Iterator<T, LQUEUE_NODE> &rhs) const
{
  // implement != in terms of ==
  return !(*this == rhs);
}

template <typename T, typename LQUEUE_NODE>
LQueue_Iterator<T, LQUEUE_NODE>::LQueue_Iterator (LQUEUE_NODE *pos)
  : pos_ (pos)
{
}

template <typename T, typename LQUEUE_NODE> const T &
Const_LQueue_Iterator<T, LQUEUE_NODE>::operator* (void) const
{
}

template <typename T, typename LQUEUE_NODE> const Const_LQueue_Iterator<T, LQUEUE_NODE> &
Const_LQueue_Iterator<T, LQUEUE_NODE>::operator++ (void)
{
}

template <typename T, typename LQUEUE_NODE> Const_LQueue_Iterator<T, LQUEUE_NODE>
Const_LQueue_Iterator<T, LQUEUE_NODE>::operator++ (int)
{
}

template <typename T, typename LQUEUE_NODE> const Const_LQueue_Iterator<T, LQUEUE_NODE> &
Const_LQueue_Iterator<T, LQUEUE_NODE>::operator-- (void)
{
}

template <typename T, typename LQUEUE_NODE> Const_LQueue_Iterator<T, LQUEUE_NODE>
Const_LQueue_Iterator<T, LQUEUE_NODE>::operator-- (int)
{
}

template <typename T, typename LQUEUE_NODE> bool
Const_LQueue_Iterator<T, LQUEUE_NODE>::operator== (const Const_LQueue_Iterator<T, LQUEUE_NODE> &rhs) const
{
}

template <typename T, typename LQUEUE_NODE> bool
Const_LQueue_Iterator<T, LQUEUE_NODE>::operator!= (const Const_LQueue_Iterator<T, LQUEUE_NODE> &rhs) const
{
  return !(*this == rhs);
}

template <typename T, typename LQUEUE_NODE>
Const_LQueue_Iterator<T, LQUEUE_NODE>::Const_LQueue_Iterator (LQUEUE_NODE *pos)
  : pos_ (pos)
{
}

template <typename T, typename LQUEUE_NODE> T &
LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator* (void)
{
}

template <typename T, typename LQUEUE_NODE> const T &
LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator* (void) const
{
}

template <typename T, typename LQUEUE_NODE> LQueue_Reverse_Iterator<T, LQUEUE_NODE> &
LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator++ (void) 
{
}

// Post-increment.
template <typename T, typename LQUEUE_NODE> LQueue_Reverse_Iterator<T, LQUEUE_NODE> 
LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator++ (int) 
{
}

template <typename T, typename LQUEUE_NODE> LQueue_Reverse_Iterator<T, LQUEUE_NODE> &
LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator-- (void)
{
}

template <typename T, typename LQUEUE_NODE> LQueue_Reverse_Iterator<T, LQUEUE_NODE>
LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator-- (int)
{
}

template <typename T, typename LQUEUE_NODE> bool
LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator== (const LQueue_Reverse_Iterator<T, LQUEUE_NODE> &rhs) const
{
}

template <typename T, typename LQUEUE_NODE> bool
LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator!= (const LQueue_Reverse_Iterator<T, LQUEUE_NODE> &rhs) const
{
  // implement != in terms of ==
  return !(*this == rhs);
}

template <typename T, typename LQUEUE_NODE>
LQueue_Reverse_Iterator<T, LQUEUE_NODE>::LQueue_Reverse_Iterator (LQUEUE_NODE *pos)
  : pos_ (pos)
{
}

template <typename T, typename LQUEUE_NODE> const T &
Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator* (void) const
{
}

template <typename T, typename LQUEUE_NODE> const Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE> &
Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator++ (void)
{
}

template <typename T, typename LQUEUE_NODE> Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE>
Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator++ (int)
{
}

template <typename T, typename LQUEUE_NODE> const Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE> &
Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator-- (void)
{
}

template <typename T, typename LQUEUE_NODE> Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE>
Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator-- (int)
{
}

template <typename T, typename LQUEUE_NODE> bool
Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator== (const Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE> &rhs) const
{
}

template <typename T, typename LQUEUE_NODE> bool
Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator!= (const Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE> &rhs) const
{
  return !(*this == rhs);
}

template <typename T, typename LQUEUE_NODE>
Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE>::Const_LQueue_Reverse_Iterator (LQUEUE_NODE *pos)
  : pos_ (pos)
{
}

#endif /* _LQUEUE_CPP */
