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
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <math.h>
using namespace std;	

const int PRECISION = 8;

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
		vector.set_size(size);
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
	try{
		MeshMatrix<double> mesh();
	}
	catch(const exception& e){
		cerr << e.what() << endl;
	}
	
	return 0;
}