
/* -*- C++ -*- */
#if !defined (_AQUEUE_H)
#define _AQUEUE_H

#include "Array.h"

// Solve circular include problem via forward decls.
template <typename T, typename ARRAY>
class AQueue_Iterator;

template <typename T, typename ARRAY>
class Const_AQueue_Iterator;

template <typename T, typename ARRAY>
class AQueue_Reverse_Iterator;

template <typename T, typename ARRAY>
class Const_AQueue_Reverse_Iterator;

/**
 * @class AQueue
 * @brief Defines a generic "first-in/first-out" (FIFO) Abstract Data Type (ADT) using an Array
 *        that is organized as a "circular queue."
 */
template <typename T, typename ARRAY = Array<T> >
class AQueue
{
  friend class AQueue_Iterator<T, ARRAY>;
  friend class Const_AQueue_Iterator<T, ARRAY>;
  friend class AQueue_Reverse_Iterator<T, ARRAY>;
  friend class Const_AQueue_Reverse_Iterator<T, ARRAY>;
public:
  // Define a "trait"
  typedef T value_type;

  // = Exceptions thrown by methods in this class.
  class Underflow {};
  class Overflow {};

  // = Initialization, assignment, and termination methods.

  // Constructor.
  AQueue (size_t size);

  // Copy constructor.
  AQueue (const AQueue<T, ARRAY> &rhs);

  // Assignment operator.
  AQueue<T, ARRAY> &operator = (const AQueue<T, ARRAY> &rhs);

  // Perform actions needed when queue goes out of scope. 
  ~AQueue (void);

  // = Classic Queue operations.

  // Place a <new_item> at the tail of the queue.  Throws
  // the <Overflow> exception if the queue is full.
  void enqueue (const T &new_item);

  // Removes the front item on the queue.  Throws the <Underflow>
  // exception if the queue is empty.
  void dequeue (void);

  // Returns the front queue item without removing it. 
  // Throws the <Underflow> exception if the queue is empty. 
  T front (void) const;

  // = Check boundary conditions for Queue operations. 

  // Returns 1 if the queue is empty, otherwise returns 0. 
  bool is_empty (void) const;

  // Returns 1 if the queue is full, otherwise returns 0. 
  bool is_full (void) const;

  // Returns the current number of elements in the queue.
  size_t size (void) const;

  // Compare this queue with <rhs> for equality.  Returns true if the
  // size()'s of the two queues are equal and all the elements from 0
  // .. size() are equal, else false.
  bool operator== (const AQueue<T, ARRAY> &rhs) const;

  // Compare this queue with <rhs> for inequality such that <*this> !=
  // <s> is always the complement of the boolean return value of
  // <*this> == <s>.
  bool operator!= (const AQueue<T, ARRAY> &s) const;

  // Efficiently swap the contents of this <AQueue> with <new_aqueue>.
  // Does not throw an exception.
  void swap (AQueue<T, ARRAY> &new_aqueue);

  // = Factory methods that create iterators.

  typedef AQueue_Iterator<T, ARRAY> iterator;
  typedef Const_AQueue_Iterator<T, ARRAY> const_iterator;
  typedef AQueue_Reverse_Iterator<T, ARRAY> reverse_iterator;
  typedef Const_AQueue_Reverse_Iterator<T, ARRAY> const_reverse_iterator;

  // Get an iterator that points to the beginning of the queue.
  iterator begin (void);

  // Get a const iterator that points to the beginning of the queue.
  const_iterator begin (void) const;

  // Get an iterator that points to the end of the queue.
  iterator end (void);

  // Get a const iterator that points to the end of the queue.
  const_iterator end (void) const;

  // Get an iterator that points to the end of the queue.
  reverse_iterator rbegin (void);

  // Get a const iterator that points to the end of the queue.
  const_reverse_iterator rbegin (void) const;

  // Get an iterator that points to the beginning of the queue.
  reverse_iterator rend (void);

