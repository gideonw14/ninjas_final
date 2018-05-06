//*******************************************************************************
// Programmers: Charles Gaitley and Gideon Walker 	Due Date: 05/06/2018
// Class: CS 5201                                   Section: A
// File: BaseMatrix.h
// Description: This file contains the class BaseMatrix which will serve as a 
//              static interface base class for all matrices. 
//*******************************************************************************

#ifndef BASEMATRIX_H
#define BASEMATRIX_H

#include "mathvector.h"
#include "GeneralMatrix.h"

// Class Prototypes.
template<class Derived, class T> class BaseMatrix;
template<class T> class GeneralMatrix;

// Keep your friends from backstabbing you.
template<class Derived, class T> ostream& operator<<(ostream& os, const BaseMatrix<Derived, T>& matrix);
template<class Derived, class T> istream& operator>>(istream& is, BaseMatrix<Derived, T>& matrix);
template<class Derived, class T> void swap(BaseMatrix<Derived, T>& left, BaseMatrix<Derived, T>& right);

/// This class represents any matrix. It will serve as a static interface base
/// for any matrix class that derives from it.
///
/// \pre Assignment operator (=) must be defined for T.
/// \pre Keep in mind that this Matrix defaults to a square matrix.
template<class Derived, class T>
class BaseMatrix{
private:

	/// This function will convert a BaseMatrix templeted on any derived Matrix 
	/// type to a BaseMatrix templated on a GeneralMatrix.
	///
	/// \param other The BaseMatrix to be converted to a BaseMatrix templated
	///        on a GeneralMatrix.
	///
	/// \return A BaseMatrix templated on a GeneralMatrix that is equivalent
	///         to other.
	BaseMatrix<GeneralMatrix<T>, T> convert_to_general(const BaseMatrix<Derived, T>& other) const;

protected:
	
	/// This member variable will hold all data for any Matrix deriving from
	/// this class.
	Vector<Vector<T>> grid;
	
	/// This member variable will store the size n of an n x n matrix.
	unsigned int size;
	
public:

	/// Default Constructor.
	///
	/// \post BaseMatrix is set to an empty state with nothing in grid and
	///       size equal to 0.
	BaseMatrix(): size(MIN_SIZE) {}

	/// Parametrized Constructor.
	///
	/// \param new_size The desired size of newly constructed BaseMatrix.
	///
	/// \post A new BaseMatrix is created with new_size x new_size storage.
	BaseMatrix(const unsigned int& new_size) {set_size(new_size);}

	/// Copy Constructor.
	///
	/// \param other The BaseMatrix that newly created BaseMatrix will be a
	///        copy of.
	///
	/// \post A new BaseMatrix is created that is an exact clone of other.
	BaseMatrix(const BaseMatrix<Derived, T>& other) {*this = other;}

	/// Move Constructor.
	///
	/// \param other The BaseMatrix whose data will be moved to newly created
	///        BaseMatrix.
	///
	/// \post A new BaseMatrix is created that has all data that used to be
	///       stored in other.
	BaseMatrix(BaseMatrix<Derived, T>&& other);

	/// Overloaded assignment operator that will set two BaseMatrix objects
	/// equal to each other.
	///
	/// \param other The BaseMatrix calling BaseMatrix will be set equal to.
	///
	/// \pre This function calls the equal function. Be aware of this 
	///      function's requirements before calling operator =.
	///
	/// \return A reference to calling BaseMatrix that is now equal to other.
	BaseMatrix<Derived, T>& operator=(const BaseMatrix<Derived, T>& other);

	/// Overloaded multiply-assignment operator (*=) that will assign calling
	/// BaseMatrix to itself times a scalar.
	///
	/// \param scalar The scalar with which to scale calling BaseMatrix.
	///
	/// \pre This function calls the scalar_multiply_assign function. Be aware 
	///      of this function's requirements before calling operator *=.
	///
	/// \return A reference to calling BaseMatrix that is now equal to itself
	///         scaled by scalar.
	BaseMatrix<Derived, T>& operator*=(const T& scalar);

	/// Overloaded add-assignment operator (+=) that will assign calling
	/// BaseMatrix to itself added with another BaseMatrix.
	///
	/// \param other The BaseMatrix that will be added to calling BaseMatrix.
	///
	/// \pre This function calls the add_assign function. Be aware of this 
	///      function's requirements before calling operator +=.
	///
	/// \return A reference to calling BaseMatrix that is now equal to itself
	///         added with other.
	BaseMatrix<Derived, T>& operator+=(const BaseMatrix<Derived, T>& other);

