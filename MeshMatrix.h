#ifndef MeshMatrix_h
#define MeshMatrix_h

#include "BaseMatrix.h"

template<class T>
class MeshMatrix: public BaseMatrix<MeshMatrix<T>, T>{
public:
	MeshMatrix() {this->size = 0;}
};

#include "MeshMatrix.hpp"
#endif
