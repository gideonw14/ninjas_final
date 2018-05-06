#ifndef GenerateBVector_h
#define GenerateBVector_h

#include "BaseMatrix.h"

template <class T, double left_bound(double), double right_bound(double), double upper_bound(double), double lower_bound(double)>
class GenerateBVector
{
public:
	Vector<T> operator()(const unsigned int &partitions)
	{
		Vector<T> b_vector(static_cast<unsigned int>(pow(partitions - 1, 2)));

		unsigned int count = 0;

		for (unsigned int k = 0; k < partitions - 1; k++)
		{
			for (unsigned int j = 0; j < partitions - 1; j++)
			{
				b_vector[count] = 0;
				if (k == 0)
					b_vector[count] += lower_bound(static_cast<double>(j + 1)/partitions);
				if (j == 0)
					b_vector[count] += left_bound(static_cast<double>(k + 1)/partitions);
				if (k == partitions - 2)
					b_vector[count] += upper_bound(static_cast<double>(j + 1)/partitions);
				if (j == partitions - 2)
					b_vector[count] += right_bound(static_cast<double>(k + 1)/partitions);
				b_vector[count] *= 1.0/4;
				count++;
			}
		}

		return b_vector;
	}
};

#endif