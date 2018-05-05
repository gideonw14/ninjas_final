/*******************************************************************************
	Filename: 	BaseMatrix.h
	Programmer: Gideon Walker
	Class: 		CS 5201 - Prof. Price
	Assignment: 5
	Due: 		April 4, 2018

	Description:
		The BaseMatrix class, made to suit all your BaseMatrix needs. 
		Has every operator overload you could ever want and more. 
*******************************************************************************/
#ifndef Matrix_h
#define Matrix_h

#include "mathvector.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

// Keep your friends from backstabbing you.
template<class Derived, class T> class BaseMatrix;
template<class Derived, class T> ostream& operator<<(ostream& os, const BaseMatrix<Derived, T>& BaseMatrix);
template<class Derived, class T> ifstream& operator>>(ifstream& ifs, BaseMatrix<Derived, T>& BaseMatrix);
template<class Derived, class T> istream& operator>>(istream& is, BaseMatrix<Derived, T>& BaseMatrix);
template<class Derived, class T> void swap(BaseMatrix<Derived, T>& left, BaseMatrix<Derived, T>& right);

/** The BaseMatrix class. Used to perform mathematical BaseMatrix operations.
 *  \pre =, +=, *=, -=, *, ==, >=, >>, << operators are implemented for T.
 */
template<class Derived, class T>
class BaseMatrix{
protected:
	Vector<Vector<T>> grid;
	unsigned int size;
public:
	/** BaseMatrix default constructor.
	 *  \pre None.
	 *  \post Height and width are zero. Grid is unset.
	 */
	BaseMatrix(): size(0) {}

	/** BaseMatrix parameterized constructor. Makes a square BaseMatrix.
	 *  \param 	new_size the size to initialize BaseMatrix with.
	 *  \pre 	None.
	 *  \post 	BaseMatrix(int, int) is called with new_size for both arguments.
	 */
	BaseMatrix(const unsigned int& new_size);

	/**	BaseMatrix copy constructor.
	 *  \param 	other the BaseMatrix to copy.
	 *	\pre	None.
	 *	\post	Becomes an exact copy of other.
	 */
	BaseMatrix(const BaseMatrix<Derived, T>& other);

	/**	BaseMatrix move constructor.
	 *  \param 	other the BaseMatrix to swap with.
	 *	\pre	None.
	 *	\post	Calling object gets swapped with other. 
	 */
	BaseMatrix(BaseMatrix<Derived, T>&& other): BaseMatrix() { swap(*this, other); }

	/**	BaseMatrix destructor. Does nothing. 
	 *	\pre	None.
	 *	\post	None.
	 */
	~BaseMatrix() {}

	/**	Assignment operator.
	 *	\pre	None.
	 *	\post	Becomes an exact copy of other with the help of swap.
	 *  \return calling object reference.
	 */
	BaseMatrix<Derived, T>& operator=(const BaseMatrix<Derived, T>& other);

	/**	Scalar multiplication assignment operator.
	 *  \param 	scalar the value to multiply by.
	 *	\pre	Operator *= is implemented for T.
	 *	\post	All values in the BaseMatrix are multiplied by the scalar.
	 *  \return calling object reference.
	 */
	BaseMatrix<Derived, T>& operator*=(const T& scalar);

	/**	BaseMatrix addition assignment operator.
	 *  \param  other the BaseMatrix to add to calling object. 
	 *	\pre	Operator += is implemented for T.
	 *	\post   Every value in other is added to corresponding value in the 
	 *  calling object.
	 *  \return calling object reference.
	 *  \throws std::invalid_argument if height and width do not match.
	 */
	BaseMatrix<Derived, T>& operator+=(const BaseMatrix<Derived, T>& other);

	/**	BaseMatrix subtraction assignment operator.
	 *  \param 	other the BaseMatrix to subtract from calling object. 
	 *	\pre	Operator -= is implemented for T.
	 *	\post   Every value in other is subtracted to corresponding value in the 
	 *  calling object.
	 *  \return calling object reference.
	 *  \throws std::invalid_argument if height and width do not match.
	 */
	BaseMatrix<Derived, T>& operator-=(const BaseMatrix<Derived, T>& other);

	/**	BaseMatrix vector multiplication operator.
	 *  \param 	vector the vector to multiply by.
	 *	\pre	*, += operators implemented for T.
	 *	\post	None.
	 *  \return the result of multiplying calling object by vector.
	 *  \throws std::invalid_argument if vector size is not equal to the BaseMatrix
	 *  width.
	 */
	Vector<T> operator*(const Vector<T>& vector) const;

	/**	BaseMatrix scalar multiplication operator.
	 *  \param  scalar the scalar to multiply by.
	 *	\pre	None.
	 *	\post	None.
	 *  \return a copy of calling object *= scalar.
	 */
	BaseMatrix<Derived, T> operator*(const T& scalar) const;

	/**	BaseMatrix addition operator.
	 *  \param  other the BaseMatrix to add to calling object. 
	 *	\pre	None.
	 *	\post	None.
	 *  \return a copy of calling object += other.
	 */
	BaseMatrix<Derived, T> operator+(const BaseMatrix<Derived, T>& other) const;

