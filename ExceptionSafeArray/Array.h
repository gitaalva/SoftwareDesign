
/* -*- C++ -*- */

#ifndef ARRAY_H
#define ARRAY_H

// This header defines "size_t"
#include <stdlib.h>
#include <boost/scoped_array.hpp>

// Generalize the type.
typedef char T;

class Array
{
public:
  // = Initialization and termination methods.

  // Define a "trait"
  typedef T value_type;

  // Dynamically create an uninitialized array.  Throws
  // <std::bad_alloc> if allocation fails.
  explicit Array (size_t size);

  // Dynamically initialize an array.  Throws
  // <std::bad_alloc> if allocation fails.
  Array (size_t size, const T &default_value);

  // The copy constructor (performs initialization).  Throws
  // <std::bad_alloc> if allocation fails.
  Array (const Array &s);

  // Assignment operator performs an assignment by making a copy of
  // the contents of parameter <s>, i.e., *this == s will return true.
  // Note that if the <max_size_> of <array_> is >= than <s.cur_size_>
  // we can copy it without reallocating.  However, if <max_size_> is
  // < <s.cur_size_> we must delete the <array_>, reallocate a new
  // <array_>, and then copy the contents of <s>.  Throws
  // <std::bad_alloc> if allocation fails.
  Array &operator= (const Array &s);

  // Clean up the array (e.g., delete dynamically allocated memory).
  ~Array (void);

  // = Set/get methods.

  // Set an item in the array at location index.  Throws
  // <std::out_of_range> if index is out of range, i.e., larger than
  // the size() of the array.
  void set (const T &new_item, size_t index);

  // Get an item in the array at location index.  Throws
  // <std::out_of_range> if index is out of range, i.e., larger than
  // the size() of the array.
  void get (T &item, size_t index) const;

  // Returns a reference to the <index> element in the <Array> without
  // checking for range errors.
  const T &operator[] (size_t index) const;

  // Set an item in the array at location index without
  // checking for range errors.
  T &operator[] (size_t index);

  // Returns the current size of the array.
  size_t size (void) const;

  // Compare this array with <s> for equality.  Returns true if the
  // size()'s of the two arrays are equal and all the elements from 0
  // .. size() are equal, else false.
  bool operator== (const Array &s) const;

  // Compare this array with <s> for inequality such that <*this> !=
  // <s> is always the complement of the boolean return value of
  // <*this> == <s>.
  bool operator!= (const Array &s) const;

private:
  // Returns 1 if <index> is within range, i.e., 0 >= <index> <
  // <cur_size_>, else returns 0.
  bool in_range (size_t index) const;

  // Add other helper methods you see fit here...

  // Maximum size of the array, i.e., the total number of <T> elements
  // in <array_>.
  size_t max_size_;

  // Current size of the array.  This starts out being == to
  // <max_size_>.  However, if we are assigned a smaller array, then
  // <cur_size_> will become less than <max_size_>.  The purpose of
  // keeping track of both sizes is to avoid reallocating memory if we
  // don't have to.
  size_t cur_size_;

  // Pointer to the array's storage buffer.
  T* array_;
};

#if defined (__INLINE__)
#define INLINE inline
#include "Array.inl"
#endif /* __INLINE__ */

#endif /* ARRAY_H */
