//*****************************************************************************
// Programmer: Charles Gaitley         Date: 01/15/2018
// Class: CS 5201                      Section: A
// File: array.h
// Description: This file contains a templated array class that will hold
//              data of a certain type T in a list like collection.
//*****************************************************************************

#ifndef ARRAY_H
#define ARRAY_H

#include "headerconstants.h"

/// This class will store data in a collection that can be accessed via an 
/// index.
///
/// \pre The insertion (<<) and extraction operator (>>) must be defined for T 
///      (ostream << T) and (istream >> T)
/// \pre Assignment operator (=) must be defined for T (T = T).
template <class T>
class Array
{
  public:
  
    /// Default Constructor.
    ///
    /// \post m_data points to nothing and m_size initialized to 0.
    Array(): m_data(NULL), m_size(MIN_SIZE) {}

    /// Parametrized Constructor.
    ///
    /// \param size Which is the desired starting size of this new Array.
    ///
    /// \post m_size is now equal to size and m_data points to a collection of
    ///       the desired size and type of this Array.
    Array(const unsigned int &size);

    /// Copy Constructor.
    ///
    /// \param other Another Array that will be copied into this Array.
    ///
    /// \post This Array is now a copy of Array other.
    Array(const Array<T> &other);

    /// Move Constructor.
    ///
    /// \param other Another Array whose data will be moved to this Array.
    ///
    /// \post Array other's data has been moved to this Array.
    Array(Array<T> &&other);

    /// This function will get the value stored in m_size.
    ///
    /// \return The value stored in m_size.
    unsigned int getSize() const {return m_size;}

    /// This function will set the size of this Array to a user defined value.
    ///
    /// \param size The size that is desired for this new Array.
    ///
    /// \pre This function will destroy all data currently in this Array before
    ///      resizing. Be aware of potential data loss when calling this 
    ///      function.
    ///
    /// \post This Array has been resized to the size of parameter size. The
    ///       Array is also cleared of all data.
    void setSize(const unsigned int &size);

    /// This function will destroy all data in this Array and reset it to an
    /// empty state.
    ///
    /// \post m_size is set to zero and m_data is NULL.
    void clear() {m_size = MIN_SIZE; m_data.reset(); return;}

    /// This function will reverse the elements in the calling Array.
    ///
    /// \pre std::swap Is defined for T (swap(T, T)).
    ///
    /// \post m_data now contains the data it had before, but in reverse order.
    void reverse();

    /// Overload operator [] for read-only access of data in this Array.
    ///
    /// \param index The desired place in the Array for data access.
    ///
    /// \pre index must be in range [0, m_size - 1].
    ///
    /// \throws std::out_of_range if index is greater than m_size - 1 or if
    ///         this Array is empty.
    ///
    /// \return The data stored at specified index.
    const T& operator [](const unsigned int &index) const;

    /// Overload operator [] for read-and-write access to data in this Array.
    ///
    /// \param index The desired place in the Array for data access.
    ///
    /// \pre index must be in range [0, m_size - 1].
    ///
    /// \throws std::out_of_range if index is greater than m_size - 1 or if
    ///         this Array is empty.
    ///
    /// \return A reference to the data stored at specified index so it can be 
    ///         modified.
    T& operator [](const unsigned int &index);

    /// Overload assignment operator (=) for this Array to set it equal to rhs.
    ///
    /// \param rhs The Array to be assigned to this Array.
    ///
    /// \return A constant reference to this Array with rhs's values stored in 
    ///         it to allow for operator chaining. 
    const Array<T>& operator =(Array<T> rhs) {swap(*this, rhs); return *this;}

    /// This function will tell us if the Array is empty or not.
    ///
    /// \return True if the size of this array is zero and therefore empty or
    ///         false otherwise.
    bool isEmpty() const {return m_size == MIN_SIZE;}

    /// This function will check if two Arrays are the same size.
    ///
    /// \param rhs The Array whose size is being compared to the calling Array.
    ///
    /// \return True if the calling Array is the same size as rhs and false
    ///         otherwise.
    bool sameSize(const Array<T> &rhs) const {return m_size == rhs.m_size;}

    /// Conversion operator to convert an Array to a bool.
    ///
    /// \return True if the Array is not empty and false otherwise.
    operator bool() const {return !isEmpty();}

    /// Overloaded equality operator (==) that will see if two Arrays are
    /// equal.
    ///
    /// \param lhs The Array being compared for equality with rhs.
    /// \param rhs The Array being compared for equality with lhs.
    ///
    /// \pre Inequality operator (!=) must be defined for T (T != T).
    ///
    /// \return True if all elements in lhs are the same as all elements in rhs 
    ///         and calling Array and rhs are the same size and false 
    ///         otherwise.
    template <class U>
    friend bool operator ==(const Array<U> &lhs, const Array<U> &rhs);

    /// Overload comparison operator (!=) that will see if two Arrays are
    /// not equal.
    ///
    /// \param lhs The Array being compared for inequality with rhs.
    /// \param rhs The Array being compared for inequality with lhs.
    ///
    /// \pre Inequality operator (!=) must be defined for T (T != T).
    ///
    /// \return The inverse of lhs == rhs.
    template <class U>
    friend bool operator !=(const Array<U> &lhs, const Array<U> &rhs);

    /// Overloaded insertion operator (<<) to insert all data in an Array into
    /// a streaming location.
    /// 
    /// \param out The ostream that streams to where data is to be inserted.
    /// \param rhs The Array whose data will be inserted to where out streams
    ///        to.
    ///
    /// \pre Insertion operator (<<) must be defined for T with an ostream
    ///      (ostream << T).
    ///
    /// \post All of rhs's data has been inserted to the streaming location
    ///       specified by out.
    ///
    /// \return out so that insertion can be chained to insert multiple Arrays
    ///         to the streaming location specified by out.
    template <class U>
    friend ostream& operator <<(ostream &out, const Array<U> &rhs);

    /// Overloaded extraction operator (>>) to extract data to fill an Array
    /// from a streaming location.
    ///
    /// \param in The istream that is streaming from where to extract from.
    /// \param rhs The Array that is getting data read into it from the
    ///        streaming location specified by in.
    ///
    /// \pre Ensure there is enough data in files to completely fill this 
    ///      Array.
    /// \pre Extraction operator (>>) must be defined for T with an istream
    ///      (istream >> T).
    ///
    /// \throws std::invalid_argument if there is not enough data to completely 
    ///         fill this Array.      
    ///
    /// \post rhs Is now completely filled with data from the source specified
    ///       by in.
    ///
    /// \return in So that extraction can be  chained to fill multiple Arrays 
    ///         with data.
    template <class U>
    friend istream& operator >>(istream &in, Array<U> &rhs);

    /// Overloaded std::swap function to accept two arrays.
    ///
    /// \param lhs The Array whose data will be transferred to rhs.
    /// \param rhs The Array whose data will be transferred to lhs.
    ///
    /// \post lhs now contains rhs's data and rhs now contains lhs's data.
    template <class U>
    friend void swap(Array<U> &lhs, Array<U> &rhs);

  protected:
    
    /// A smart pointer containing the data in Array instance.
    unique_ptr<T[]> m_data;
    
    /// Stores the number of elements in Array instance.
    unsigned int m_size;
};

#include "array.hpp"

#endif