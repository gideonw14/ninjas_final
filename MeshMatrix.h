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
	const T& get_data(const unsigned int& height, const unsigned int& width) const;
	T& get_data(const unsigned int& height, const unsigned int& width);
	Vector<T> vector_multiply(const Vector<T>& vector) const;
	void set_size_derived(const unsigned int& new_size);
};

#include "MeshMatrix.hpp"
#endif