	/// Overloaded subtract-assignment operator (-=) that will assign calling
	/// BaseMatrix to itself subtracted by another BaseMatrix.
	///
	/// \param other The BaseMatrix that calling BaseMatrix will be subtracted
	///        by.
	///
	/// \pre This function calls the subtract_assign function. Be aware of this 
	///      function's requirements before calling operator =.
	///
	/// \return A reference to calling BaseMatrix that is now equal to itself
	///         subtracted by other.
	BaseMatrix<Derived, T>& operator-=(const BaseMatrix<Derived, T>& other);

	/// Overloaded binary operator (*) for Vector multiplication.
	///
	/// \param vector The Vector that calling BaseMatrix will be multiplied by.
	///
	/// \pre This function calls the vector_multiply function. Be aware of this 
	///      function's requirements before calling operator *.
	///
	/// \return A Vector that is equivalent to calling BaseMatrix multiplied by
	///         vector.
	Vector<T> operator*(const Vector<T>& vector) const;

	/// Overloaded binary operator (*) for scalar multiplication.
	///
	/// \param scalar The to scale calling BaseMatrix by.
	///
	/// \pre This function calls the scalar_multiply function. Be aware of this 
	///      function's requirements before calling operator *.
	///
	/// \return A copy of a BaseMatrix that is equivalent to calling BaseMatrix
	///         scaled by scalar.
	BaseMatrix<Derived, T> operator*(const T& scalar) const;
	
	/// Overloaded binary operator (*) for BaseMatrix multiplication.
	///
	/// \param other The BaseMatrix that will be multiplied with calling 
	///        BaseMatrix.
	///
	/// \pre This function calls the multiply function. Be aware of this 
	///      function's requirements before calling operator *.
	///
	/// \return A copy of a BaseMatrix templated on a GeneralMatrix that is
	///         equivalent to calling BaseMatrix multiplied by other.
	BaseMatrix<GeneralMatrix<T>, T> operator*(const BaseMatrix<Derived, T>& other) const;

	/// Overloaded binary operator (+) for BaseMatrix addition.
	///
	/// \param other The BaseMatrix that will be added to calling BaseMatrix.
	///
	/// \pre This function calls the add function. Be aware of this function's 
	///      requirements before calling operator +.
	///
	/// \return A copy of a BaseMatrix that is equivalent to calling BaseMatrix
	///         added with other.
	BaseMatrix<Derived, T> operator+(const BaseMatrix<Derived, T>& other) const;

	/// Overloaded binary operator (-) for BaseMatrix subtraction.
	///
	/// \param other The BaseMatrix that will be subtracted from calling 
	///        BaseMatrix.
	///
	/// \pre This function calls the subtract function. Be aware of this 
	///      function's requirements before calling operator -.
	///
	/// \return A copy of a BaseMatrix that is equivalent to calling BaseMatrix
	///         subtracted by other.
	BaseMatrix<Derived, T> operator-(const BaseMatrix<Derived, T>& other) const;

	/// Overloaded transpose operator (~) that will calculate the transpose of
	/// calling BaseMatrix.
	///
	/// \pre This function calls the transpose function. Be aware of this 
	///      function's requirements before calling operator ~.
	///
	/// \return A copy of a BaseMatrix that is equivalent to the transpose of
	///         calling BaseMatrix.
	BaseMatrix<Derived, T> operator~() const;

	/// Overloaded parentheses operator () to access an element in calling
	/// BaseMatrix with read-and-write access.
	///
	/// \param height The row where desired data is stored.
	/// \param width The column where desired data is stored.
	///
	/// \pre This function calls the non-const get_data function. Be aware of 
	///      this function's requirements before calling operator ().
	///
	/// \return A reference to data stored at height and width so that is can
	///         be modified.
	T& operator()(const unsigned int& height, const unsigned int& width);

	/// Overloaded parentheses operator () to access an element in calling
	/// BaseMatrix with read-only access.
	///
	/// \param height The row where desired data is stored.
	/// \param width The column where desired data is stored.
	///
	/// \pre This function calls the const get_data function. Be aware of 
	///      this function's requirements before calling operator ().
	///
	/// \return A constant reference to data stored at height and width so that
	///         it can only be read and not modified.
	const T& operator()(const unsigned int& height, const unsigned int& width) const;

