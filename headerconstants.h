//*****************************************************************************
// Programmer: Charles Gaitley         Date: 03/10/2018
// Class: CS 5201                      Section: A
// File: headerconstants.h
// Description: This file contains all standard libraries, namespaces, and 
//              global constants used in this program.
//*****************************************************************************

#ifndef HEADERCONSTANTS_H
#define HEADERCONSTANTS_H

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>
#include <memory>

using namespace std;

// Global Constants
const string INCOMPATIBLE_LENGTH = "Error: Two Vectors are incompatible "
                                   "due to not being the same size!";
const string INCOMPATIBLE_DIMENSIONS = "Error: Two Matrices are incompatible "
                                       "due to not having the same number of "
                                       "rows and columns.";
const string BAD_SYSTEM = "Error: System provided does not make sense. Matrix "
                          "A does not have the same number of rows as Vector "
                          "b has elements.";
const string BAD_MULTIPLY = "Error: Two Matrices are incompatible due to "
                            "Matrix on left-hand side of multiplcation not "
                            "having the same number of columns as Matrix on "
                            "right-hand side of multiplication has rows.";
const string OUT_OF_RANGE = "Error: The index provided is greater than the "
                            "largest address where data is stored in this "
                            "Vector or the Vector is empty.";
const string INVALID_SIZE = "Error: Setting the number of rows or columns to "
                            "zero equvalient to calling clear. Use that "
                            "function instead.";
const string INCONSISTENT_SYSTEM = "Error: System passed into Gaussian "
                                   "has no solution!";
const string INVALID_DATA = "Error: There was not enough data to fill Array, "
                            "Vector, or Matrix.";
const string MATRIX_OUT = "Error: Requested row or column does not exist in "
                          "Matrix or Matrix is empty!";

// SteepestDescent and GuassSiedel error messages.
const string WRONG_FORM = "Error: Attempting to solve a system by steepest "
                          "descent when Matrix A is not positive definite!";

const unsigned int MIN_SIZE = 0, VECTOR_COLS = 1;

#endif