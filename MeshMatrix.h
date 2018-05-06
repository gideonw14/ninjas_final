//*****************************************************************************
// Programmers: Charles Gaitley and Gideon Walker	Due Date: 05/06/2018
// Class: CS 5201									Section: A
// File: MeshMatrix.h
// Description: This file contains a matrix that represents a special type of
//              banded matrix when solving a PDE in the unit square.
//*****************************************************************************

#ifndef MESHMATRIX_H
#define MESHMATRIX_H

#include "BaseMatrix.h"

/// This class represents a special matrix that is produced when solving a PDE
/// in the unit square with known boundaries.
///
/// \pre Same pre-conditions as BaseMatrix, but this matrix also cannot be
///      modified except for its diagonal and special band values.
/// \pre All diagonal and special band values are uniform for every spot in the
///      diagonal or special band.
/// \pre Data outside of diagonals or special bands cannot be modified.
/// \pre integers must be able to be statically cast to type T 
///      (static_cast<T>(int))
template<class T>
class MeshMatrix: public BaseMatrix<MeshMatrix<T>, T>{
private:
	
	/// Represents the storage spaces in grid[0] where a zero, partition 
	/// (special band) value, and diagonal data is stored.
	enum{ZERO, PARTITION, DIAGONAL};
	
	/// A zero value to return in the read-only version of get_data.
	static const T zero;
	
	/// The number of partitions used in generating a MeshMatrix.
	unsigned int partitions;
	
public:

	/// Default Constructor.
	///
	/// \pre This constructor calls BaseMatrix default constructor. Be aware of
	///      this constructor's requirements before invoking MeshMatrix default
	///      constructor.
	///
	/// \post A new MeshMatrix is created in its default, empty state.
	MeshMatrix(): BaseMatrix<MeshMatrix<T>, T>(), partitions(MIN_SIZE) {}
	
	/// Parametrized Constructor.
	///
	/// \param new_partitions The desired number of partitions in approximation
	///        mesh for the PDE.
	///
	/// \pre This constructor calls BaseMatrix parametrized constructor. Be 
	///      aware of this constructor's requirements before invoking 
	///      MeshMatrix parametrized constructor.
	///
	/// \post A new MeshMatrix is generated based on partitions.
	MeshMatrix(const unsigned int& new_partitions): BaseMatrix<MeshMatrix<T>, T>(new_partitions) {}
	
	/// Copy Constructor.
	///
	/// \param other The MeshMatrix that newly created MeshMatrix will be a
	///        copy of.
	///
	/// \pre This constructor calls BaseMatrix copy constructor. Be aware of
	///      this constructor's requirements before invoking MeshMatrix copy
	///      constructor.
	///
	/// \post A new MeshMatrix is created that is a copy of other.
	MeshMatrix(const MeshMatrix<T>& other): BaseMatrix<MeshMatrix<T>, T>(other) {}
	
	/// Move Constructor.
	///
	/// \param other The MeshMatrix whose data will be moved into newly created
	///        MeshMatrix.
	///
	/// \pre This constructor calls BaseMatrix move constructor. Be aware of
	///      this constructor's requirements before invoking MeshMatrix move
	///      constructor.
	///
	/// \post A new MeshMatrix is created with other's data moved into it.
	MeshMatrix(MeshMatrix<T>&& other): partitions(other.partitions), BaseMatrix<MeshMatrix<T>, T>(other) {}
	
	/// Assignment operator = implementation for a MeshMatrix.
	///
	/// \param other The MeshMatrix that calling MeshMatrix will be set equal 
	///        to.
	///
	/// \pre This function calls BaseMatrix equal function. Be aware of this
	///      function's requirements before calling MeshMatrix equal function.
	///
	/// \return A reference to calling MeshMatrix that is now equal to other.
	MeshMatrix<T>& operator=(const MeshMatrix<T>& other);
	
	/// Parentheses operator () implementation for read-and-write access of a 
	/// MeshMatrix.
	///
	/// \param height The desired row where data is stored in the MeshMatrix.
	/// \param width The desired column where data is stored in the MeshMatrix.
	///
	/// \pre Calling MeshMatrix must not be empty.
	/// \pre height or width must not exceed size - 1.
	/// \pre Be warned that modifing diagonal or special band data will
	///      change all values on that diagonal and special band.
	///
	/// \throws std::out_of_range if calling MeshMatrix is empty or height or
	///         width exceeds size - 1.
	///
	/// \return A constant reference to data at height and width so it cannot
	///         be modified.
	T& get_data(const unsigned int& height, const unsigned int& width);
	
	/// Parentheses operator () implementation for read-only access of a 
	/// MeshMatrix.
	///
	/// \param height The desired row where data is stored in the MeshMatrix.
	/// \param width The desired column where data is stored in the MeshMatrix.
	///
	/// \pre Calling MeshMatrix must not be empty.
	/// \pre height or width must not exceed size - 1.
	///
	/// \throws std::out_of_range if calling MeshMatrix is empty or height or
	///         width exceeds size - 1.
	///
	/// \return A constant reference to data at height and width so it cannot
	///         be modified.
	const T& get_data(const unsigned int& height, const unsigned int& width) const;
	
	/// Binary operator (*) implementation for MeshMatrix and vector 
	/// multiplication.
	///
	/// \param vector The Vector calling MeshMatrix is being multiplied by.
	///
	/// \pre vector must have the same number of elements as the size of
	///      calling MeshMatrix.
	///
	/// \throws std::invalid_argument if calling MeshMatrix and vector are not
	///         the same size.
	///
	/// \return A Vector that is the result of calling MeshMatrix times vector.
	Vector<T> vector_multiply(const Vector<T>& vector) const;
	
	/// set_size implementation for a MeshMatrix.
	///
	/// \param new_partitions The desired new partition to generate a 
	///        MeshMatrix from.
	///
	/// \pre This function will generate a brand new MeshMatrix. All data from
	///      previous MeshMatrix will be lost.
	///
	/// \post A new MeshMatrix has been generated based on the new number of
	///       partitions in approximation mesh.
	void set_size_derived(const unsigned int& new_partitions);
	
	/// Transpose operator ~ implementation for MeshMatrix.
	/// 
	/// \return A copy of calling Matrix since all MeshMatrix transpose is
	///         themselves.
	MeshMatrix<T> transpose() const {return *this;}
	
	/// p_def implementation to determine if a MeshMatrix is positive definite
	/// or not.
	///
	/// \return True if calling MeshMatrix is symmetric and diagonally dominant
	///         and false otherwise.
	bool p_def_derived() const;
	
	/// clear implementation for a MeshMatrix.
	///
	/// \post The MeshMatrix is now back to its default empty state.
	void erase();
};

#include "MeshMatrix.hpp"
#endif
