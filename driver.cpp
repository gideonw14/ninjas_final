/*******************************************************************************
	Filename: 	driver.cpp
	Programmer: Gideon Walker
	Class: 		CS 5201 - Prof. Price
	Assignment: 6 - An Abstract Matrix Class and Derivatives
	Due: 		Wednesday, April 18, 2018

	Description:
		Driver file for homework #6
*******************************************************************************/

#include "BaseMatrix.h"
#include "MeshMatrix.h"
#include "GeneralMatrix.h"
#include "GuassSiedel.h"
#include "steepestdescent.h"
#include "GenerateLinearSystem.h"
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
void file_input(int argc, char* argv[], U& matrix, Vector<T>& vector){
	if(argc != 2){
		cerr << "Please give exactly 1 CL arg with a valid filename." << endl;
		exit(1);
	}

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
	}
	catch(const exception& e){
		input_file.close();
		cerr << e.what() << endl;
	}
	input_file.close();
	return;
}

int main(int argc, char* argv[]){
	cout << setprecision(PRECISION);
	high_resolution_clock::time_point guass_start;
	high_resolution_clock::time_point guass_finish;
	high_resolution_clock::time_point steep_start;
	high_resolution_clock::time_point steep_finish;
	if(argc != 2){
		cerr << "Please give exactly 1 CL arg with the number of partitions." << endl;
		exit(1);
	}
	try{
		unsigned int partitions = atoi(argv[1]);
		unsigned int matrix_size = static_cast<unsigned int>(pow((partitions - 1), 2));
		BaseMatrix<MeshMatrix<double>, double> *mesh = new MeshMatrix<double>(matrix_size, partitions);
		GuassSiedel<MeshMatrix<double>, double> guass;
		SteepestDescent<MeshMatrix<double>, double> steep;
		GenerateBVector<double, left_bound, right_bound, upper_bound, lower_bound> generate;
		Vector<double> vec = generate(partitions);
		
		guass_start = high_resolution_clock::now();
		Vector<double> guass_result = guass(*mesh, vec);
		guass_finish = high_resolution_clock::now();

		steep_start = high_resolution_clock::now();
		Vector<double> steep_result = steep(*mesh, vec);
		steep_finish = high_resolution_clock::now();

		duration<double> guass_time = duration_cast<duration<double>>(guass_finish - guass_start);
		duration<double> steep_time = duration_cast<duration<double>>(steep_finish - steep_start);
		cout << "GuassSiedel finished in " << guass_time.count() << " seconds." << endl;
		cout << "SteepestDescent finished in " << steep_time.count() << " seconds." << endl;

		cout << "SteepestDescent result" << endl;
		
		unsigned int count = matrix_size - 1;
		for(unsigned int i=partitions-1; i > 0; i--){
			for(unsigned int j=partitions-1; j > 0; j--){
				cout << steep_result[count] << " ";
				count--;
			}
			cout << endl;
		}
		cout << endl;
	}
	catch(const exception& e){
		cerr << e.what() << endl;
	}
	
	return 0;
}