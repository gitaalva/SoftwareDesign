
/**
 * @class AQueue
 * @brief Defines a generic "first-in/first-out" (FIFO) Abstract Data Type (ADT) using an Array
 *        that is organized as a "circular queue."
 */

#if !defined (_AQUEUE_C)
#define _AQUEUE_C

#include "AQueue.h"
#include <vector>

// Returns the current number of elements in the queue.

template <typename T, typename ARRAY> 
size_t
AQueue<T, ARRAY>::size (void) const
{
    return count_;
}

// Constructor.

template <typename T, typename ARRAY> 
AQueue<T, ARRAY>::AQueue (size_t size) : queue_(ARRAY(size+1)), head_(0), tail_(0), count_(0) // +1 for the dummy node
{
}

// Copy constructor.

template <typename T, typename ARRAY> 
AQueue<T, ARRAY>::AQueue (const AQueue<T, ARRAY> &rhs): queue_ (rhs.queue_), head_(rhs.head_), tail_(rhs.tail_), count_ (rhs.count_)
{
}

template <typename T, typename ARRAY>
void
AQueue<T, ARRAY>::swap (AQueue<T, ARRAY> &new_aqueue)
{
    std::swap (queue_, new_aqueue.queue_);
    std::swap (head_, new_aqueue.head_);
    std::swap (tail_, new_aqueue.tail_);
    std::swap (count_, new_aqueue.count_);
}

// Assignment operator.
template <typename T, typename ARRAY>
AQueue<T, ARRAY>& 
AQueue<T, ARRAY>::operator= (const AQueue<T, ARRAY> &rhs) 
{
    AQueue<T, ARRAY> temp(rhs);
    swap (temp);
    return *this;
}

// Perform actions needed when queue goes out of scope.

template <typename T, typename ARRAY>
AQueue<T, ARRAY>::~AQueue (void)
{
  // There's nothing to do here since we didn't dynamically
  // allocate any memory. The queue_ dtor handles that.
}

// Compare this queue with <rhs> for equality.  Returns true if the
// size()'s of the two queues are equal and all the elements from 0
// .. size() are equal, else false.
template <typename T, typename ARRAY>
bool 
AQueue<T, ARRAY>::operator== (const AQueue<T, ARRAY> &rhs) const
{
    if (count_ != rhs.count_) return false;
    for (size_t i=head_, j=rhs.head_; i < tail_; ++i,++j) {
        if (queue_[i] != rhs.queue_[j]) return false;
    }
    return true;
}

// Compare this queue with <rhs> for inequality such that <*this> !=
// <s> is always the complement of the boolean return value of
// <*this> == <s>.

template <typename T, typename ARRAY>
bool 
AQueue<T, ARRAY>::operator!= (const AQueue<T, ARRAY> &rhs) const
{
    return !(*this == rhs);
}

// Place a <new_item> at the tail of the queue.  Throws
// the <Overflow> exception if the queue is full.

template <typename T, typename ARRAY>
void
AQueue<T, ARRAY>::enqueue (const T &new_item)
{
    if (count_ == queue_.size()-1) throw Overflow();
    queue_[tail_] = new_item;
    tail_ = increment(tail_);
    ++count_;
    /*
    if (tail_ = queue_.size()) tail = 0;
    queue_[++tail_] = new_item;
    if (count_++ == 0) head_=1; // incrementes the count too
    */
}

// Remove the front item on the queue.  Throws the <Underflow>
// exception if the queue is empty.

template <typename T, typename ARRAY>
void
AQueue<T, ARRAY>::dequeue (void)
{
    if (count_ == 0) throw Underflow();
    else if (count_ == 1) { // can have this special condition so that we can start from the beginning
        head_ = 0; tail_ = 0; --count_;
    } else {
        head_ = increment(head_);
        --count_;
    }
}

// Returns the front queue item without removing it.  Throws the
// <Underflow> exception if the queue is empty.

template <typename T, typename ARRAY>
T
AQueue<T, ARRAY>::front (void) const
{
    if (count_ == 0) throw Underflow();
    return queue_[head_];
}

// Returns true if the queue is empty, otherwise returns false.

template <typename T, typename ARRAY>
bool
AQueue<T, ARRAY>::is_empty (void) const 
{
    return count_ == 0;
}

// Returns true if the queue is full, otherwise returns false.

template <typename T, typename ARRAY>
bool
AQueue<T, ARRAY>::is_full (void) const 
{
    return count_ == queue_.size()-1;
}

// Get an iterator to the begining of the queue
template <typename T, typename ARRAY>
typename AQueue<T, ARRAY>::iterator
AQueue<T, ARRAY>::begin (void)
{
    return iterator(*this,head_);
}

// Get an iterator pointing past the end of the queue
template <typename T, typename ARRAY>
typename AQueue<T, ARRAY>::iterator
AQueue<T, ARRAY>::end (void)
{
    return iterator(*this,tail_);
}

// Get an iterator to the begining of the queue
template <typename T, typename ARRAY>
typename AQueue<T, ARRAY>::const_iterator
AQueue<T, ARRAY>::begin (void) const
{
    return const_iterator(*this,head_);
}

