//*****************************************************************************
// Programmers: Charles Gaitley and Gideon Walker	Due Date: 05/06/2018
// Class: CS 5201									Section: A
// File: BaseMatrix.hpp
// Description: This file contains function implementations for the BaseMatrix 
//              class.
//*****************************************************************************

// This function will convert a BaseMatrix templated on any type to a 
// BaseMatrix templated on a GeneralMatrix.
template<class Derived, class T>
BaseMatrix<GeneralMatrix<T>, T> BaseMatrix<Derived, T>::convert_to_general(const BaseMatrix<Derived, T>& other) const{
	// Function object.
	BaseMatrix<GeneralMatrix<T>, T> general(size);
	
	// Assign all values in other to the corresponding positions in general.
	for(unsigned int i=0; i<size; i++){
		for(unsigned int j=0; j<size; j++){
			general(i, j) = other(i, j);
		}
	}
	return general;
}

// Move Constructor.
template <class Derived, class T>
BaseMatrix<Derived, T>::BaseMatrix(BaseMatrix<Derived, T>&& other):
	grid(move(other.grid)), size(other.size) 
{
	other.clear();	
}

// Overloaded assignment operator (=) for BaseMatrix assignment.
template<class Derived, class T>
BaseMatrix<Derived, T>& BaseMatrix<Derived, T>::operator=(const BaseMatrix<Derived, T>& other){
	return asDerived().equal(other);
}

// Overloaded multiply-assignment operator (*=) for scalar multiplication.
template<class Derived, class T>
BaseMatrix<Derived, T>& BaseMatrix<Derived, T>::operator*=(const T& scalar){
	return asDerived().scalar_multiply_assign(scalar);
}

// Overloaded add-assignment operator (+=) for BaseMatrix addition.
template<class Derived, class T>
BaseMatrix<Derived, T>& BaseMatrix<Derived, T>::operator+=(const BaseMatrix<Derived, T>& other){
	return asDerived().add_assign(other);
}

// Overloaded subtract-assignment operator (-=).
template<class Derived, class T>
BaseMatrix<Derived, T>& BaseMatrix<Derived, T>::operator-=(const BaseMatrix<Derived, T>& other){
	return asDerived().subtract_assign(other);
}

// Overloaded binary operator (*) for vector multiplication.
template<class Derived, class T>
Vector<T> BaseMatrix<Derived, T>::operator*(const Vector<T>& vector) const{
	return asDerived().vector_multiply(vector);
}

// Overloaded binary operator (*) for scalar multiplication.
template<class Derived, class T>
BaseMatrix<Derived, T> BaseMatrix<Derived, T>::operator*(const T& scalar) const{
	return asDerived().scalar_multiply(scalar);
}

// Overloaded binary operator (*) for BaseMatrix multiplication.
template<class Derived, class T>
BaseMatrix<GeneralMatrix<T>, T> BaseMatrix<Derived, T>::operator*(const BaseMatrix<Derived, T>& other) const{
	return asDerived().multiply(other);
}

// Overloaded binary operator (+) for BaseMatrix addition.
template<class Derived, class T>
BaseMatrix<Derived, T> BaseMatrix<Derived, T>::operator+(const BaseMatrix<Derived, T>& other) const{
	return asDerived().add(other);
}

// Overloaded binary operator (-) for BaseMatrix subtraction.
template<class Derived, class T>
BaseMatrix<Derived, T> BaseMatrix<Derived, T>::operator-(const BaseMatrix<Derived, T>& other) const{
	return asDerived().subtract(other);
}

// Overloaded transpose operator (~) that will find the transpose of a 
// BaseMatrix.
template<class Derived, class T>
BaseMatrix<Derived, T> BaseMatrix<Derived, T>::operator~() const{
	return asDerived().transpose();
}

// Overloaded parentheses operator () that will access data in calling 
// BaseMatrix with read-and-write access.
template<class Derived, class T>
T& BaseMatrix<Derived, T>::operator()(const unsigned int& height, const unsigned int& width){
	return asDerived().get_data(height, width);
}

// Overloaded parentheses operator () that will access data in calling 
// BaseMatrix with read-only access.
template<class Derived, class T>
const T& BaseMatrix<Derived, T>::operator()(const unsigned int& height, const unsigned int& width) const{
	return asDerived().get_data(height, width);
}

// This function will set the size of calling BaseMatrix to a new size.
template<class Derived, class T>
void BaseMatrix<Derived, T>::set_size(const unsigned int& new_size){
	asDerived().set_size_derived(new_size);
	return;
}

// Operator = default implementation function.
template<class Derived, class T>
BaseMatrix<Derived, T>& BaseMatrix<Derived, T>::equal(const BaseMatrix<Derived, T>& other){
	grid = other.grid;
	size = other.size;
	return *this;
}

// Operator *= default implementation.
template<class Derived, class T>
BaseMatrix<Derived, T>& BaseMatrix<Derived, T>::scalar_multiply_assign(const T& scalar){
	grid*=scalar; 
	return *this;
}

// Operator += default implementation
template<class Derived, class T>
BaseMatrix<Derived, T>& BaseMatrix<Derived, T>::add_assign(const BaseMatrix<Derived, T>& other){
	// Check that other's size matches calling BaseMatrix's size.
	if(other.size != size){
		throw invalid_argument("Sizes must match for addition!");
	}
	
	grid += other.grid;	
	return *this;
}

