template<class Derived, class T>
BaseMatrix<Derived, T>::BaseMatrix(const unsigned int& new_size){
	size = new_size;
	grid.setSize(size);
	for(int i=0; i<size; i++){
		grid[i].setSize(size);
	}
}

template<class Derived, class T>
BaseMatrix<Derived, T>::BaseMatrix(const BaseMatrix<Derived, T>& other){
	*this = other;	
}

template<class Derived, class T>
BaseMatrix<Derived, T>& BaseMatrix<Derived, T>::operator=(const BaseMatrix<Derived, T>& other){
	size = other.size;
	grid = other.grid;
	return *this;
}

template<class Derived, class T>
BaseMatrix<Derived, T>& BaseMatrix<Derived, T>::operator*=(const T& scalar){
	return asDerived().scalar_multiply_assign(scalar);
}

template<class Derived, class T>
BaseMatrix<Derived, T>& BaseMatrix<Derived, T>::operator+=(const BaseMatrix<Derived, T>& other){
	return asDerived().add_assign(other);
}

template<class Derived, class T>
BaseMatrix<Derived, T>& BaseMatrix<Derived, T>::operator-=(const BaseMatrix<Derived, T>& other){
	return asDerived().subtract_assign(other);
}

template<class Derived, class T>
BaseMatrix<Derived, T> BaseMatrix<Derived, T>::operator*(const T& scalar) const{
	return asDerived().scalar_multiply(scalar);
}

template<class Derived, class T>
Vector<T> BaseMatrix<Derived, T>::operator*(const Vector<T>& vector) const{
	return asDerived().vector_multiply(vector);
}

template<class Derived, class T>
BaseMatrix<Derived, T> BaseMatrix<Derived, T>::operator+(const BaseMatrix<Derived, T>& other) const{
	return asDerived().add(other);
}

template<class Derived, class T>
BaseMatrix<Derived, T> BaseMatrix<Derived, T>::operator-(const BaseMatrix<Derived, T>& other) const{
	return asDerived().subtract(other);
}

template<class Derived, class T>
BaseMatrix<Derived, T> BaseMatrix<Derived, T>::operator~() const{
	return asDerived().transpose();
}

template<class Derived, class T>
T& BaseMatrix<Derived, T>::operator()(const unsigned int& height, const unsigned int& width){
	return asDerived().get_data(height, width);
}

template<class Derived, class T>
const T& BaseMatrix<Derived, T>::operator()(const unsigned int& height, const unsigned int& width) const{
	return asDerived().get_data(height, width);
}


template<class Derived, class T>
void BaseMatrix<Derived, T>::set_size(const unsigned int& new_size){
	return asDerived().set_size_derived(new_size);
}

template<class Derived, class T>
bool BaseMatrix<Derived, T>::d_dom() const{
	return asDerived().d_dom_derived();
}

template<class Derived, class T>
BaseMatrix<Derived, T>& BaseMatrix<Derived, T>::add_assign(const BaseMatrix<Derived, T>& other){
	if(other.size != size){
		throw invalid_argument("Sizes must match for addition!");
	}
	grid += other.grid;	
	return *this;
}

template<class Derived, class T>
BaseMatrix<Derived, T>& BaseMatrix<Derived, T>::subtract_assign(const BaseMatrix<Derived, T>& other){
	if(other.size != size){
		throw invalid_argument("Sizes must match for subtraction!");
	}
	grid -= other.grid;
	return *this;
}

template<class Derived, class T>
BaseMatrix<Derived, T>& BaseMatrix<Derived, T>::multiply_assign(const BaseMatrix<Derived, T>& other){
	if(size != other.size){
		throw invalid_argument("Width must match height of other Matrix!");
	}
	T product;
	T sum;
	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++){
			for(int k=0; k<other.size; k++){
				product = grid[i][k] * other.grid[k][j];
				k==0 ? sum = product : sum += product;
			}
			grid[i][j] = sum;	
		}
	}
	return *this;
}

template<class Derived, class T>
Vector<T> BaseMatrix<Derived, T>::vector_multiply(const Vector<T>& vector) const{
	if(size != vector.get_size()){
		throw invalid_argument("Vector size must equal Matrix size!");
	}
	Vector<T> result_vector(size);
	T sum;
	T product;
	for(int h=0; h<size; h++){
		for(int w=0; w<size; w++){
			product = grid[h][w] * vector[w];
			w==0 ? sum = product : sum += product;
		}
		result_vector[h] = sum;
	}
	return result_vector;
}

template<class Derived, class T>
BaseMatrix<Derived, T> BaseMatrix<Derived, T>::add(const BaseMatrix<Derived, T>& other) const{
	BaseMatrix<Derived, T> temp(*this);
	return temp += other;
}

template<class Derived, class T>
BaseMatrix<Derived, T> BaseMatrix<Derived, T>::subtract(const BaseMatrix<Derived, T>& other) const{
	BaseMatrix<Derived, T> temp(*this);
	return temp -= other;
}

template<class Derived, class T>
BaseMatrix<Derived, T> BaseMatrix<Derived, T>::multiply(const BaseMatrix<Derived, T>& other) const{
	BaseMatrix<Derived, T> temp(*this);
	return temp *= other;
}

template<class Derived, class T>
BaseMatrix<Derived, T> BaseMatrix<Derived, T>::scalar_multiply(const T& scalar) const{
	BaseMatrix<Derived, T> temp(*this);
	return temp *= scalar;
}

template<class Derived, class T>
BaseMatrix<Derived, T> BaseMatrix<Derived, T>::transpose() const{
	BaseMatrix<Derived, T> transpose(size);
	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++){
			transpose.grid[j][i] = grid[i][j];
		}
	}
	return transpose;
}

template<class Derived, class T>
T& BaseMatrix<Derived, T>::get_data(const unsigned int& height, const unsigned int& width){
	return grid[height][width];
}

template<class Derived, class T>
const T& BaseMatrix<Derived, T>::get_data(const unsigned int& height, const unsigned int& width) const{
	return grid[height][width];
}

template<class Derived, class T>
bool BaseMatrix<Derived, T>::d_dom_derived() const{
	T diagonal;
	T sum;
	for(int i=0; i<size; i++){
		sum = 0;
		for(int j=0; j<size; j++){
			if(i == j){
				diagonal = fabs(grid[i][j]);
			}
			else{
				if(j > i){
					// Return false if not symmetric.
					if(grid[i][j] != grid[j][i]){
						return false;
					}
				}
				sum += fabs(grid[i][j]);
			}
		}
		// Return false if diagonal is not greater than sum of other elements.
		if(sum >= diagonal){
			return false;
		}
	}
	return true;
} 

template<class Derived, class T>
void BaseMatrix<Derived, T>::set_size_derived(const unsigned int& new_size){
	size = new_size;
	grid.setSize(size);
	for(int i=0; i<size; i++){
		grid[i].setSize(size);
	}
	return;
}