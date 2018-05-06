template<class T>
const T MeshMatrix<T>::zero = 0;

template<class T>
MeshMatrix<T>::MeshMatrix(const unsigned int& new_size, const unsigned int& new_partitions){
	partitions = new_partitions;
	this->size = new_size;
	this->grid.setSize(1);
	this->grid[0].setSize(3);
	this->grid[0][DIAGONAL] = 1;
	this->grid[0][PARTITION] = static_cast<T>(-1)/4;
	this->grid[0][ZERO] = 0;
}

template<class T>
T& MeshMatrix<T>::get_data(const unsigned int& height, const unsigned int& width){
	if(height >= this->size || width >= this->size){
		throw out_of_range("Height and/or width must be less than size!");
	}
	this->grid[0][ZERO] = zero;
	if(height == width){
		return this->grid[0][DIAGONAL];
	}
	else if(height + 1 == width){
		return width % (partitions - 1) == 0 ? this->grid[0][ZERO] : this->grid[0][PARTITION];
	}
	else if(width + 1 == height){
		return height % (partitions - 1) == 0 ? this->grid[0][ZERO] : this->grid[0][PARTITION];
	}
	else if(height + partitions - 1 == width || width + partitions - 1 == height){
		return this->grid[0][PARTITION];
	}
	return this->grid[0][ZERO];
}

template<class T>
const T& MeshMatrix<T>::get_data(const unsigned int& height, const unsigned int& width) const{
	if(height >= this->size || width >= this->size){
		throw out_of_range("Height and/or width must be less than size!");
	}
	if(height == width){
		return this->grid[0][DIAGONAL];
	}
	else if(height + 1 == width){
		return width % (partitions - 1) == 0 ? zero : this->grid[0][PARTITION];
	}
	else if(width + 1 == height){
		return height % (partitions - 1) == 0 ? zero : this->grid[0][PARTITION];
	}
	else if(height + partitions - 1 == width || width + partitions - 1 == height){
		return this->grid[0][PARTITION];
	}
	return zero;
}

template<class T>
Vector<T> MeshMatrix<T>::vector_multiply(const Vector<T>& vector) const{
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

template<class T>
void MeshMatrix<T>::set_size_derived(const unsigned int& new_size){
	this->size = new_size;
	this->grid[0][DIAGONAL] = 1;
	this->grid[0][PARTITION] = static_cast<T>(-1)/4;
	this->grid[0][ZERO] = 0;
}

template<class T>
bool MeshMatrix<T>::d_dom_derived() const{
	return (4 * fabs(this->grid[0][PARTITION]) <= this->grid[0][DIAGONAL]);
}