  // Get a const iterator that points to the beginning of the queue.
  const_reverse_iterator rend (void) const;

protected:
  /// Helper functions to calculate appropriate pointers into the queue
  /// even with the possibility of wrapping around.

  /// Calculate the appropriate index when incrementing.
  size_t increment (size_t index) const;

  /// Calculate the appropriate index when decrementing.
  size_t decrement (size_t index) const;

private:
  ARRAY queue_;
  // Resizable buffer that holds circular queue data.

  size_t head_;
  // Contains the index location of the head (front) item 
  // in the queue.

  size_t tail_;
  // Contains the index location of the "dummy" (back) item
  // at the tail of the queue.

  size_t count_;
  // Number of items that are currently in the queue.
};

/**
 * @class AQueue_Iterator
 * @brief Implements a bidirectional iterator for AQueue classes.
 *
 * Note:  Having a const Iterator does not guarantee that the current
 * *position* that it points to will not change, it only guarantees that
 * you cannot change the underlying array!
 */
template <typename T, typename ARRAY>
class AQueue_Iterator 
{
public:
  /// Construct an AQueue_Iterator at position pos.  
  AQueue_Iterator (AQueue<T, ARRAY> &queue, size_t pos = 0);

  /// Dereference operator returns a reference to the item contained
  /// at the current position
  T& operator* (void);

  /// Returns a const reference to the item contained at the current position
  const T& operator* (void) const;

  /// Preincrement operator
  AQueue_Iterator<T, ARRAY> &operator++ (void);

  /// Postincrement operator
  AQueue_Iterator<T, ARRAY> operator++ (int);

  /// Predecrement operator
  AQueue_Iterator<T, ARRAY> &operator-- (void);

  /// Posdecrement operator
  AQueue_Iterator<T, ARRAY> operator-- (int);

  /// Equality operator
  bool operator== (const AQueue_Iterator<T, ARRAY> &rhs) const;

  /// Nonequality operator
  bool operator!= (const AQueue_Iterator<T, ARRAY> &lhs) const;

  // = Necessary traits
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef T value_type;
  typedef T *pointer;
  typedef T &reference;
  typedef int difference_type;

private:
  /// the array we are dealing with
  AQueue<T, ARRAY> &aqueue_ref_;

  /// Our current position in the queue.
  mutable size_t pos_;
};

/**
 * @class Const_AQueue_Iterator
 * @brief Implements a bidirectional iterator for const AQueue classes.
 *
 * Note:  Having a const Iterator does not guarantee that the current
 * *position* that it points to will not change, it only guarantees that
 * you cannot change the underlying array!
 */
template <typename T, typename ARRAY>
class Const_AQueue_Iterator 
{
public:
  /// Construct an AQueue_Iterator at position pos.  
  Const_AQueue_Iterator (const AQueue<T, ARRAY> &queue, size_t pos = 0);

  /// Dereference operator returns a const reference to the item
  /// contained at the current position.
  const T& operator* (void) const;

  /// Preincrement operator
  const Const_AQueue_Iterator<T, ARRAY> &operator++ (void);

  /// Postincrement operator
  Const_AQueue_Iterator<T, ARRAY> operator++ (int);

  /// Predecrement operator
  const Const_AQueue_Iterator<T, ARRAY> &operator-- (void);

  /// Posdecrement operator
  Const_AQueue_Iterator<T, ARRAY> operator-- (int);

  /// Equality operator
  bool operator== (const Const_AQueue_Iterator<T, ARRAY> &rhs) const;

  /// Nonequality operator
  bool operator!= (const Const_AQueue_Iterator<T, ARRAY> &lhs) const;

  // = Necessary traits
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef T value_type;
  typedef T *pointer;
  typedef T &reference;
  typedef int difference_type;

private:
  /// the array we are dealing with
  const AQueue<T, ARRAY> &aqueue_ref_;

  /// Our current position in the queue.
  mutable size_t pos_;
};

