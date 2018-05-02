//*****************************************************************************
// Programmer: Charles Gaitley         Date: 03/14/2018
// Class: CS 5201                      Section: A
// File: mathvector.h
// Description: This file contains a class which represents a mathematical
//              vector.  It inherits from the Array class and adds math 
//              operations such as addition and multiplication.
//*****************************************************************************

#ifndef MATHVECTOR_H
#define MATHVECTOR_H

#include "array.h"

/// This class will represent a Vector in mathematics.  It inherits from the
/// Array class and adds functionality such as vector addition, subtraction,
/// scalar multiplication, and dot product.
///
/// \pre This class inherits from Array. Please check Array's preconditions
///      before instantiating an instance of this class.
template <class T>
class Vector: public Array<T>
{
  public:
    
    /// Default Constructor.  Array default constructor called.
    ///
    /// \post m_size is initialized to 0 with m_data pointing to nothing.
    Vector(): Array<T>() {}

    /// Parametrized Constructor.
    ///
    /// \param size The desired size of constructed Vector.
    ///
    /// \post m_size is now equal to size and the appropriate space has been
    ///       allocated to match this size.
    Vector(const unsigned int &size): Array<T>(size) {}

    /// Copy Constructor.  Array copy constructor called.
    ///
    /// \param vec The vector to be copied to the new Vector being constructed.
    ///
    /// \post A new Vector is created that is an exact copy of vec.
    Vector(const Vector<T> &vec): Array<T>(vec) {}

    /// Move Constructor.  Array move constructor called.
    ///
    /// \param vec The Vector whose data is to be moved to the new Vector being
    ///        created.
    ///
    /// \post All of the data in vec has been moved to the newly created Vector
    ///       and vec has returned to a default state.
    Vector(Vector<T> &&vec): Array<T>(vec) {}

    /// Overloaded assignment operator (=) that will set calling Array equal
    /// to parameter rhs.
    ///
    /// \param rhs The Vector that the calling Vector will be set equal to.
    ///
    /// \return A constant reference to the calling Vector that is now 
    ///         equvalent to rhs to allow for chaining with the assignment 
    ///         operator and its variations.
    const Vector<T>& operator =(const Vector<T> &rhs);

    /// Overloaded add-assignment operator (+=) to perform Vector addition
    /// followed by assignment to calling Vector.
    ///
    /// \param rhs The Vector that will be added to calling Vector.
    ///
    /// \pre Calling Vector and rhs must be the same size.
    /// \pre Add-assignment operator (+=) defined for T (T += T).
    ///
    /// \throws std::length_error if calling object and rhs are not the same
    ///         size.
    ///
    /// \return A constant reference to the calling Vector that has had its
    ///         elements added by the corresponding elements of rhs.
    const Vector<T>& operator +=(const Vector<T> &rhs);

    /// Overloaded subtract-assignment operator (-=) to perform Vector 
    /// subtraction followed by assignment to calling Vector.
    ///
    /// \param rhs The Vector that calling Vector will be subtracted by.
    ///
    /// \pre Calling Vector and rhs must be the same size.
    /// \pre Subtract-assignment operator (-=) defined for T (T -= T).
    ///
    /// \throws std::length_error if calling object and rhs are not the same
    ///         size.
    ///
    /// \return A constant reference to the calling Vector that has had its
    ///         elements subtracted by the elements of rhs.
    const Vector<T>& operator -=(const Vector<T> &rhs);

    /// Overloaded multiplication-assignment operator (*=) for scalar 
    /// multiplication.
    ///
    /// \param scalar The scalar that calling Vector will be multiplied by.
    ///
    /// \pre Multiplication-assignment operator (*=) is defined for T (T *= T).
    ///
    /// \return A constant reference to the calling Vector that has been scaled
    ///         by scalar.
    const Vector<T>& operator *=(const T &scalar);

    /// Overloaded binary operator (*) to find the dot product of two Vectors.
    ///
    /// \param lhs The left-hand Vector used in the calculation of the dot 
    ///        product.
    /// \param rhs The right-hand Vector used in the calculation of the dot 
    ///        product.
    ///
    /// \pre lhs and rhs must be the same size.
    /// \pre Assignment operator (=) must be defined for U with integers 
    ///      (U = int).
    /// \pre Binary operator (*) must be defined for U (U * U).
    /// \pre Addition-assignment operator (+=) must be defined for U (U += U).
    ///
    /// \throws std::length_error if lhs is not the same size as rhs.
    ///
    /// \return The dot product of lhs and rhs represented as a single value of
    ///         the type of both lhs and rhs.
    template <class U>
    friend U operator *(const Vector<U> &lhs, const Vector<U> &rhs);

    /// Overloaded binary operator (*) for scalar multiplication.
    ///
    /// \param lhs The Vector to be scaled.
    /// \param scalar The scalar that lhs will be scaled by.
    ///
    /// \pre This function calls operator *= member function. Be aware of that
    ///      function's requirements before calling operator *.
    ///
    /// \return A Vector that is equivalent to lhs scaled by scalar.
    template <class U>
    friend Vector<U> operator *(Vector<U> lhs, const U &scalar);

    /// Overloaded binary operator (+) to add two Vectors together, but not 
    /// modify either Vector.
    ///
    /// \param lhs The Vector on the left-hand side of binary operator (+)
    ///        being added with rhs.
    /// \param rhs The Vector being added with lhs on the right-hand side of
    ///        the binary operator (+).
    ///
    /// \pre This function calls operator += member function. Be aware of that
    ///      functions requirements before calling operator +.
    ///
    /// \return A Vector whose elements are the sum of the corresponding 
    ///         elements in lhs and rhs.
    template <class U>
    friend Vector<U> operator +(Vector<U> lhs, const Vector<U> &rhs);

    /// Overloaded binary operator (-) to subtract two Vectors together, 
    /// but not modify either Vector.
    ///
    /// \param lhs The Vector on the left-hand side of subtraction operator (-)
    ///        being subtracted by rhs.
    /// \param rhs The Vector lhs is being subtracted by on the right-hand side 
    ///        of the subtraction operator (-).
    ///
    /// \pre This function calls operator -= member function. Be aware of that
    ///      functions requirements before calling operator -.
    ///
    /// \return A Vector whose elements are the difference of the corresponding 
    ///         elements in lhs and rhs.
    template <class U>
    friend Vector<U> operator -(Vector<U> lhs, const Vector<U> &rhs);

    /// Overloaded transpose operator (~) to calculate the magnitude of a
    /// Vector.
    ///
    /// \param vec The Vector to find the magnitude of.
    ///
    /// \pre Assignment operator (=) must be defined for T with integers 
    ///      (T = int).
    /// \pre Add-assignment operator (+=) must be defined for T (T += T).
    /// \pre cmath library function pow() must be defined for T with an integer 
    ///      (pow(T, int)).
    /// \pre cmath library function sqrt() must be defined for T (sqrt(T)).
    ///
    /// \return The magnitude of vec which is defined as the square root of the
    ///         sum of the square of its elements.
    template <class U>
    friend U operator ~(const Vector<U> &vec);
};

#include "mathvector.hpp"

#endif
