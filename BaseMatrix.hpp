template<class Derived, class T>
BaseMatrix<GeneralMatrix<T>, T> BaseMatrix<Derived, T>::convert_to_general(const BaseMatrix<Derived, T>& other) const{
	BaseMatrix<GeneralMatrix<T>, T> general(size);
	for(unsigned int i=0; i<size; i++){
		for(unsigned int j=0; j<size; j++){
			general(i, j) = other(i, j);
		}
	}
	return general;
}

template<class Derived, class T>
BaseMatrix<Derived, T>::BaseMatrix(const unsigned int& new_size){
	size = new_size;
	grid.setSize(size);
	for(unsigned int i=0; i<size; i++){
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
BaseMatrix<GeneralMatrix<T>, T> BaseMatrix<Derived, T>::operator*(const BaseMatrix<Derived, T>& other) const{
	return asDerived().multiply(other);
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
Vector<T> BaseMatrix<Derived, T>::vector_multiply(const Vector<T>& vector) const{
	if(size != vector.get_size()){
		throw invalid_argument("Vector size must equal Matrix size!");
	}
	Vector<T> result_vector(size);
	T sum;
	T product;
	for(unsigned int h=0; h<size; h++){
		for(unsigned int w=0; w<size; w++){
			product = (*this)(h, w) * vector[w];
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
BaseMatrix<GeneralMatrix<T>, T> BaseMatrix<Derived, T>::multiply(const BaseMatrix<Derived, T>& other) const{
	if(size != other.size){
		throw invalid_argument("Width must match height of other Matrix!");
	}
	BaseMatrix<GeneralMatrix<T>, T> temp = convert_to_general(*this);
	T product;
	T sum;
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

template<class Derived, class T>
BaseMatrix<Derived, T> BaseMatrix<Derived, T>::scalar_multiply(const T& scalar) const{
	BaseMatrix<Derived, T> temp(*this);
	return temp *= scalar;
}

template<class Derived, class T>
BaseMatrix<Derived, T> BaseMatrix<Derived, T>::transpose() const{
	BaseMatrix<Derived, T> transpose(size);
	for(unsigned int i=0; i<size; i++){
		for(unsigned int j=0; j<size; j++){
			transpose(j, i) = (*this)(i, j);
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
	for(unsigned int i=0; i<size; i++){
		sum = 0;
		for(unsigned int j=0; j<size; j++){
			if(i == j){
				diagonal = fabs((*this)(i, j));
			}
			else{
				if(j > i){
					// Return false if not symmetric.
					if((*this)(i, j) != (*this)(j, i)){
						return false;
					}
				}
				sum += fabs((*this)(i, j));
			}
		}
		// Return false if diagonal is not greater than sum of other elements.
		if(sum > diagonal){
			return false;
		}
	}
	return true;
} 

template<class Derived, class T>
void BaseMatrix<Derived, T>::set_size_derived(const unsigned int& new_size){
	size = new_size;
	grid.setSize(size);
	for(unsigned int i=0; i<size; i++){
		grid[i].setSize(size);
	}
	return;
}