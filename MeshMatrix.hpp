//*****************************************************************************
// Programmers: Charles Gaitley and Gideon Walker	Due Date: 05/06/2018
// Class: CS 5201									Section: A
// File: MeshMatrix.hpp
// Description: This file contains function implementations for the MeshMatrix
//              class.
//*****************************************************************************

// Set constant class member.
template<class T>
const T MeshMatrix<T>::zero = 0;

// Assignment operator (=) implementation.
template<class T>
MeshMatrix<T>& MeshMatrix<T>::operator=(const MeshMatrix<T>& other){
	BaseMatrix<MeshMatrix<T>, T>::operator=(other);
	partitions = other.partitions;
	return *this;
}

// Parentheses operator () implementation for read-and-write access.
template<class T>
T& MeshMatrix<T>::get_data(const unsigned int& height, const unsigned int& width){
	// Check for emptiness of out of bounds.
	if(this -> is_empty() || height >= this->size || width >= this->size){
		throw out_of_range("Height and/or width must be less than size!");
	}
	
	this->grid[0][ZERO] = zero;
	
	// Diagonal Data.
	if(height == width){
		return this->grid[0][DIAGONAL];
	}
	// Upper Special Band 1.
	else if(height + 1 == width){
		return width % (partitions - 1) == 0 ? this->grid[0][ZERO] : this->grid[0][PARTITION];
	}
	// Lower Special Band 1.
	else if(width + 1 == height){
		return height % (partitions - 1) == 0 ? this->grid[0][ZERO] : this->grid[0][PARTITION];
	}
	// Other Special Bands.
	else if(height + partitions - 1 == width || width + partitions - 1 == height){
		return this->grid[0][PARTITION];
	}
	return this->grid[0][ZERO];
}

// Parentheses operator () implementation for read-only access.
template<class T>
const T& MeshMatrix<T>::get_data(const unsigned int& height, const unsigned int& width) const{
	// Check for emptiness of out of bounds.
	if(this -> is_empty() || height >= this->size || width >= this->size){
		throw out_of_range("Height and/or width must be less than size!");
	}
	
	// Diagonal Data.
	if(height == width){
		return this->grid[0][DIAGONAL];
	}
	// Upper Special Band 1.
	else if(height + 1 == width){
		return width % (partitions - 1) == 0 ? zero : this->grid[0][PARTITION];
	}
	// Lower Special Band 1.
	else if(width + 1 == height){
		return height % (partitions - 1) == 0 ? zero : this->grid[0][PARTITION];
	}
	// Other Special Bands.
	else if(height + partitions - 1 == width || width + partitions - 1 == height){
		return this->grid[0][PARTITION];
	}
	return zero;
}

// Binary operator * implementation for Vector multiplication.
template<class T>
Vector<T> MeshMatrix<T>::vector_multiply(const Vector<T>& vector) const{
	// Check that vector's size is same as MeshMatrix size.
	if(this->size != vector.getSize()){
		throw invalid_argument("Vector size must equal BandedMatrix width!");
	}
	Vector<T> result_vector(vector);
	// Diagonal
	result_vector *= this->grid[0][DIAGONAL];
	//First Upper band
	for (unsigned int i=0; i<this->size-1; i++)
	{
		result_vector[i] += vector[i+1] * (*this)(i, i+1);
	}
	//First Lower Band
	for (unsigned int i=1; i<this->size; i++)
	{
		result_vector[i] += vector[i-1] * (*this)(i, i-1);
	}
	//Second Upper Band
	for (unsigned int i=0; i<this->size-partitions+1; i++)
	{
		result_vector[i] += vector[i+partitions-1] * (*this)(i, i+partitions-1);
	}
	//Second Lower Band
	for (unsigned int i=partitions-1; i<this->size; i++)
	{
		result_vector[i] += vector[i-partitions+1] * (*this)(i, i-partitions+1);
	}
	return result_vector;
}

// set_size implementation for a MeshMatrix.
template<class T>
void MeshMatrix<T>::set_size_derived(const unsigned int& new_partitions){
	partitions = new_partitions;
	this->size = static_cast<unsigned int>(pow(new_partitions - 1, 2));
	this->grid.setSize(1);
	this->grid[0].setSize(3);
	this->grid[0][DIAGONAL] = 1;
	this->grid[0][PARTITION] = static_cast<T>(-1)/4;
	this->grid[0][ZERO] = 0;
}

// p_def implementation for a MeshMatrix.
template<class T>
bool MeshMatrix<T>::p_def_derived() const{
	return (4 * fabs(this->grid[0][PARTITION]) <= this->grid[0][DIAGONAL]);
}

// clear implementation for a MeshMatrix.
template <class T>
void MeshMatrix<T>::erase(){
	partitions = MIN_SIZE; 
	this->size = MIN_SIZE; 
	this->grid.clear(); 
	return;
}