	/// This function will set the size of calling BaseMatrix to a new size.
	///
	/// \param new_size The new size that calling BaseMatrix will be set equal
	///        to.
	///
	/// \pre This function calls the set_size_derived function. Be aware of 
	///      this function's requirements before calling set_size.
	///
	/// \post Calling BaseMatrix has been resized to new_size x new_size.
	void set_size(const unsigned int& new_size);

	/// This function will retrieve the size of calling BaseMatrix.
	///
	/// \return The size of calling BaseMatrix.
	unsigned int get_size() const {return asDerived().get_size_derived();}
	
	/// This function will determine if calling BaseMatrix is symmetric and
	/// diagonally dominant. In other words, positive definite.
	///
	/// \pre This function calls the p_def_derived function. Be aware of 
	///      this function's requirements before calling p_def.
	///
	/// \return True if calling BaseMatrix is positive definite and false
	///         otherwise.
	bool p_def() const {return asDerived().p_def_derived();}
	
	/// This function will return a BaseMatrix to its default, empty state.
	///
	/// \pre This function calls the erase function. Be aware of this 
	///      function's requirements before calling clear.
	///
	/// \post All data has been cleaned from calling BaseMatrix and the
	///       BaseMatrix is now in its default empty state.
	void clear() {asDerived().erase(); return;}
	
	/// This function will determine if calling BaseMatrix is empty or not.
	///
	/// \pre This function calls the is_empty_derived function. Be aware of 
	///      this function's requirements before calling is_empty.
	///
	/// \return True if calling BaseMatrix contains no data and false 
	///         otherwise.
	bool is_empty() const {return asDerived().is_empty_derived();}
	
	/// This function will cast calling BaseMatrix as its derived matrix type 
	/// that is modifable.
	///
	/// \return A reference to calling BaseMatrix casted as its derived matrix
	///         type.
	Derived& asDerived(){return static_cast<Derived&>(*this);}
	
	/// This function will cast calling BaseMatrix as its derived matrix type 
	/// that is not modifable.
	///
	/// \return A constant reference to calling BaseMatrix casted as its 
	///         derived matrix type.
	const Derived& asDerived() const {return static_cast<const Derived&>(*this);}
	
	/// This function is the default implementation for the assignment operator 
	/// (=).
	///
	/// \param other The BaseMatrix that will be set equal to calling 
	///        BaseMatrix.
	///
	/// \return A reference to calling BaseMatrix that is now equal to other.
	BaseMatrix<Derived, T>& equal(const BaseMatrix<Derived, T>& other);
	
	/// This function is the default implementation for the multiply-assignment
	/// operator (*=).
	///
	/// \param scalar The value with which to scale calling BaseMatrix by.
	///
	/// \pre This function calls Vector multiply-assignment operator (*=). Be 
	///      aware of this function's requirements before calling 
	///      scalar_multiply_assign.
	///
	/// \return A reference to calling BaseMatrix which is now equal to itself
	///         scaled by scalar.
	BaseMatrix<Derived, T>& scalar_multiply_assign(const T& scalar);
	
	/// This function is the default implementation for the add-assignment
	/// operator (+=).
	///
	/// \param other The BaseMatrix that will be added to calling BaseMatrix.
	///
	/// \pre other and calling BaseMatrix must be the same size.
	/// \pre This function calls Vector add-assignment operator (+=). Be aware 
	///      of this function's requirements before calling add_assign.
	///
	/// \throws std::invalid_argument if other is not the same size as calling
	///         BaseMatrix.
	///
	/// \return A reference to calling BaseMatrix which is now equal to itself
	///         plus other.
	BaseMatrix<Derived, T>& add_assign(const BaseMatrix<Derived, T>& other);
	
	/// This function is the default implementation for the subtract-assignment
	/// operator (-=).
	///
	/// \param other The BaseMatrix that will be subtracted from calling 
	///        BaseMatrix.
	///
	/// \pre other and calling BaseMatrix must be the same size.
	/// \pre This function calls Vector subtract-assignment operator (-=). Be 
	///      aware of this function's requirements before calling 
	///      subtract_assign.
	///
	/// \throws std::invalid_argument if other is not the same size as calling
	///         BaseMatrix.
	///
	/// \return A reference to calling BaseMatrix which is now equal to itself
	///         minus other.
	BaseMatrix<Derived, T>& subtract_assign(const BaseMatrix<Derived, T>& other);
	
