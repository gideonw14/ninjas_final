#ifndef MeshMatrix_h
#define MeshMatrix_h

#include "BaseMatrix.h"

template<class T>
class MeshMatrix: public BaseMatrix<MeshMatrix<T>, T>{
private:
	enum{ZERO, PARTITION, DIAGONAL};
	static const T zero;
	unsigned int partitions;
public:
	MeshMatrix() {this->size = 0;}
	MeshMatrix(const unsigned int& new_size, const unsigned int& partitions);
	const T& operator()(const unsigned int& height, const unsigned int& width) const;
	T operator()(const unsigned int& height, const unsigned int& width);
	Vector<T> operator*(const Vector<T>& vector);
	void set_size(const unsigned int& new_size);

};

#include "MeshMatrix.hpp"
#endif