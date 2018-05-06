//*****************************************************************************
// Programmers: Charles Gaitley and Gideon Walker	Due Date: 05/06/2018
// Class: CS 5201									Section: A
// File: GenerateBVector.h
// Description: This file contains a functor that will create a vector b for
//              the equation Ax=b based on boundary functions and partitions
//              for an approximation mesh.
//*****************************************************************************

#ifndef GenerateBVector_h
#define GenerateBVector_h

#include "BaseMatrix.h"

/// This class will serve as a functor that will generate a vector b based on
/// templated boundary functions and a desired partition for approximation of
/// a PDE boundary problem.
///
/// \pre Add-assignment operator (+=) is defined for T with double 
///      (T += double).
/// \pre Multiply-assignment operator (*=) is defined for T with double
///      (T *= double).
template <class T, double left_bound(double), double right_bound(double), double upper_bound(double), double lower_bound(double)>
class GenerateBVector
{
public:

	/// Overloaded parentheses operator () that will generate a vector b_vector
	/// based on the desired number of partitions for an approximation mesh for
	/// a PDE boundary problem.
	///
	/// \param partitions The desired number of partitions in the approximation
	///        matrix.
	///
	/// \return A Vector to represent b in the system Ax=b that will be used to
	///         approximate solutions to a PDE.
	Vector<T> operator()(const unsigned int &partitions)
	{
		// Function object and variable.
		Vector<T> b_vector(static_cast<unsigned int>(pow(partitions - 1, 2)));
		unsigned int count = 0;

		// Loop through each row of mesh bottom up.
		for (unsigned int k = 0; k < partitions - 1; k++)
		{
			// Loop through each column of mesh left to right.
			for (unsigned int j = 0; j < partitions - 1; j++)
			{
				b_vector[count] = 0;
				
				// Lower Boundary.
				if (k == 0)
					b_vector[count] += lower_bound(static_cast<double>(j + 1)/partitions);
				
				// Left Boundary.
				if (j == 0)
					b_vector[count] += left_bound(static_cast<double>(k + 1)/partitions);
				
				// Upper Boundary.
				if (k == partitions - 2)
					b_vector[count] += upper_bound(static_cast<double>(j + 1)/partitions);
				
				// Right Boundary.
				if (j == partitions - 2)
					b_vector[count] += right_bound(static_cast<double>(k + 1)/partitions);
				
				b_vector[count] *= 1.0/4;
				count++;
			}
		}

		return b_vector;
	}
};

#endif