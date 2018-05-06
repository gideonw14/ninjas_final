//*****************************************************************************
// Programmers: Charles Gaitley and Gideon Walker	Date: 05/04/2018
// Class: CS 5201                                   Section: A
// File: GuassSiedel.h
// Description: This file contains a functor that with solve a linear system
//              by the Guass-Siedel iterative method.
//*****************************************************************************

#ifndef GUASSSIEDEL_H
#define GUASSSIEDEL_H

#include "BaseMatrix.h"

/// This functor will solve a linear system by the Guass Siedel method and
/// output the number of iterations to do it.
///
/// \pre Assignment operator (=) must be defined for T (T = T).
template<class Derived, class T>
class GuassSiedel
{
	public:
	
		/// Overloaded parentheses operator () that will solve a linear system
		/// by the Guass Siedel method and output the number of iterations it
		/// took to do it.
		///
		/// \param a_matrix The matrix A in the equation Ax=b.
		/// \param b_vector The Vector b in the equation Ax=b.
		///
		/// \pre a_matrix must be positive definite.
		/// \pre Assignment operator (=) must be defined for T with integers 
		///      (T = int).
		/// \pre Add-assignment operator (+=) must be defined for T (T += T).
		/// \pre Binary operator (-) must be defined for T (T - T).
		/// \pre Binary operator (*) must be defined for T (T * T).
		/// \pre Binary operator (/) must be defined for T (T / T).
		/// \pre Comparison operator (>) must be defined for T with double 
		///      (T > double).
		///
		/// \throws std::domain_error if a_matrix is not positive definite.
		///
		/// \return A Vector that is the approximate solution x to the system
		///         Ax=b.
		Vector<T> operator ()(const BaseMatrix<MeshMatrix<T>, T>& a_matrix, const Vector<T> &b_vector)
		{
			// Check that a_matrix is positive definite.
	    	if (!a_matrix.p_def()){
	        	throw domain_error(WRONG_FORM);
	    	}
			
			// Function objects and variables.
			Vector<T> result(b_vector), old_result;
			T omega;
			unsigned long iterations = 0;
			
			// Iterated until convergence.
			do 
			{
				iterations++;
				old_result = result;
				
				// Calculate approximation for solution.
				for (unsigned int k = 0; k < result.getSize(); k++)
				{
					omega = 0;
					
					// Determine omega for current iteration.
					for (unsigned int j = 0; j < result.getSize(); j++)
						if (j != k)
							omega += a_matrix(k, j) * result[j];
					
					result[k] = (b_vector[k] - omega) / a_matrix(k, k);
				}
			}
			while (((~(result - old_result)) / ~old_result) > 1e-9);
			cout << "GuassSiedel iterations: " << iterations << endl;
			return result;
		}
};

#endif