// Get an iterator pointing past the end of the queue
template <typename T, typename ARRAY>
typename AQueue<T, ARRAY>::const_iterator
AQueue<T, ARRAY>::end (void) const
{
    return const_iterator (*this,tail_);
}

// Get an iterator to the end of the queue
template <typename T, typename ARRAY>
typename AQueue<T, ARRAY>::reverse_iterator
AQueue<T, ARRAY>::rbegin (void)
{
    return reverse_iterator (*this,decrement(tail_));
}

// Get an iterator pointing to the beginning of the queue
template <typename T, typename ARRAY>
typename AQueue<T, ARRAY>::reverse_iterator
AQueue<T, ARRAY>::rend (void)
{
    return reverse_iterator (*this, decrement(head_));
}

// Get an iterator to the end of the queue
template <typename T, typename ARRAY>
typename AQueue<T, ARRAY>::const_reverse_iterator
AQueue<T, ARRAY>::rbegin (void) const
{
    const_reverse_iterator (*this,decrement(tail_));
}

// Get an iterator pointing to the beginning of the queue
template <typename T, typename ARRAY>
typename AQueue<T, ARRAY>::const_reverse_iterator
AQueue<T, ARRAY>::rend (void) const
{
    const_reverse_iterator (*this, decrement(head_));
}

/// Calculate the appropriate index when incrementing.
template <typename T, typename ARRAY>
size_t
AQueue<T, ARRAY>::increment (size_t index) const
{
    return index == (queue_.size()-1) ? 0 : ++index;
}

/// Calculate the appropriate index when decrementing.
template <typename T, typename ARRAY>
size_t
AQueue<T, ARRAY>::decrement (size_t index) const
{
    return index == (0) ? queue_.size()-1 : --index;
}

template <typename T, typename ARRAY>
T &
AQueue_Iterator<T, ARRAY>::operator* (void)
{
    return aqueue_ref_.queue_[pos_];
}

template <typename T, typename ARRAY>
const T &
AQueue_Iterator<T, ARRAY>::operator* (void) const
{
    return aqueue_ref_[pos_];
}

template <typename T, typename ARRAY>
AQueue_Iterator<T, ARRAY> &
AQueue_Iterator<T, ARRAY>::operator++ (void) 
{
    pos_ = aqueue_ref_.increment(pos_);
    return *this;
}

// Post-increment.
template <typename T, typename ARRAY>
AQueue_Iterator<T, ARRAY> 
AQueue_Iterator<T, ARRAY>::operator++ (int) 
{
    AQueue_Iterator<T, ARRAY> temp(*this);
    this->operator++();
    return temp;
}

template <typename T, typename ARRAY>
AQueue_Iterator<T, ARRAY> &
AQueue_Iterator<T, ARRAY>::operator-- (void)
{
    pos_ = aqueue_ref_.decrement(pos_);
    return *this;
}

// Post-decrement.
template <typename T, typename ARRAY>
AQueue_Iterator<T, ARRAY>
AQueue_Iterator<T, ARRAY>::operator-- (int) 
{
    AQueue_Iterator<T, ARRAY> temp(*this);
    this->operator--();
    return temp;
}

template <typename T, typename ARRAY>
bool
AQueue_Iterator<T, ARRAY>::operator== (const AQueue_Iterator<T, ARRAY> &rhs) const
{
    return (pos_ == rhs.pos_ && &aqueue_ref_ == &rhs.aqueue_ref_);
}

template <typename T, typename ARRAY>
bool
AQueue_Iterator<T, ARRAY>::operator!= (const AQueue_Iterator<T, ARRAY> &rhs) const
{
  return !(pos_ == rhs.pos_ && &aqueue_ref_ == &rhs.aqueue_ref_);
}

template <typename T, typename ARRAY>
AQueue_Iterator<T, ARRAY>::AQueue_Iterator (AQueue<T, ARRAY> &queue,
                                            size_t pos) : aqueue_ref_(queue), pos_(pos)
{
}

template <typename T, typename ARRAY>
const T &
Const_AQueue_Iterator<T, ARRAY>::operator* (void) const
{
    return aqueue_ref_.queue_[pos_];
}

template <typename T, typename ARRAY>
const Const_AQueue_Iterator<T, ARRAY> &
Const_AQueue_Iterator<T, ARRAY>::operator++ (void)
{
    pos_ = aqueue_ref_.increment(pos_);
    return *this;
}

template <typename T, typename ARRAY>
Const_AQueue_Iterator<T, ARRAY>
Const_AQueue_Iterator<T, ARRAY>::operator++ (int)
{
    Const_AQueue_Iterator<T, ARRAY> temp(*this);
    this->operator++();
    return temp;
}

template <typename T, typename ARRAY>
const Const_AQueue_Iterator<T, ARRAY> &
Const_AQueue_Iterator<T, ARRAY>::operator-- (void)
{
    pos_ = aqueue_ref_.decrement(pos_);
    return *this;
}

// Post-decrement.
template <typename T, typename ARRAY>
Const_AQueue_Iterator<T, ARRAY>
Const_AQueue_Iterator<T, ARRAY>::operator-- (int)
{
    Const_AQueue_Iterator<T, ARRAY> temp(*this);
    this->operator--();
    return temp;
}