	/// This function is the default implementation for binary operator (*) for 
	/// Vector multiplication.
	///
	/// \param vector The Vector that calling BaseMatrix will be multiplied by.
	///
	/// \pre vector must have the same number of elements as calling 
	///      BaseMatrix's size.
	/// \pre Binary operator (*) must be defined for T (T * T).
	/// \pre Add-assignment operator (+=) must be defined for T (T += T).
	///
	/// \throws std::invalid_argument if vector does not have the same number of
	///         elements as calling BaseMatrix's size.
	///
	///	\return A Vector that is equivalent to calling BaseMatrix times vector. 
	Vector<T> vector_multiply(const Vector<T>& vector) const;
	
	/// This function is the default implementation for binary operator (+) for
	/// BaseMatrix addition.
	///
	/// \param other The BaseMatrix that will be added to calling BaseMatrix.
	///
	/// \pre This function calls operator +=. Be aware of this function's
	///      requirements before calling add.
	///
	/// \return A BaseMatrix that is a copy of calling BaseMatrix added with
	///         other.
	BaseMatrix<Derived, T> add(const BaseMatrix<Derived, T>& other) const;
	
	/// This function is the default implementation for binary operator (-) for
	/// BaseMatrix subtraction.
	///
	/// \param other The BaseMatrix that will be subtracted from calling 
	///        BaseMatrix.
	///
	/// \pre This function calls operator -=. Be aware of this function's
	///      requirements before calling subtract.
	///
	/// \return A BaseMatrix that is a copy of calling BaseMatrix subtracted by
	///         other.
	BaseMatrix<Derived, T> subtract(const BaseMatrix<Derived, T>& other) const;
	
	/// This function is the default implementation for binary operator (*) for
	/// BaseMatrix multiplication.
	///
	/// \param other The BaseMatrix that calling BaseMatrix will be multiplied 
	///        by.
	///
	/// \pre Calling BaseMatrix and other must be the same size.
	/// \pre Binary operator (*) must be defined for T (T * T).
	/// \pre Add-assignment operator (+=) must be defined for T (T += T).
	///
	/// \throws std::invalid_argument if other's size does not match calling
	///         BaseMatrix size.
	///
	/// \return A BaseMatrix that is a copy of calling BaseMatrix times other.
	BaseMatrix<GeneralMatrix<T>, T> multiply(const BaseMatrix<Derived, T>& other) const;
	
	/// This function is the default implementation for binary operator (*) for
	/// scalar multiplication.
	///
	/// \param scalar The amount to scale calling BaseMatrix by.
	///
	/// \pre This function calls Vector multiply-assignment operator (*=) for 
	///      scalar multiplication. Be aware of this function's requirements
	///      before calling this function.
	///
	/// \return A BaseMatrix that is a copy of calling BaseMatrix scaled by
	///         scalar.
	BaseMatrix<Derived, T> scalar_multiply(const T& scalar) const;
	
	/// This function is the default implementation for transpose operator (~)
	/// that will calculate the transpose of calling BaseMatrix.
	///
	/// \return A BaseMatrix that is a copy of the transpose of calling 
	///         BaseMatrix.
	BaseMatrix<Derived, T> transpose() const;
	
	/// This function is the default implementation for parentheses operator ()
	/// for read-and-write access of data in calling BaseMatrix.
	///
	/// \param height The row where desired data is stored.
	/// \param width The column where desired data is stored.
	///
	/// \pre Calling BaseMatrix must not be empty.
	/// \pre height or width must not exceed size - 1.
	///
	/// \throws std::invalid_argument if calling BaseMatrix is empty or height
	///         or width exceeds size - 1.
	///
	/// \return A reference to data at height and width so that it can be 
	///         modified.
	T& get_data(const unsigned int& height, const unsigned int& width);
	
	/// This function is the default implementation for parentheses operator ()
	/// for read-only access of data in calling BaseMatrix.
	///
	/// \param height The row where desired data is stored.
	/// \param width The column where desired data is stored.
	///
	/// \pre Calling BaseMatrix must not be empty.
	/// \pre height or width must not exceed size - 1.
	///
	/// \throws std::invalid_argument if calling BaseMatrix is empty or height
	///         or width exceeds size - 1.
	///
	/// \return A constant reference to data at height and width so that it can 
	///         not be modified.
	const T& get_data(const unsigned int& height, const unsigned int& width) const;
	
