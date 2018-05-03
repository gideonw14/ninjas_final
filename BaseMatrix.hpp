// template<class Derived, class T>
// BaseMatrix<Derived, T>::BaseMatrix(const int new_size){
// 	(*this) = BaseMatrix<Derived, T>(new_size, new_size);
// }

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
	return *this = *this * scalar;
}

template<class Derived, class T>
BaseMatrix<Derived, T>& BaseMatrix<Derived, T>::operator+=(const BaseMatrix<Derived, T>& other){
	return *this = *this + other;
}

template<class Derived, class T>
BaseMatrix<Derived, T>& BaseMatrix<Derived, T>::operator-=(const BaseMatrix<Derived, T>& other){
	return *this = *this - other;
}

template<class Derived, class T>
BaseMatrix<Derived, T> BaseMatrix<Derived, T>::operator*(const T& scalar) const{
	return asDerived.scalar_multiply(scalar);
}

template<class Derived, class T>
Vector<T> BaseMatrix<Derived, T>::operator*(const Vector<T>& vector) const{
	return asDerived.vector_mulitply(vector);
}

template<class Derived, class T>
BaseMatrix<Derived, T> BaseMatrix<Derived, T>::operator+(const BaseMatrix<Derived, T>& other) const{
	return asDerived.add(other);
}

template<class Derived, class T>
BaseMatrix<Derived, T> BaseMatrix<Derived, T>::operator-(const BaseMatrix<Derived, T>& other) const{
	return asDerived.subtract(other);
}

template<class Derived, class T>
BaseMatrix<Derived, T> BaseMatrix<Derived, T>::operator~() const{
	return asDerived.transpose();
}

template<class Derived, class T>
T& BaseMatrix<Derived, T>::operator()(const unsigned int& height, const unsigned int& width){
	return asDerived.operator()(height, width);
}

template<class Derived, class T>
const T& BaseMatrix<Derived, T>::operator()(const unsigned int& height, const unsigned int& width) const{
	return asDerived.operator()(height, width);
}


template<class Derived, class T>
void BaseMatrix<Derived, T>::set_size(const unsigned int& new_size){
	return asDerived.set_size(new_size);
}

template<class Derived, class T>
bool BaseMatrix<Derived, T>::d_dom() const{
	return asDerived.d_dom();
}