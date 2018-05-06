//*****************************************************************************
// Programmer: Charles Gaitley         Date: 04/17/2018
// Class: CS 5201                      Section: A
// File: steepestdescent.h
// Description: This file contains a functor that will solve a system of
//              equations with the method of steepest descent.
//*****************************************************************************

#ifndef STEEPESTDESCENT_H
#define STEEPESTDESCENT_H

#include "BaseMatrix.h"

enum STEEP_CONSTANTS
{
  INITIAL_VALUE = 1,
  PERCENTAGE = 100,
  ERROR = 1
};

/// This class contains a functor that will solve a system of equations by the
/// method of steepest descent.
///
/// \pre Assignment operator (=) must be defined for T (T = T).
template <class Derived, class T>
class SteepestDescent
{
  public:
    
    /// Overloaded parentheses operator () that will use the method of
    /// steepest descent to approximate a solution to the system Ax = b.
    ///
    /// \param a_matrix The Matrix that represents A in the system Ax = b.
    /// \param b_vector The Vector that represents b in the system Ax = b.
    ///
    /// \pre a_matrix must be a positive definite Matrix.
    /// \pre Assignment operator (=) must be defined for T with integers 
    ///      (T = int).
    /// \pre Binary division operator (/) must be defined for T (T / T).
    /// \pre Binary multiplication operator (*) must be defined for T with 
    ///      integers (T * int).
    ///
    /// \throws std::domain_error if a_matrix is not a positive definite 
    ///         matrix.
    ///
    /// \return A Vector that is the approximate solution to the system Ax = b.
    Vector<T> operator ()(const BaseMatrix<Derived, T> &a_matrix, const Vector<T> &b_vector)
    {
      // Check that a_matrix is positive definite.
      if (!a_matrix.d_dom()){
        throw domain_error(WRONG_FORM);
      }

      Vector<T> x(b_vector);
      Vector<T> r(b_vector.getSize());
      Vector<T> old_x(b_vector.getSize());

      T a;
      unsigned int count = 0;

      // Perform steepest descent until small error in between x vectors.
      do
      {
        old_x = x;
          
        if (!(count % 5))
        {
          r = b_vector - (a_matrix * x);
        }
        else
        {
          r = r - ((a_matrix * r) * a);
        }

        a = (r * r) / (r * (a_matrix * r));

        x = x + (r * a);
      }
      while (((~(x - old_x)) / ~old_x) > 1e-9);

      return x;
    }
};

#endif