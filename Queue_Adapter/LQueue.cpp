
#if !defined (_LQUEUE_CPP)
#define _LQUEUE_CPP

#include <functional>
#include <algorithm>
#include "LQueue.h"
#include <iostream>

/* static */
template <typename T> LQueue_Node<T> *
LQueue_Node<T>::free_list_ = 0;

// Allocate a new <LQueue_Node>, trying first from the
// <free_list_> and if that's empty try from the global <::operator
// new>.

template <typename T> void *
LQueue_Node<T>::operator new (size_t)
{
    if (!free_list_) return (::new LQueue_Node<T>());
    else {
        LQueue_Node<T>* tempVal = free_list_;
        tempVal->next_ = nullptr;
        tempVal->prev_ = nullptr;
        free_list_ = free_list_->next_;
        //free_list_->prev_ = nullptr;
        return tempVal;
    }
}

// Return <ptr> to the <free_list_>.

template <typename T> void
LQueue_Node<T>::operator delete (void *ptr)
{
    LQueue_Node<T> *tobedeleted = static_cast<LQueue_Node<T>* > (ptr);
    tobedeleted->prev_ = nullptr;
    tobedeleted->next_ = free_list_;
    free_list_ = tobedeleted;
}

// Returns all dynamic memory on the free list to the free store.

template <typename T> void
LQueue_Node<T>::free_list_release (void)
{
    int count = 0;
    if (!free_list_) return;
    LQueue_Node<T> *temp;
    while (free_list_) {
        ++count;
        temp = free_list_->next_;
        delete free_list_;
        free_list_ = temp;
    }
    std::cerr << "Total number of free release is " << count << std::endl;
}

// Preallocate <n> <LQueue_Nodes> and store them on the
// <free_list_>.

