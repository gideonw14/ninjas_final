//*****************************************************************************
// Programmers: Charles Gaitley and Gideon Walker	Due Date: 05/06/2018
// Class: CS 5201                                   Section: A
// File: GeneralMatrix.h
// Description: This file contains a matrix that defines a generalized square
//              matrix with no other special properties.
//*****************************************************************************

#ifndef GENERALMATRIX_H
#define GENERALMATRIX_H

#include "BaseMatrix.h"

// Class Protoypes.
template<class Derived, class T> class BaseMatrix;
template<class T> class GeneralMatrix;

/// This class represents a generalized square matrix with no other special
/// functionality.
///
/// \pre Same as BaseMatrix. Check these before instantiating a GeneralMatrix.
template<class T>
class GeneralMatrix: public BaseMatrix<GeneralMatrix<T>, T>{
public:

	/// Default Constructor.
	///
	/// \pre This constructor calls BaseMatrix default constructor. Check this
	///      constructor's requirements before calling GeneralMatrix default 
	///      constructor.
	///
	/// \post A new GeneralMatrix is constructed in its empty state.
	GeneralMatrix(): BaseMatrix<GeneralMatrix<T>, T>() {}
	
	/// Parametrized Constructor.
	///
	/// \param new_size The desired size of newly constructed GeneralMatrix.
	///
	/// \pre This constructor calls BaseMatrix parametrized constructor. Check 
	///      this constructor's requirements before calling GeneralMatrix 
	///      default constructor.
	///
	/// \post A new GeneralMatrix is constructed with new_size x new_size 
	///       storage.
	GeneralMatrix(const unsigned int& new_size): BaseMatrix<GeneralMatrix<T>, T>(new_size) {}
	
	/// Copy Constructor.
	///
	/// \param other The GeneralMatrix that new GeneralMatrix will be a copy
	///        of.
	///
	/// \pre This constructor calls BaseMatrix copy constructor. Check this
	///      constructor's requirements before calling GeneralMatrix copy 
	///      constructor.
	///
	/// \post A new GeneralMatrix is constructed that is a copy of other.
	GeneralMatrix(const GeneralMatrix<T>& other): BaseMatrix<GeneralMatrix<T>, T>(other) {}
	
	/// Move Constructor.
	///
	/// \param other The GeneralMatrix whose data will be moved into new
	///        GeneralMatrix.
	///
	/// \pre This constructor calls BaseMatrix move constructor. Check this
	///      constructor's requirements before calling GeneralMatrix move
	///      constructor.
	///
	/// \post A new GeneralMatrix is constructed that with other's data moved 
	///       into it.
	GeneralMatrix(GeneralMatrix<T>&& other): BaseMatrix<GeneralMatrix<T>, T>(other) {}
	
	/// Overloaded assignment operator (=) that will set one GeneralMatrix 
	/// equal to another GeneralMatrix.
	///
	/// \param other The GeneralMatrix that calling GeneralMatrix will be set
	///        equal to.
	///
	/// \pre This function calls BaseMatrix operator =. Be aware of this
	///      function's requirements before calling operator =.
	///
	/// \return A reference to calling GeneralMatrix that is now equal to
	///         other.
	GeneralMatrix<T>& operator=(const GeneralMatrix<T>& other){
		BaseMatrix<GeneralMatrix<T>, T>::operator =(other);
		return *this;
	}
};

#endif