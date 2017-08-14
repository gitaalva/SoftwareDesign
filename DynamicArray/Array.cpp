
#ifndef ARRAY_CPP
#define ARRAY_CPP

#include <sys/types.h>

#include <algorithm>
#include <memory>
#include <sstream>

#include "Array.h"

#if !defined (__INLINE__)
#define INLINE
#include "Array.inl"
#endif /* __INLINE__ */

template <typename T> 
Array<T>::Array (size_t size) : cur_size_ (size), max_size_ (size), array_ (new T[size])
{
}

template <typename T> 
Array<T>::Array (size_t size, 
		 const T &default_value) : cur_size_ (size), max_size_ (size) , default_value_ (new T(default_value)), array_(new T[size])
{
	std::fill(array_.get(), array_.get()+cur_size_,default_value);
}

// The copy constructor (performs initialization).

template <typename T> 
Array<T>::Array (const Array<T> &s) : cur_size_(s.size()), max_size_(s.size()), array_(new T[s.size()])
{
	if (s.default_value_) default_value_.reset (new T(s.default_value_));
	std::copy (s.begin(),s.end(),array_.get());
}

template <typename T> void
Array<T>::resize (size_t new_size)
{
	if (new_size == cur_size_) return;
	else if (new_size < cur_size_) {
		cur_size_ = new_size;
	}
	else {
		if (new_size < max_size_ && default_value_.get())  {
			std::fill (array_.get()+cur_size_, array_.get()+new_size, *default_value_.get());
			cur_size_ = new_size;
		}
		else {
			scoped_array<T> new_array (new T[new_size]);
			std::copy (begin(),end(),new_array.get());
			if (default_value_.get())
				std::fill (new_array.get()+cur_size_,new_array.get()+new_size, *default_value_.get());
			array_.swap (new_array);
			cur_size_ = max_size_ = new_size;
		}
	}
}

template <typename T> void
Array<T>::swap (Array<T> &new_array)
{
	std::swap (cur_size_,new_array.cur_size_);
	std::swap (max_size_,new_array.max_size_);
	default_value_.swap(new_array.default_value_);
	array_.swap(new_array.array_);
}

// Assignment operator (performs assignment). 

template <typename T> Array<T> &
Array<T>::operator= (const Array<T> &s)
{
	if (this == &s) return *this;
	Array<T> temp(s);
	swap(temp);
	return *this;
}

// Clean up the array (e.g., delete dynamically allocated memory).

template <typename T> 
Array<T>::~Array (void)
{
}

// = Set/get methods.

// Set an item in the array at location index.  

template <typename T> void
Array<T>::set (const T &new_item, size_t index)
{
	if (index >= cur_size_) {
		resize(index+1);
	}//throw std::out_of_range("Index out of range");
	array_[index] = new_item;
}

// Get an item in the array at location index.

template <typename T> void
Array<T>::get (T &item, size_t index)
{
	if (index >= cur_size_) throw std::out_of_range("Index out of range");
	item = array_[index];
}

// Compare this array with <s> for equality.

template <typename T> bool
Array<T>::operator== (const Array<T> &s) const
{
	return cur_size_ == s.cur_size_ && std::equal(begin(),end(),s.begin());
}

// Compare this array with <s> for inequality.

template <typename T> bool
Array<T>::operator!= (const Array<T> &s) const
{
	return !(cur_size_ == s.cur_size_ && std::equal(begin(),end(),s.begin()));
}

template <typename T>
Array_Iterator<T>::Array_Iterator (Array<T> &array, size_t pos) : array_ (array), pos_ (pos)
{
}

template <typename T>
Const_Array_Iterator<T>::Const_Array_Iterator (const Array<T> &array, size_t pos) : array_ (array), pos_ (pos)
{
}

#endif /* ARRAY_CPP */
