//******************************************************************************
// Programmer: Charles Gaitley         Date: 02/15/2018
// Class: CS 5201                      Section: A
// File: array.hpp
// Description: This file contains function definitions for the Array class.
//*****************************************************************************

#ifndef ARRAY_HPP
#define ARRAY_HPP

//*****************************************************************************
// Member Functions
//*****************************************************************************

// Parametrized Constructor.
template <class T>
Array<T>::Array(const unsigned int &size): m_size(size)
{
  m_data.reset(new T[m_size]);
}

// Copy Constructor.
template <class T>
Array<T>::Array(const Array<T> &other): m_size(other.m_size)
{
  m_data.reset(new T[m_size]);

  // Copy other's data into newly constructed Array data
  for (unsigned int k = 0; k < m_size; k++)
    m_data[k] = other.m_data[k];
}

// Move Constructor.
template <class T>
Array<T>::Array(Array<T> &&other): m_data(move(other.m_data)), 
                                   m_size(other.m_size)
{
  other.m_data.reset(NULL);
  other.m_size = MIN_SIZE;
}

// Sets the size of this Array and clears all data currently in this Array if
// size is not equal to m_size.
template <class T>
void Array<T>::setSize(const unsigned int &size)
{
  m_size = size;
  m_data.reset(new T[m_size]);
  
  return;
}

// Returns A copy of this Array with its elements in reverse.
template <class T>
void Array<T>::reverse()
{
  // Assign calling object's elements to reversed in reverse order.
  for (unsigned int k = 0; k < m_size / 2; k++)
    swap(m_data[k], m_data[m_size - k - 1]);

  return;
}

// Read-only overload of operator [].
template <class T>
const T& Array<T>::operator [](const unsigned int &index) const
{
  // Check for out-of-bounds index.
  if (isEmpty() || index > m_size - 1)
    throw out_of_range(OUT_OF_RANGE);

  return m_data[index];
}

// Read-and-write overload of operator [].
template <class T>
T& Array<T>::operator [](const unsigned int &index)
{
  // Check for out-of-bounds index.
  if (isEmpty() || index > m_size - 1)
    throw out_of_range(OUT_OF_RANGE);

  return m_data[index];
}

//*****************************************************************************
// Friend Function
//*****************************************************************************

// Overload comparison operator (==).
template <class T>
bool operator ==(const Array<T> &lhs, const Array<T> &rhs)
{
  // Check that lhs and rhs are the same size.
  if (!lhs.sameSize(rhs))
    return false;

  // Check that each element in lhs and rhs are the same.
  for (unsigned int k = 0; k < lhs.m_size; k++)
    // Compare elements.
    if (lhs.m_data[k] != rhs.m_data[k])
      return false;

  return true;
}

// Overloaded comparison operator (!=).
template <class T>
bool operator !=(const Array<T> &lhs, const Array<T> &rhs) 
{
  return !(lhs == rhs);
}

// Overloaded insertion operator (<<).
template <class T>
ostream& operator <<(ostream &out, const Array<T> &rhs)
{
  // Insert all data in rhs's m_data to the location specified by out.
  for (unsigned int k = 0; k < rhs.m_size; k++)
    out << rhs.m_data[k] << endl;
  
  return out;
}

// Overloaded extraction operator (>>).
template <class T>
istream& operator >>(istream &in, Array<T> &rhs)
{
  // Extract data into rhs's m_data from the location specified by in.
  for (unsigned int k = 0; k < rhs.m_size; k++)
    // Check for no more data to read.
    if (!(in >> rhs.m_data[k]))
      throw invalid_argument(INVALID_DATA);

  return in;
}

// Overloaded std::swap for the Array class.
template <class T>
void swap(Array<T> &lhs, Array<T> &rhs)
{
  swap(lhs.m_size, rhs.m_size);
  swap(lhs.m_data, rhs.m_data);

  return;
}

#endif