/**
 * @class AQueue_Reverse_Iterator
 * @brief Implements a bidirectional reverse iterator for AQueue classes.
 *
 * Note:  Having a const Iterator does not guarantee that the current
 * *position* that it points to will not change, it only guarantees that
 * you cannot change the underlying array!
 */
template <typename T, typename ARRAY>
class AQueue_Reverse_Iterator 
{
public:
  /// Construct an AQueue_Iterator at position pos.  
  AQueue_Reverse_Iterator (AQueue<T, ARRAY> &queue, size_t pos = 0);

  /// Dereference operator returns a reference to the item contained
  /// at the current position
  T& operator* (void);

  /// Returns a const reference to the item contained at the current position
  const T& operator* (void) const;

  /// Preincrement operator
  /// Different semantics from a non-reverse iterator
  AQueue_Reverse_Iterator<T, ARRAY> &operator++ (void);

  /// Postincrement operator
  /// Different semantics from a non-reverse iterator
  AQueue_Reverse_Iterator<T, ARRAY> operator++ (int);

  /// Predecrement operator
  /// Different semantics from a non-reverse iterator
  AQueue_Reverse_Iterator<T, ARRAY> &operator-- (void);

  /// Posdecrement operator
  /// Different semantics from a non-reverse iterator
  AQueue_Reverse_Iterator<T, ARRAY> operator-- (int);

  /// Equality operator
  bool operator== (const AQueue_Reverse_Iterator<T, ARRAY> &rhs) const;

  /// Nonequality operator
  bool operator!= (const AQueue_Reverse_Iterator<T, ARRAY> &lhs) const;

  // = Necessary traits
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef T value_type;
  typedef T *pointer;
  typedef T &reference;
  typedef int difference_type;

private:
  /// the array we are dealing with
  AQueue<T, ARRAY> &aqueue_ref_;

  /// Our current position in the queue.
  mutable size_t pos_;
};

/**
 * @class Const_AQueue_Reverse_Iterator
 * @brief Implements a bidirectional reverse iterator for const AQueue classes.
 *
 * Note:  Having a const Iterator does not guarantee that the current
 * *position* that it points to will not change, it only guarantees that
 * you cannot change the underlying array!
 */
template <typename T, typename ARRAY>
class Const_AQueue_Reverse_Iterator 
{
public:
  /// Construct an AQueue_Reverse_Iterator at position pos.  
  Const_AQueue_Reverse_Iterator (const AQueue<T, ARRAY> &queue, size_t pos = 0);

  /// Dereference operator returns a const reference to the item
  /// contained at the current position.
  const T& operator* (void) const;

  /// Preincrement operator
  /// Different semantics from a non-reverse iterator
  const Const_AQueue_Reverse_Iterator<T, ARRAY> &operator++ (void);

  /// Postincrement operator
  /// Different semantics from a non-reverse iterator
  Const_AQueue_Reverse_Iterator<T, ARRAY> operator++ (int);

  /// Predecrement operator
  /// Different semantics from a non-reverse iterator
  const Const_AQueue_Reverse_Iterator<T, ARRAY> &operator-- (void);

  /// Posdecrement operator
  /// Different semantics from a non-reverse iterator
  Const_AQueue_Reverse_Iterator<T, ARRAY> operator-- (int);

  /// Equality operator
  bool operator== (const Const_AQueue_Reverse_Iterator<T, ARRAY> &rhs) const;

  /// Nonequality operator
  bool operator!= (const Const_AQueue_Reverse_Iterator<T, ARRAY> &lhs) const;

  // = Necessary traits
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef T value_type;
  typedef T *pointer;
  typedef T &reference;
  typedef int difference_type;

private:
  /// the array we are dealing with
  const AQueue<T, ARRAY> &aqueue_ref_;

  /// Our current position in the queue.
  mutable size_t pos_;
};

#include "AQueue.cpp"
#endif /* AQUEUE_H */
