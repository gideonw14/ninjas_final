/*******************************************************************************
	Filename: 	driver.cpp
	Programmer: Gideon Walker
	Class: 		CS 5201 - Prof. Price
	Assignment: Final project
	Due: 		Wednesday, April 18, 2018

	Description:
		Driver file for final project.
*******************************************************************************/

#include "BaseMatrix.h"
#include "MeshMatrix.h"
#include "GeneralMatrix.h"
#include "GuassSiedel.h"
#include "steepestdescent.h"
#include "GenerateBVector.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <math.h>
#include <ctime>
#include <chrono>
#include <ratio>
using namespace std;
using namespace std::chrono;
const int PRECISION = 3;

double lower_bound (double x) {return 1 - 4 * pow((x - 1.0/2), 2);}
double upper_bound (double x) {x = 0; return x;}
double right_bound (double y) {y = 0; return y;}
double left_bound  (double y) {y = 0; return y;}

template<class U, class T>
void file_input(char* argv[], U& matrix, Vector<T>& vector){
	string filename = argv[1];
	ifstream input_file;

	input_file.open(filename);
	if(! input_file.is_open()){
		cout << "The file " << filename 
			 <<" could not be opened. Try again." << endl;
		exit(1);
	}

	string string_size = "";
	int size = 0;
	string::size_type str_size;

	getline(input_file, string_size);
	size = stoi(string_size, &str_size);
	if (string_size.substr(str_size).length() > 1) {
		cout << "First line of input file must be an integer. (no extra spaces)" << endl;
		exit(1);
	}
		
	try{
		matrix.set_size(size);
		vector.setSize(size);
		input_file >> matrix;
		input_file >> vector;
		cout << "Testing this matrix: " << endl;
		cout << matrix << endl;
	}
	catch(const exception& e){
		input_file.close();
		cerr << e.what() << endl;
		exit(1);
	}
	input_file.close();
	return;
}

template<class Derived, class T>
void tester(char* argv[], BaseMatrix<Derived, T>& matrix, string title){
	cout << "Testing " << title << " matrix." << endl;
	Vector<T> test_vector;
	file_input(argv, matrix, test_vector);
	cout << "Copy constructor " << endl;
	BaseMatrix<Derived, T>& copy_matrix(matrix);
	cout << copy_matrix << endl;
	cout << "Matrix multiplication" << endl;
	cout << matrix * matrix << endl;
	cout << "Matrix addition" << endl;
	cout << matrix + matrix << endl;
	cout << "Matrix subtraction" << endl;
	cout << matrix - matrix << endl;
	cout << "Matrix-vector multiplication" << endl;
	cout << matrix * test_vector << endl;
	cout << "Matrix scalar multiplication" << endl;
	cout << matrix * 3 << endl;
	cout << "Matrix transpose " << endl;
	cout << ~matrix << endl;
	cout << "Diagonally dominant? " << (matrix.d_dom() ? "true" : "false") << endl << endl;
}

int main(int argc, char* argv[]){
	cout << setprecision(PRECISION);
	high_resolution_clock::time_point guass_start;
	high_resolution_clock::time_point guass_finish;
	high_resolution_clock::time_point steep_start;
	high_resolution_clock::time_point steep_finish;
	if(argc != 3){
		cerr << "Please provide CL arg 1 with the name of the test file and CL arg 2 with the number of partitions." << endl;
		exit(1);
	}
	try{

		// ### Testing ###
		BaseMatrix<MeshMatrix<double>, double> *test_mesh = new MeshMatrix<double>(9, 4);
		BaseMatrix<GeneralMatrix<double>, double> *test_general = new GeneralMatrix<double>;
		tester(argv, *test_mesh, "Mesh");
		tester(argv, *test_general, "General");

		// ### PDE Approximation ###
		// Initializze Variables
		unsigned int partitions = atoi(argv[2]);
		unsigned int matrix_size = static_cast<unsigned int>(pow((partitions - 1), 2));
		BaseMatrix<MeshMatrix<double>, double> *mesh = new MeshMatrix<double>(matrix_size, partitions);
		GuassSiedel<MeshMatrix<double>, double> guass;
		SteepestDescent<MeshMatrix<double>, double> steep;
		GenerateBVector<double, left_bound, right_bound, upper_bound, lower_bound> generate;
		Vector<double> vec = generate(partitions);
		
		// Run and time Guass-Siedel
		guass_start = high_resolution_clock::now();
		Vector<double> guass_result = guass(*mesh, vec);
		guass_finish = high_resolution_clock::now();

		// Run and time Steepest Descent
		steep_start = high_resolution_clock::now();
		Vector<double> steep_result = steep(*mesh, vec);
		steep_finish = high_resolution_clock::now();

		// Output times
		duration<double> guass_time = duration_cast<duration<double>>(guass_finish - guass_start);
		duration<double> steep_time = duration_cast<duration<double>>(steep_finish - steep_start);
		cout << "GuassSiedel finished in " << guass_time.count() << " seconds." << endl;
		cout << "SteepestDescent finished in " << steep_time.count() << " seconds." << endl;
		
		// Output data to CSV
		ofstream output_file;
		output_file.open("solution_approx.csv");
		unsigned int count = 0;
		for(unsigned int i=0; i < partitions-1; i++){
			for(unsigned int j=0; j < partitions-1; j++){
				output_file << static_cast<double>(i+1)/partitions << ", " << static_cast<double>(j+1)/partitions << ", " << steep_result[count] << "\n";
				count++;
			}
		}
		output_file << "\n";
	}
	catch(const exception& e){
		cerr << e.what() << endl;
	}
	
	return 0;
}