template <typename T, typename ARRAY>
bool
Const_AQueue_Iterator<T, ARRAY>::operator== (const Const_AQueue_Iterator<T, ARRAY> &rhs) const
{
    return pos_ == rhs.pos_;
}

template <typename T, typename ARRAY>
bool
Const_AQueue_Iterator<T, ARRAY>::operator!= (const Const_AQueue_Iterator<T, ARRAY> &rhs) const
{
  return ! (pos_ == rhs.pos_) ;
}

template <typename T, typename ARRAY>
Const_AQueue_Iterator<T, ARRAY>::Const_AQueue_Iterator (const AQueue<T, ARRAY> &queue,
                                                        size_t pos):aqueue_ref_(queue), pos_ (pos)
{
}

template <typename T, typename ARRAY>
T &
AQueue_Reverse_Iterator<T, ARRAY>::operator* (void)
{
    return aqueue_ref_.queue_[pos_];
}

template <typename T, typename ARRAY>
const T &
AQueue_Reverse_Iterator<T, ARRAY>::operator* (void) const
{
    return aqueue_ref_.queue_[pos_];
}

template <typename T, typename ARRAY>
AQueue_Reverse_Iterator<T, ARRAY> &
AQueue_Reverse_Iterator<T, ARRAY>::operator++ (void) 
{
    pos_ = aqueue_ref_.decrement(pos_);
    return *this;
}

template <typename T, typename ARRAY>
AQueue_Reverse_Iterator<T, ARRAY> 
AQueue_Reverse_Iterator<T, ARRAY>::operator++ (int) 
{
    AQueue_Reverse_Iterator<T, ARRAY> temp(*this);
    this->operator++();
    return temp;
    
}

template <typename T, typename ARRAY>
AQueue_Reverse_Iterator<T, ARRAY> &
AQueue_Reverse_Iterator<T, ARRAY>::operator-- (void)
{
    pos_ = aqueue_ref_.increment(pos_);
    return *this;
}

template <typename T, typename ARRAY>
AQueue_Reverse_Iterator<T, ARRAY>
AQueue_Reverse_Iterator<T, ARRAY>::operator-- (int) 
{
    AQueue_Reverse_Iterator<T, ARRAY> temp(*this);
    this->operator--();
    return temp;
}

template <typename T, typename ARRAY>
bool
AQueue_Reverse_Iterator<T, ARRAY>::operator== (const AQueue_Reverse_Iterator<T, ARRAY> &rhs) const
{
    return (pos_ == rhs.pos_) && &aqueue_ref_ == &rhs.aqueue_ref_;
}

template <typename T, typename ARRAY>
bool
AQueue_Reverse_Iterator<T, ARRAY>::operator!= (const AQueue_Reverse_Iterator<T, ARRAY> &rhs) const
{
  return !(*this == rhs);
}

template <typename T, typename ARRAY>
AQueue_Reverse_Iterator<T, ARRAY>::AQueue_Reverse_Iterator (AQueue<T, ARRAY> &queue,
                                                            size_t pos) : aqueue_ref_ (queue), pos_ (pos)
{
}

template <typename T, typename ARRAY>
const T &
Const_AQueue_Reverse_Iterator<T, ARRAY>::operator* (void) const
{
}

template <typename T, typename ARRAY>
const Const_AQueue_Reverse_Iterator<T, ARRAY> &
Const_AQueue_Reverse_Iterator<T, ARRAY>::operator++ (void)
{
    pos_ = aqueue_ref_.decrement(pos_);
    return *this;
}

template <typename T, typename ARRAY>
Const_AQueue_Reverse_Iterator<T, ARRAY>
Const_AQueue_Reverse_Iterator<T, ARRAY>::operator++ (int)
{
    Const_AQueue_Reverse_Iterator<T, ARRAY> temp(*this);
    this->operator++();
    return temp;
}

template <typename T, typename ARRAY>
const Const_AQueue_Reverse_Iterator<T, ARRAY> &
Const_AQueue_Reverse_Iterator<T, ARRAY>::operator-- (void)
{
}

template <typename T, typename ARRAY>
Const_AQueue_Reverse_Iterator<T, ARRAY>
Const_AQueue_Reverse_Iterator<T, ARRAY>::operator-- (int)
{
}

template <typename T, typename ARRAY>
bool
Const_AQueue_Reverse_Iterator<T, ARRAY>::operator== (const Const_AQueue_Reverse_Iterator<T, ARRAY> &rhs) const
{
}

template <typename T, typename ARRAY>
bool
Const_AQueue_Reverse_Iterator<T, ARRAY>::operator!= (const Const_AQueue_Reverse_Iterator<T, ARRAY> &rhs) const
{
  return !(*this == rhs);
}

template <typename T, typename ARRAY>
Const_AQueue_Reverse_Iterator<T, ARRAY>::Const_AQueue_Reverse_Iterator (const AQueue<T, ARRAY> &queue,
                                                                        size_t pos)
{
}

#endif /* _AQUEUE_C */
