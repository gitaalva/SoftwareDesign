
/* -*- C++ -*- */

#ifndef ARRAY_H
#define ARRAY_H

// This header defines "size_t"
#include <stdlib.h>
#include <stdexcept>
#include <memory>
#include "scoped_array.h"

// Solve circular include problem
template <typename T>
class Array_Iterator;

// Solve circular include problem
template <typename T>
class Const_Array_Iterator;

/**
 * @class Array
 * @brief Implements a vector that resizes.
 */
template <typename T>
class Array
{
public:
  // Define a "trait"
  typedef T value_type;

  // = Initialization and termination methods.

  // Dynamically create an uninitialized array.  Throws <std::bad_alloc>
  // if allocation fails.
  Array (size_t size);

  // Dynamically initialize the entire array to the <default_value>.
  // Throws <std::bad_alloc> if allocation fails.
  Array (size_t size, const T &default_value);

  // The copy constructor performs initialization by making an exact
  // copy of the contents of parameter <s>, i.e., *this == s will
  // return true.  Throws <std::bad_alloc> if allocation fails.
  Array (const Array<T> &s);

  // Assignment operator performs an assignment by making a copy of
  // the contents of parameter <s>, i.e., *this == s will return true.
  // Throws <std::bad_alloc> if allocation fails.  If any exceptions
  // occur, however, the state of the original array remains unchanged
  // (i.e., implement "strong exception guarantee" semantics).
  Array<T> &operator= (const Array<T> &s);

  // Clean up the array (e.g., delete dynamically allocated memory).
  ~Array (void);

  // = Forward iterator definitions
  typedef Array_Iterator<T> iterator;
  typedef Const_Array_Iterator<T> const_iterator;

  // Get an iterator that points to the beginning of the list
  iterator begin (void);

  // Get a const interator that points to the beginning of the Array.
  const_iterator begin (void) const;

  // Get an iterator that points to the end
  iterator end (void);

  // Get a const iterator that points to the end of the list.
  const_iterator end (void) const;

  // = Set/get methods.

  // Set an item in the array at location index.  If <index> >=
  // <s.cur_size_> then <resize()> the array so it's big enough.
  // Throws <std::bad_alloc> if resizing the array fails.
  void set (const T &new_item, size_t index);

  // Get an item in the array at location index.  Throws <std::out_of_range>
  // of index is not <in_range>.
  void get (T &item, size_t index);

  // Returns the <cur_size_> of the array.
  size_t size (void) const;

  // Returns a reference to the <index> element in the <Array> without
  // checking for range errors.
  const T &operator[] (size_t index) const;

  // Set an item in the array at location index without 
  // checking for range errors.
  T &operator[] (size_t index);

  // Compare this array with <s> for equality.  Returns true if the
  // size()'s of the two arrays are equal and all the elements from 0
  // .. size() are equal, else false.
  bool operator== (const Array<T> &s) const;

  // Compare this array with <s> for inequality such that <*this> !=
  // <s> is always the complement of the boolean return value of
  // <*this> == <s>.
  bool operator!= (const Array<T> &s) const;

  // Change the size of the array to be at least <new_size> elements.
  // If a <default_value> was given in the <Array> constructor then
  // make sure any new elements are initialized accordingly.  Throws
  // <std::bad_alloc> if allocation fails.
  void resize (size_t new_size);

  // Efficiently swap the contents of this array with <new_array>.
  // Does not throw an exception.
  void swap (Array<T> &new_array);

private:
  // Returns true if <index> is within range, i.e., 0 <= <index> <
  // <cur_size_>, else returns false.
  bool in_range (size_t index) const;

  // Maximum size of the array, i.e., the total number of <T> elements
  // in <array_>.
  size_t max_size_;
        
  // Current size of the array.  The purpose of keeping track of both 
  // <cur_size_> and <max_size_> is to avoid reallocating memory if we
  // don't have to in the set() method. 
  size_t cur_size_;

  // If a default value is needed, keep track of its value.
  std::unique_ptr<T> default_value_;

  // @@ Replace unique_ptr with auto_ptr if your compiler doesn't support C++11.
  // std::auto_ptr<T> default_value_;

  // Pointer to the array's storage buffer.
  scoped_array<T> array_;
};

/**
 * @class Array_Iterator
 * @brief Implements a bidirectional iterator for array type classes.
 *
 * Note:  Having a const Iterator does not guarantee that the current
 * *position* that it points to will not change, it only guarantees that
 * you cannot change the underlying array!
 */
template <typename T>
class Array_Iterator 
{
  friend class Array<T>;

private:
  /// Construct an Array_Iterator at position pos.  
  Array_Iterator (Array<T> &array, size_t pos = 0);

public:
  /// Dereference operator returns a reference to the item contained
  /// at the current position
  T& operator* (void);

  /// Returns a const reference to the item contained at the current position
  const T& operator* (void) const;

  /// Preincrement operator
  Array_Iterator<T> &operator++ (void);

  /// Postincrement operator
  Array_Iterator<T> operator++ (int);

  /// Predecrement operator
  Array_Iterator<T> &operator-- (void);

  /// Posdecrement operator
  Array_Iterator<T> operator-- (int);

  /// Equality operator
  bool operator== (const Array_Iterator<T> &rhs) const;

  /// Nonequality operator
  bool operator!= (const Array_Iterator<T> &lhs) const;

  // = Necessary traits
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef T value_type;
  typedef T *pointer;
  typedef T &reference;
  typedef int difference_type;

private:
  /// the array we are dealing with
  Array<T> &array_;

  /// Our current position
  mutable size_t pos_;
};

/**
 * @class Const_Array_Iterator
 * @brief Implements a bidirectional iterator for array type classes.
 *
 * Note:  Having a const Iterator does not gaurantee that the current
 * *position* that it points to will not change, it only guarantees that
 * you cannot change the underlying array!
 */
template <typename T>
class Const_Array_Iterator
{
public:
  friend class Array<T>;

public:
  /// Construct an iterator at position pos.
  Const_Array_Iterator (const Array<T> &array, size_t pos = 0);

  /// Returns a const reference to the item contained at the current position.
  const T& operator* (void) const;

  /// Preincrement operator
  const Const_Array_Iterator<T> &operator++ (void) const;

  /// Postincrement operator
  Const_Array_Iterator<T> operator++ (int) const;

  /// Predecrement operator
  const Const_Array_Iterator &operator-- (void) const; 

  /// Postdecrement operator
  Const_Array_Iterator<T> operator-- (int) const;

  /// Equality operator
  bool operator== (const Const_Array_Iterator<T> &rhs) const;

  /// Nonequality operator
  bool operator!= (const Const_Array_Iterator<T> &lhs) const;

  // = Necessary traits
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef T value_type;
  typedef T *pointer;
  typedef T &reference;
  typedef int difference_type;

private:
  /// the array we are dealing with
  const Array<T> &array_;

  /// Our current position
  mutable size_t pos_;
};

#if defined (__INLINE__)
#define INLINE inline
#include "Array.inl"
#endif /* __INLINE__ */

#include "Array.cpp"

#endif /* ARRAY_H */