	/**	BaseMatrix subtraction operator.
	 *  \param  other the BaseMatrix to subtract from calling object.
	 *	\pre	None.
	 *	\post	None.
	 *  \return a copy of calling object -= other.
	 */
	BaseMatrix<Derived, T> operator-(const BaseMatrix<Derived, T>& other) const;

	/**	BaseMatrix transpose operator.
	 *	\pre	Operator = is implemented for T.
	 *	\post	None.
	 *  \return a transposed BaseMatrix of the calling object.
	 */
	BaseMatrix<Derived, T> operator~() const;

	/**	Accessor operator.
	 *  \param 	height the height (vertical) element to retrieve (starts at 0).
	 *  \param 	width the width (horizontal) element to retrieve (starts at 0).
	 *	\pre	None.
	 *	\post	None.
	 *  \return T reference at the given height, width. 
	 *  \throws std::out_of_range if height, width is negative 
	 *			or height, width is >= size.
	 */
	T& operator()(const unsigned int& height, const unsigned int& width);

	/**	Const accessor operator.
	 *  \param 	height the height (vertical) element to retrieve (starts at 0).
	 *  \param 	width the width (horizontal) element to retrieve (starts at 0).
	 *	\pre	None.
	 *	\post	None.
	 *  \return const T reference at the given height, width. 
	 *  \throws std::out_of_range if height, width is negative 
	 *			or height, width is >= size.
	 */
	const T& operator()(const unsigned int& height, const unsigned int& width) const;

	/**	Mutator function.
	 *  \param 	new_size the size to set to height and width.
	 *	\pre	See set_height_width.
	 *	\post	Calling object becomes a square BaseMatrix of new_size.
	 */
	void set_size(const unsigned int& new_size);

	/**	Getter function.
	 *	\pre	None.
	 *	\post	None.
	 *  \return size.
	 */
	unsigned int get_size() const { return size; }
	
	/**	Diagonally domminated. That just means the BaseMatrix is symmetric and the
	 * 	absolute value at the diagonal is greater than the sum of the absolute
	 *  values of the other elements in the row for each row. 
	 *	\pre	==, >= operators are implemented for T.
	 *	\post	None.
	 *  \return true if the BaseMatrix is diagonlly dominated. false if the BaseMatrix
	 *			is not symmetric or otherwise not diagonally dominated.
	 */
	bool d_dom() const;

	Derived& asDerived(){ return static_cast<Derived&>(*this); }
	const Derived& asDerived() const { return static_cast<const Derived&>(*this); }

	BaseMatrix<Derived, T>& scalar_multiply_assign(const T& scalar){grid*=scalar; return *this;}

	BaseMatrix<Derived, T>& add_assign(const BaseMatrix<Derived, T>& other);
	BaseMatrix<Derived, T>& subtract_assign(const BaseMatrix<Derived, T>& other);

	/**	Standard output stream operator.
	 *  \param  os the output stream.
	 *  \param  BaseMatrix the BaseMatrix to print out.
	 *	\pre	<< operator is defined for T.
	 *	\post	The BaseMatrix is nicely output to os.
	 *  \return os. 
	 */
	friend ostream& operator<<<Derived, T>(ostream& os, const BaseMatrix& BaseMatrix);

	/**	File input stream operator.
	 *  \param 	ifs the input file stream.
	 * 	\param  BaseMatrix the BaseMatrix to read in to.
	 *	\pre	>> operator is defined for T.
	 *	\post	The BaseMatrix is filled with the file data.
	 *  \throws std::invalid_argument if there is an error while reading in.
	 *  \return ifs.
	 */
	friend ifstream& operator>><Derived, T>(ifstream& ifs, BaseMatrix& BaseMatrix);

	/**	Standard input stream operator.
	 *  \param 	is the input stream.
	 *  \param 	BaseMatrix the BaseMatrix to read in to.
	 *	\pre	>> operator is defined for T.
	 *	\post	The BaseMatrix is filled with user input.
	 *  \return is. 
	 */
	friend istream& operator>><Derived, T>(istream& is, BaseMatrix& BaseMatrix);

	/**	Swap function.
	 *  \param 	left the left BaseMatrix.
	 * 	\param 	right the right BaseMatrix.
	 *	\pre	None.
	 *	\post	Swaps left and right.
	 */
	friend void swap<Derived, T>(BaseMatrix& left, BaseMatrix& right);
};	

template<class Derived, class T>
ostream& operator<<(ostream& os, const BaseMatrix<Derived, T>& matrix){
	for(unsigned int i=0; i<matrix.get_size(); i++){
		for(unsigned int j=0; j<matrix.get_size(); j++){
			os << matrix(i, j) << " ";
		}
		os << "\n";
	}
	return os;
}

template<class Derived, class T>
ifstream& operator>>(ifstream& ifs, BaseMatrix<Derived, T>& matrix){
	for(unsigned int i=0; i<matrix.get_size(); i++){
		for(unsigned int j=0; j<matrix.get_size(); j++){
			if(!(ifs >> matrix(i, j)))
				throw std::invalid_argument("Failed to read in full BaseMatrix.");
		}
	}
	return ifs;
}

template<class Derived, class T>
void swap(BaseMatrix<Derived, T>& left, BaseMatrix<Derived, T>& right){
	using std::swap;
	swap(left.grid, right.grid);
	swap(left.size, right.size);
	return;
}

#include "BaseMatrix.hpp"
#endif