template <typename T> void
LQueue_Node<T>::free_list_allocate (size_t n)
{
    for (size_t i=0; i < n; ++i) {
        LQueue_Node<T> *newNode = new LQueue_Node<T> ();
        newNode->next = free_list_;
        free_list_ = newNode;
    }
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
  /*
  if (next_)
      next_->prev_ = prev_;
  if (prev_)
      prev_->next_ = next_;
  */
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
: tail_ (new LQUEUE_NODE()),
    count_ (0)
{
    for (size_t i=0; i < size_hint; ++i) {
        LQUEUE_NODE* newNode = new LQUEUE_NODE ();
        newNode->next_ = tail_->next_;
        newNode->prev_ = tail_;
        tail_->next_->prev_ = newNode;
        tail_->next_ = newNode;
    }
}

template<typename T, typename LQUEUE_NODE> void
LQueue<T, LQUEUE_NODE>::swap (LQueue<T, LQUEUE_NODE> &new_queue)
{
    std::swap (count_ , new_queue.count_);
    std::swap (tail_ , new_queue.tail_);
}

// Copy constructor.

template <typename T, typename LQUEUE_NODE>
LQueue<T, LQUEUE_NODE>::LQueue (const LQueue<T, LQUEUE_NODE> &rhs)
  // Initialize fields here.
  : tail_ (new LQUEUE_NODE()), // tail_ will be set correctly by swap().
    count_ (rhs.count_) // count_ will be set correctly by swap().
{
    LQUEUE_NODE *temp = rhs.tail_->next_;
    LQUEUE_NODE *prev = tail_;
    LQUEUE_NODE *newNode = nullptr;
    while (temp != rhs.tail_) {
        newNode = new LQUEUE_NODE();
        newNode->item_ = temp->item_;
        newNode->prev_ = prev;
        prev->next_ = newNode;
        prev = newNode;
        temp = temp->next_;
    }
    tail_->prev_ = prev;
    prev->next_ = tail_;
}

// Assignment operator.
template <typename T, typename LQUEUE_NODE> LQueue<T, LQUEUE_NODE> &
LQueue<T, LQUEUE_NODE>::operator= (const LQueue<T, LQUEUE_NODE> &rhs) 
{
    LQueue<T, LQUEUE_NODE> temp(rhs);
    swap (temp);
    return *this;
}

// Perform actions needed when queue goes out of scope.

template <typename T, typename LQUEUE_NODE>
LQueue<T, LQUEUE_NODE>::~LQueue (void)
{
    LQUEUE_NODE *temp = tail_;
    LQUEUE_NODE *next=nullptr;
    while ( tail_ != temp) {
        next = tail_->next_;
        delete tail_;
        tail_ = next;
    }
    delete temp;
}

// Compare this queue with <rhs> for equality.  Returns true if the
// size()'s of the two queues are equal and all the elements from 0
// .. size() are equal, else false.

template <typename T, typename LQUEUE_NODE> bool 
LQueue<T, LQUEUE_NODE>::operator== (const LQueue<T, LQUEUE_NODE> &rhs) const
{
    if (count_ != rhs.count_) return false;
    LQUEUE_NODE *tempLeft = tail_->next_;
    LQUEUE_NODE *tempRight = rhs.tail_->next_;
    
    while (tempLeft != tail_ ) {
        if (tempLeft->item_ != tempRight->item_)  return false;
        tempLeft = tempLeft->next_;
        tempRight = tempRight->next_;
    }
    return true;
}

// Compare this queue with <rhs> for inequality such that <*this> !=
// <s> is always the complement of the boolean return value of
// <*this> == <s>.

template <typename T, typename LQUEUE_NODE> bool 
LQueue<T, LQUEUE_NODE>::operator!= (const LQueue<T, LQUEUE_NODE> &rhs) const
{
    return !(operator==(rhs));
}

// Returns true if the queue is empty, otherwise returns false.

template <typename T, typename LQUEUE_NODE> bool
LQueue<T, LQUEUE_NODE>::is_empty (void) const 
{
    return count_ == 0;
}

// Returns true if the queue is full, otherwise returns false.

template <typename T, typename LQUEUE_NODE> bool
LQueue<T, LQUEUE_NODE>::is_full (void) const 
{
    size_t count = 0;
    LQUEUE_NODE *temp = tail_;
    while (temp->next_ != tail_) {
        temp = temp->next_;
        ++count;
    }
    std::cout << "count is" << count << "actual count is" << count_ << std::endl;
    return count == count_;
}

// Place a <new_item> at the tail of the queue.  Throws
// the <Overflow> exception if the queue is full.

template <typename T, typename LQUEUE_NODE> void
LQueue<T, LQUEUE_NODE>::enqueue (const T &new_item)
{
    if (is_full()) throw Overflow();
    LQUEUE_NODE *temp = tail_;
    for (size_t i=1; i <= count_; ++i) {
        temp = temp->next_;
    }
    temp->next_->item_ = new_item;
    ++count_;
}

// Remove the front item on the queue without checking if the queue is empty.

template <typename T, typename LQUEUE_NODE> void
LQueue<T, LQUEUE_NODE>::dequeue_i (void)
{
    LQUEUE_NODE *temp = tail_->next_->next;
    // move the first node to the last;
    tail_->next_->next_ = tail_;
    tail_->next_->prev_ = tail_->prev_;
    tail_->next_->prev_->next_ = tail_->next_;
    tail_->next_ = temp;
    temp->prev_ = tail_;
    --count_;
}

// Throws the <Underflow> exception if the queue is empty. 
template <typename T, typename LQUEUE_NODE> void
LQueue<T, LQUEUE_NODE>::dequeue (void)
{
    if (count_ == 0) throw Underflow();
    LQUEUE_NODE *temp = tail_->next_->next_;
    tail_->next_->next_ = tail_;
    tail_->next_->prev_ = tail_->prev_;
    tail_->next_->prev_->next_ = tail_->next_;
    tail_->prev_ = tail_->next_;
    tail_->next_ = temp;
    temp->prev_ = tail_;
    --count_;
}

// Returns the front queue item without removing it. 
// Throws the <Underflow> exception if the queue is empty. 

template <typename T, typename LQUEUE_NODE> T 
LQueue<T, LQUEUE_NODE>::front (void) const
{
    if (count_ == 0) throw Underflow();
    return tail_->next_->item_;
}

// Get an iterator to the begining of the queue
template <typename T, typename LQUEUE_NODE> typename LQueue<T, LQUEUE_NODE>::iterator
LQueue<T, LQUEUE_NODE>::begin (void)
{
    return iterator (tail_->next_);
}

// Get an iterator pointing past the end of the queue
template <typename T, typename LQUEUE_NODE> typename LQueue<T, LQUEUE_NODE>::iterator
LQueue<T, LQUEUE_NODE>::end (void)
{
    LQUEUE_NODE *temp = tail_->next_;
    for (size_t i=1; i <= count_; ++i) {
        temp = temp->next_;
    }
    return iterator (temp);
}

// Get an iterator to the begining of the queue
template <typename T, typename LQUEUE_NODE> typename LQueue<T, LQUEUE_NODE>::const_iterator
LQueue<T, LQUEUE_NODE>::begin (void) const
{
    return const_iterator (tail_->next_);
}

// Get an iterator pointing past the end of the queue
template <typename T, typename LQUEUE_NODE> typename LQueue<T, LQUEUE_NODE>::const_iterator
LQueue<T, LQUEUE_NODE>::end (void) const
{
    LQUEUE_NODE *temp = tail_->next_;
    for (size_t i=1; i <= count_; ++i) {
        temp = temp->next_;
    }
    return const_iterator (temp);
}

// Get an iterator to the begining of the queue
template <typename T, typename LQUEUE_NODE> typename LQueue<T, LQUEUE_NODE>::reverse_iterator
LQueue<T, LQUEUE_NODE>::rbegin (void)
{
    LQUEUE_NODE *temp = tail_;
    for (size_t i=0; i<count_; ++i) {
        temp = temp->next_;
    }
    return reverse_iterator (temp);
}

// Get an iterator pointing past the end of the queue
template <typename T, typename LQUEUE_NODE> typename LQueue<T, LQUEUE_NODE>::reverse_iterator
LQueue<T, LQUEUE_NODE>::rend (void)
{
    return reverse_iterator (tail_);
}

// Get an iterator to the begining of the queue
template <typename T, typename LQUEUE_NODE> typename LQueue<T, LQUEUE_NODE>::const_reverse_iterator
LQueue<T, LQUEUE_NODE>::rbegin (void) const
{
    LQUEUE_NODE *temp = tail_;
    for (size_t i=0; i<count_; ++i) {
        temp = temp->next_;
    }
    return const_reverse_iterator (temp);
}

// Get an iterator pointing past the end of the queue
template <typename T, typename LQUEUE_NODE> typename LQueue<T, LQUEUE_NODE>::const_reverse_iterator
LQueue<T, LQUEUE_NODE>::rend (void) const
{
    return const_reverse_iterator (tail_);
}

template <typename T, typename LQUEUE_NODE> T &
LQueue_Iterator<T, LQUEUE_NODE>::operator* (void)
{
    return pos_->item_;
}

template <typename T, typename LQUEUE_NODE> const T &
LQueue_Iterator<T, LQUEUE_NODE>::operator* (void) const
{
    return pos_->item;
}

template <typename T, typename LQUEUE_NODE> LQueue_Iterator<T, LQUEUE_NODE> &
LQueue_Iterator<T, LQUEUE_NODE>::operator++ (void) 
{
    pos_ = pos_->next_;
    return *this;
}

// Post-increment.
template <typename T, typename LQUEUE_NODE> LQueue_Iterator<T, LQUEUE_NODE> 
LQueue_Iterator<T, LQUEUE_NODE>::operator++ (int) 
{
    LQueue_Iterator<T, LQUEUE_NODE> temp (*this);
    this->operator++();
    return temp;
}

template <typename T, typename LQUEUE_NODE> LQueue_Iterator<T, LQUEUE_NODE> &
LQueue_Iterator<T, LQUEUE_NODE>::operator-- (void)
{
    pos_ = pos_->prev_;
    return *this;
}

// Post-increment.
template <typename T, typename LQUEUE_NODE> LQueue_Iterator<T, LQUEUE_NODE> 
LQueue_Iterator<T, LQUEUE_NODE>::operator-- (int) 
{
    LQueue_Iterator<T, LQUEUE_NODE> temp (*this);
    this->operator--();
    return temp;
}

template <typename T, typename LQUEUE_NODE> bool
LQueue_Iterator<T, LQUEUE_NODE>::operator== (const LQueue_Iterator<T, LQUEUE_NODE> &rhs) const
{
    return pos_ == rhs.pos_;
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
    return pos_->item_;
}

template <typename T, typename LQUEUE_NODE> const Const_LQueue_Iterator<T, LQUEUE_NODE> &
Const_LQueue_Iterator<T, LQUEUE_NODE>::operator++ (void)
{
    pos_ = pos_->next_;
    return *this;
}

template <typename T, typename LQUEUE_NODE> Const_LQueue_Iterator<T, LQUEUE_NODE>
Const_LQueue_Iterator<T, LQUEUE_NODE>::operator++ (int)
{
    Const_LQueue_Iterator<T, LQUEUE_NODE> temp (*this);
    this->operator++();
    return temp;
}

template <typename T, typename LQUEUE_NODE> const Const_LQueue_Iterator<T, LQUEUE_NODE> &
Const_LQueue_Iterator<T, LQUEUE_NODE>::operator-- (void)
{
    pos_ = pos_->prev_;
    return *this;
}

template <typename T, typename LQUEUE_NODE> Const_LQueue_Iterator<T, LQUEUE_NODE>
Const_LQueue_Iterator<T, LQUEUE_NODE>::operator-- (int)
{
    Const_LQueue_Iterator<T, LQUEUE_NODE> temp (*this);
    this->operator--();
    return temp;
}

template <typename T, typename LQUEUE_NODE> bool
Const_LQueue_Iterator<T, LQUEUE_NODE>::operator== (const Const_LQueue_Iterator<T, LQUEUE_NODE> &rhs) const
{
    return pos_ == rhs.pos_;
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
    return pos_->item_;
}

template <typename T, typename LQUEUE_NODE> const T &
LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator* (void) const
{
    return pos_->item_;
}

template <typename T, typename LQUEUE_NODE> LQueue_Reverse_Iterator<T, LQUEUE_NODE> &
LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator++ (void) 
{
    pos_ = pos_->prev_;
    return *this;
}

// Post-increment.
template <typename T, typename LQUEUE_NODE> LQueue_Reverse_Iterator<T, LQUEUE_NODE> 
LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator++ (int) 
{
    LQueue_Reverse_Iterator<T, LQUEUE_NODE> temp (*this);
    this->operator++();
    return temp;
}

template <typename T, typename LQUEUE_NODE> LQueue_Reverse_Iterator<T, LQUEUE_NODE> &
LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator-- (void)
{
    pos_ = pos_->next_;
    return *this;
}

template <typename T, typename LQUEUE_NODE> LQueue_Reverse_Iterator<T, LQUEUE_NODE>
LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator-- (int)
{
    LQueue_Reverse_Iterator<T, LQUEUE_NODE> temp (*this);
    this->operator--();
    return temp;
}

template <typename T, typename LQUEUE_NODE> bool
LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator== (const LQueue_Reverse_Iterator<T, LQUEUE_NODE> &rhs) const
{
    return pos_ == rhs.pos_;
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
    return pos_->item_;
}

template <typename T, typename LQUEUE_NODE> const Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE> &
Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator++ (void)
{
    pos_ = pos_->prev_;
    return *this;
}

template <typename T, typename LQUEUE_NODE> Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE>
Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator++ (int)
{
    Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE> temp (*this);
    this->operator++();
    return temp;
}

template <typename T, typename LQUEUE_NODE> const Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE> &
Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator-- (void)
{
    pos_ = pos_->next_;
    return *this;
}

template <typename T, typename LQUEUE_NODE> Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE>
Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator-- (int)
{
    Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE> temp (*this);
    this->operator--();
    return temp;
}

template <typename T, typename LQUEUE_NODE> bool
Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator== (const Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE> &rhs) const
{
    return pos_ == rhs.pos__;
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