	/// This function is the default implementation of the p_def function.
	///
	/// \pre Be aware that this function will return true for an empty 
	///      BaseMatrix.
	/// \pre Assignment operator (=) must be defined for T with integers 
	///      (T = int).
	/// \pre cmath library function fabs must be defined for T (fabs(T)).
	/// \pre Inequality operator (!=) must be defined for T (T != T).
	/// \pre Comparison operator (>) must be defined for T (T > T).
	/// \pre Add-assignment operator (+=) must be defined for T (T += T).
	///
	/// \return True if calling BaseMatrix is positive definite and false
	///         otherwise.
	bool p_def_derived() const;
	
	/// This function is the default implementation of the set_size function.
	///
	/// \param new_size The desired size of calling BaseMatrix.
	///
	/// \pre Be aware that calling this function will erase all data currently
	///      in calling BaseMatrix.
	///
	/// \post Calling BaseMatrix can now store new_size x new_size amount of
	///       data.
	void set_size_derived(const unsigned int& new_size);
	
	/// This function is the default implementation of the get_size function.
	///
	/// \return The size of calling BaseMatrix.
	unsigned int get_size_derived() const {return size;}
	
	/// This function is the default implementation of the clear function.
	///
	/// \post Calling BaseMatrix has been reset to its default, empty state.
	void erase() {size = MIN_SIZE; grid.clear(); return;}
	
	/// This function is the default implementation of the is_empty function.
	///
	/// \return True if size of calling BaseMatrix is not zero and false 
	///         otherwise.
	bool is_empty_derived() const {return size == MIN_SIZE;}
	
	/// Overloaded insertion operator (<<) that will insert data from a 
	/// BaseMatrix formatted appropriately to an output stream source.
	///
	/// \param os The output stream to insert data into.
	/// \param matrix The BaseMatrix whose data will be inserted to os.
	///
	/// \pre All data in matrix will be inserted to os. Ensure matrix is
	///      completely filled to avoid strange results.
	///
	/// \return os So the insertion operator can be chained to insert other
	///         data into os.
	friend ostream& operator<<<Derived, T>(ostream& os, const BaseMatrix& matrix);

	/// Overloaded extraction operator (>>) that will collect input from an
	/// istream and store it in a BaseMatrix.
	///
	/// \param is The istream to extract data from.
	/// \param matrix The BaseMatrix that will have data extracted into it.
	/// 
	/// \pre There must be enough data in is to completely fill matrix.
	///
	/// \throws std::invalid_argument if there is not enough data in is to
	///         completely fill matrix.
	///
	/// \return is So the extraction operator can be chained to extract other
	///         data from is.
	friend istream& operator>><Derived, T>(istream& is, BaseMatrix& matrix);

	/// Overloaded std::swap that will swap the values in two BaseMatrix
	/// objects.
	///
	/// \param left The BaseMatrix that will swap data with right.
	/// \param right The BaseMatrix that will swap data with left.
	///
	/// \post All data in left is now in right and all data in right is now in
	///       left.
	friend void swap<Derived, T>(BaseMatrix& left, BaseMatrix& right);
};	

// Overloaded insertion operator (<<).
template<class Derived, class T>
ostream& operator<<(ostream& os, const BaseMatrix<Derived, T>& matrix){
	// Insert all data in matrix to os with appropriate formatting.
	for(unsigned int i=0; i<matrix.get_size(); i++){
		for(unsigned int j=0; j<matrix.get_size(); j++){
			os << matrix(i, j) << " ";
		}
		os << "\n";
	}
	return os;
}

// Overloaded extraction operator (>>).
template<class Derived, class T>
istream& operator>>(istream& is, BaseMatrix<Derived, T>& matrix){
	// Extract data until matrix is completely filled with data.
	for(unsigned int i=0; i<matrix.get_size(); i++){
		for(unsigned int j=0; j<matrix.get_size(); j++){
			// Error if not enough data to completely fill matrix.
			if(!(is >> matrix(i, j)))
				throw invalid_argument("Failed to read in full BaseMatrix.");
		}
	}
	return is;
}

// Overloaded std::swap for BaseMatrix.
template<class Derived, class T>
void swap(BaseMatrix<Derived, T>& left, BaseMatrix<Derived, T>& right){
	swap(left.grid, right.grid);
	swap(left.size, right.size);
	return;
}

#include "BaseMatrix.hpp"
#endif