// Operator -= default implementation.
template<class Derived, class T>
BaseMatrix<Derived, T>& BaseMatrix<Derived, T>::subtract_assign(const BaseMatrix<Derived, T>& other){
	// Check that other's size matches calling BaseMatrix's size.
	if(other.size != size){
		throw invalid_argument("Sizes must match for subtraction!");
	}
	
	grid -= other.grid;
	return *this;
}

// Binary operator * for Vector multiplication default implementation.
template<class Derived, class T>
Vector<T> BaseMatrix<Derived, T>::vector_multiply(const Vector<T>& vector) const{
	// Check that the size of vector is equal to calling BaseMatrix
	if(size != vector.get_size()){
		throw invalid_argument("Vector size must equal Matrix size!");
	}
	
	// Function objects and variables.
	Vector<T> result_vector(size);
	T sum;
	T product;
	
	// Set each index in resultant Vector to the dot product between
	// corresponding row in calling BaseMatrix and vector.
	for(unsigned int h=0; h<size; h++){
		for(unsigned int w=0; w<size; w++){
			product = (*this)(h, w) * vector[w];
			w==0 ? sum = product : sum += product;
		}
		result_vector[h] = sum;
	}
	return result_vector;
}

// Binary operator + for BaseMatrix addition default implementation.
template<class Derived, class T>
BaseMatrix<Derived, T> BaseMatrix<Derived, T>::add(const BaseMatrix<Derived, T>& other) const{
	// Function Object.
	BaseMatrix<Derived, T> temp(*this);
	return temp += other;
}

// Binary operator - for BaseMatrix subtraction default implementation.
template<class Derived, class T>
BaseMatrix<Derived, T> BaseMatrix<Derived, T>::subtract(const BaseMatrix<Derived, T>& other) const{
	// Function Object.
	BaseMatrix<Derived, T> temp(*this);
	return temp -= other;
}

// Binary operator * for BaseMatrix multiplication default implementation.
template<class Derived, class T>
BaseMatrix<GeneralMatrix<T>, T> BaseMatrix<Derived, T>::multiply(const BaseMatrix<Derived, T>& other) const{
	// Check that other's size is the same as calling BaseMatrix size.
	if(size != other.size){
		throw invalid_argument("Width must match height of other Matrix!");
	}
	
	BaseMatrix<GeneralMatrix<T>, T> temp = convert_to_general(*this);
	
	// Function variables.
	T product;
	T sum;
	
	// Set corresponding row and column in temp with dot product of row in
	// calling BaseMatrix and column in other.
	for(unsigned int i=0; i<size; i++){
		for(unsigned int j=0; j<size; j++){
			for(unsigned int k=0; k<size; k++){
				product = (*this)(i, k) * other(k, j);
				k==0 ? sum = product : sum += product;
			}
			temp(i, j) = sum;	
		}
	}
	return temp;
}

// Binary operator * for scalar multiplication default implementation.
template<class Derived, class T>
BaseMatrix<Derived, T> BaseMatrix<Derived, T>::scalar_multiply(const T& scalar) const{
	// Function Object.
	BaseMatrix<Derived, T> temp(*this);
	return temp *= scalar;
}

// Transpose operator ~ for calculating the transpose of calling BaseMatrix
// default implementation.
template<class Derived, class T>
BaseMatrix<Derived, T> BaseMatrix<Derived, T>::transpose() const{
	// Function Object.
	BaseMatrix<Derived, T> transpose(size);
	
	// Swap elements at row and column with elements at column and row.
	for(unsigned int i=0; i<size; i++){
		for(unsigned int j=0; j<size; j++){
			transpose(j, i) = (*this)(i, j);
		}
	}
	return transpose;
}

// Parentheses operator () default implementation for read-and-write access.
template<class Derived, class T>
T& BaseMatrix<Derived, T>::get_data(const unsigned int& height, const unsigned int& width){
	// Check for out of bounds request or emptiness of calling BaseMatrix.
	if (is_empty() || height >= size || width >= size){
		throw invalid_argument(MATRIX_OUT);
	}
	return grid[height][width];
}

// Parentheses operator () default implementation for read-only access.
template<class Derived, class T>
const T& BaseMatrix<Derived, T>::get_data(const unsigned int& height, const unsigned int& width) const{
	// Check for out of bounds request or emptiness of calling BaseMatrix.
	if (is_empty() || height >= size || width >= size){
		throw invalid_argument(MATRIX_OUT);
	}
	return grid[height][width];
}

// p_def default implementation.
template<class Derived, class T>
bool BaseMatrix<Derived, T>::p_def_derived() const{
	// Function variables.
	T diagonal;
	T sum;
	
	// Check for a symmetric and diagonally dominant BaseMatrix.
	for(unsigned int i=0; i<size; i++){
		sum = 0;
		for(unsigned int j=0; j<size; j++){
			// Diagonal.
			if(i == j){
				diagonal = fabs((*this)(i, j));
			}
			else{
				// Return false if not symmetric.
				if(j > i){
					if((*this)(i, j) != (*this)(j, i)){
						return false;
					}
				}
				sum += fabs((*this)(i, j));
			}
		}
		// Return false if diagonal is not less than sum of other elements.
		if(sum > diagonal){
			return false;
		}
	}
	return true;
} 

// set_size default implementation.
template<class Derived, class T>
void BaseMatrix<Derived, T>::set_size_derived(const unsigned int& new_size){
	size = new_size;
	grid.setSize(size);
	
	// Set the size of all rows to the new_size.
	for(unsigned int i=0; i<size; i++){
		grid[i].setSize(size);
	}
	return;
}