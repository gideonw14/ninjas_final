#ifndef GeneralMatrix_h
#define GeneralMatrix_h

#include "BaseMatrix.h"

template<class Derived, class T> class BaseMatrix;
template<class T> class GeneralMatrix;
template<class T> void swap(GeneralMatrix<T>& left, GeneralMatrix<T>& right);

template<class T>
class GeneralMatrix: public BaseMatrix<GeneralMatrix<T>, T>{
public:
	GeneralMatrix() {this->size(0);}
	GeneralMatrix(const unsigned int& new_size){
		this->size = new_size;
		this->grid.setSize(new_size);
		for(unsigned int i=0; i<this->size; i++){
			this->grid[i].setSize(new_size);
		}
	}
	GeneralMatrix(const GeneralMatrix<T>& other){
		*this = other;
	}
	GeneralMatrix(GeneralMatrix<T>&& other){
		swap(*this, other);
	}
	GeneralMatrix<T>& operator=(const GeneralMatrix<T>& other){
		this->grid = other.grid;
		this->size = other.size;
		return *this;
	}
	friend void swap<T>(GeneralMatrix& left, GeneralMatrix& right);
};

template<class T>
void swap(GeneralMatrix<T>& left, GeneralMatrix<T>& right){
	using std::swap;
	swap(left.grid, right.grid);
	swap(left.size, right.size);
}

#endif