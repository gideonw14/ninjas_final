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

template<class Derived, class T>
class GuassSiedel
{
	public:
	
		Vector<T> operator ()(const BaseMatrix<MeshMatrix<T>, T>& a_matrix, const Vector<T> &b_vector)
		{
			Vector<T> result(b_vector), old_result;
			
			do 
			{
				old_result = result;
				
				for (unsigned int k = 0; k < result.getSize(); k++)
				{
					T omega = 0;
					
					for (unsigned int j = 0; j < result.getSize(); j++)
						if (j != k)
							omega += a_matrix(k, j) * result[j];
					
					result[k] = (b_vector[k] - omega) / a_matrix(k, k);
				}
			}
			while (((~(result - old_result)) / ~old_result) > 1e-9);
			
			return result;
		}
};

#endif