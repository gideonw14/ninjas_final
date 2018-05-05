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
	return asDerived().operator*(scalar);
}

template<class Derived, class T>
Vector<T> BaseMatrix<Derived, T>::operator*(const Vector<T>& vector) const{
	return asDerived().operator*(vector);
}

template<class Derived, class T>
BaseMatrix<Derived, T> BaseMatrix<Derived, T>::operator+(const BaseMatrix<Derived, T>& other) const{
	return asDerived().operator+(other);
}

template<class Derived, class T>
BaseMatrix<Derived, T> BaseMatrix<Derived, T>::operator-(const BaseMatrix<Derived, T>& other) const{
	return asDerived().operator-(other);
}

template<class Derived, class T>
BaseMatrix<Derived, T> BaseMatrix<Derived, T>::operator~() const{
	return asDerived().operator~();
}

template<class Derived, class T>
T& BaseMatrix<Derived, T>::operator()(const unsigned int& height, const unsigned int& width){
	return asDerived().operator()(height, width);
}

template<class Derived, class T>
const T& BaseMatrix<Derived, T>::operator()(const unsigned int& height, const unsigned int& width) const{
	return asDerived().operator()(height, width);
}


template<class Derived, class T>
void BaseMatrix<Derived, T>::set_size(const unsigned int& new_size){
	return asDerived().set_size(new_size);
}

template<class Derived, class T>
bool BaseMatrix<Derived, T>::d_dom() const{
	return asDerived().d_dom();
}

template<class Derived, class T>
BaseMatrix<Derived, T>& BaseMatrix<Derived, T>::add_assign(const BaseMatrix<Derived, T>& other){
	if(other.size != size){
		throw invalid_argument("Sizes must match for addition!");
	}
	grid += other.grid;	
	return *this;
}