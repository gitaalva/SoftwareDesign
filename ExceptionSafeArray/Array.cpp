
#ifndef ARRAY_C
#define ARRAY_C

#include <stdexcept>
#include <memory>
#include <boost/scoped_array.hpp>
#include <algorithm>

#include "Array.h"

#if !defined (__INLINE__)
#define INLINE
#include "Array.inl"
#endif /* __INLINE__ */

Array::Array (size_t size) : cur_size_(size), max_size_(size), array_(new T[size])
{
}

// Dynamically initialize an array.

Array::Array (size_t size, const T &default_value) : cur_size_(size), max_size_(size), array_(new T[size])
{
        for (size_t i=0; i < cur_size_; ++i) {
                array_[i] = default_value;
        }
}

// The copy constructor (performs initialization).

Array::Array (const Array &s) : cur_size_(s.cur_size_), max_size_(s.max_size_), array_(new T[cur_size_])
{
        for (size_t i=0; i < cur_size_; ++i) {
                array_[i] = s.array_[i];
        }
}

// Compare this array with <s> for equality.

bool
Array::operator== (const Array &s) const
{
        if (cur_size_ != s.cur_size_) {
                return false;
        }

        for(int i=0; i < cur_size_; ++i) {
                if (array_[i] != s.array_[i]) return false;
        }
        return true;
}

// Compare this array with <s> for inequality.

bool
Array::operator!= (const Array &s) const
{
        if (cur_size_ != s.cur_size_) {
                return true;
        }
        for(int i=0; i < cur_size_; ++i) {
                if (array_[i] != s.array_[i]) return true;
        }
        return false;
}

// Assignment operator (performs assignment).

Array &
Array::operator= (const Array &s)
{
        if (this == &s) return *this;
        if (s.cur_size_ < max_size_) {
                std::copy(s.array_,s.array_+cur_size_,array_);
        } else {
                Array temp(s);
                std::swap(array_,temp.array_);
                max_size_ = temp.max_size_;

        }
        cur_size_ = s.cur_size_;
        return *this;
}

// Clean up the array (e.g., delete dynamically allocated memory).

Array::~Array (void)
{
        delete[] array_;
}

// = Set/get methods.

// Set an item in the array at location index.  Throws
// <std::out_of_range> if index is out of range, i.e., larger than the
// size() of the array.

void
Array::set (const T &new_item, size_t index)
{
        if(index > cur_size_+1) throw std::out_of_range("index out of range");
        array_[index] = new_item;
        cur_size_ = index;
}

// Get an item in the array at location index.  Throws
// <std::out_of_range> if index is out of range, i.e., larger than the
// size() of the array.

void
Array::get (T &item, size_t index) const
{
        if (index > cur_size_) throw std::out_of_range("index out of range");
        item = array_[index];
}



#endif /* ARRAY_C */
