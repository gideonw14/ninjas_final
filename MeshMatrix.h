#ifndef MeshMatrix_h
#define MeshMatrix_h

#include "BaseMatrix.h"

template<class T>
class MeshMatrix: public BaseMatrix<MeshMatrix, T>{
public:
	MeshMatrix(): size(0) {}
};

#include "MeshMatrix.hpp"
#endif