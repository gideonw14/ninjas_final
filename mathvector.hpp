//*****************************************************************************
// Programmer: Charles Gaitley         Date: 03/14/2018
// Class: CS 5201                      Section: A
// File: mathvector.hpp
// Description: Contains member function definitions for the Vector class.
//*****************************************************************************

#ifndef MATHVECTOR_HPP
#define MATHVECTOR_HPP

//*****************************************************************************
// Member Functions
//*****************************************************************************

// Overloaded assignment operator (=).
template <class T>
const Vector<T>& Vector<T>::operator =(const Vector<T> &rhs)
{
  Array<T>::operator =(rhs);

  return *this;
}

// Overloaded add-assignment operator (+=).
template <class T>
const Vector<T>& Vector<T>::operator +=(const Vector<T> &rhs)
{
  // Check that calling Vector is the same size as rhs.
  if (!(*this).sameSize(rhs))
    throw length_error(INCOMPATIBLE_LENGTH);

  // Add all elements in rhs to calling Vector's elements.
  for (unsigned int k = 0; k < rhs.m_size; k++)
    (*this)[k] += rhs.m_data[k];

  return *this;
}

// Overloaded subtract-assignment operator (-=).
template <class T>
const Vector<T>& Vector<T>::operator -=(const Vector<T> &rhs)
{
  // Check that calling Vector is the same size as rhs.
  if (!(*this).sameSize(rhs))
    throw length_error(INCOMPATIBLE_LENGTH);

  // Add all elements in rhs to calling Vector's elements.
  for (unsigned int k = 0; k < rhs.m_size; k++)
    (*this)[k] -= rhs.m_data[k];

  return *this;
}

// Overloaded multiplication-assignment operator (*=).
template <class T>
const Vector<T>& Vector<T>::operator *=(const T &scalar)
{
  // Multiply each element by scalar.
  for (unsigned int k = 0; k < (*this).getSize(); k++)
    (*this)[k] *= scalar;

  return *this;
}

//*****************************************************************************
// Friend Functions
//*****************************************************************************

// Overloaded binary operator (*) for dot product.
template <class T>
T operator *(const Vector<T> &lhs, const Vector<T> &rhs)
{
  // Check that lhs is same length as rhs.
  if (!lhs.sameSize(rhs))
    throw length_error(INCOMPATIBLE_LENGTH);

  // Function Variable.
  T result = 0;

  // Multiply each element and add them together.
  for (unsigned int k = 0; k < lhs.m_size; k++)
    result += lhs.m_data[k] * rhs.m_data[k];

  return result;
}

// Overloaded binary operator (*) for scalar multiplication.
template <class T>
Vector<T> operator *(Vector<T> lhs, const T &scalar) {return lhs *= scalar;}

// Overloaded binary operator (+).
template <class T>
Vector<T> operator +(Vector<T> lhs, const Vector<T> &rhs) {return lhs += rhs;}

// Overloaded binary operator (-).
template <class T>
Vector<T> operator -(Vector<T> lhs, const Vector<T> &rhs) {return lhs -= rhs;}

// Overloaded transpose operator (~).
template <class T>
T operator ~(const Vector<T> &vec)
{
  T mag = 0;

  // Add the squares of all elements in vec.
  for (unsigned int k = 0; k < vec.getSize(); k++)
    mag += pow(vec[k], 2);

  return sqrt(mag);
}

#endif