#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <random>
#include <unordered_map>

struct free_delete
{
	void operator()(void* x) { free(x); }
};

class matrix_iterator
{
public:
	matrix_iterator(int i, int nr, int nc, float* data_ptr_in);
	void set_i(int in);
	void set_rows_cols(int i, int j);
	void set_ptr(float* in);
	float operator[](int j);
private:
	int i;
	float* data_ptr;
	int num_rows;
	int num_cols;
};

class matrix
{
public:
	matrix();
	matrix(const matrix& m);
	matrix(int r, int c);
	~matrix();

	matrix T();
	matrix_iterator operator[](int i);
	matrix operator*(matrix m);
	matrix operator*(float input);
	matrix operator+(float input);
	matrix operator+(matrix m);
	matrix operator-(matrix m);
	matrix operator-(float input);
	void operator=(matrix m);
	matrix operator^(matrix m);


	void set_dims(int r, int c);
	int get_rows() const;
	
	int get_columns() const;
	

	void set_data(int i, int j, float data_in);
	float get_data(int i, int j)const;
	float* get_data_address(int i, int j);
	float* get_data_ptr() const;

	void clear();
	

private:
	int rows;
	int columns;
	float* data; //contains the entire matrix. 
};

class matrix_unit_test
{
public:
	matrix_unit_test();

};


matrix sigm(matrix m);

matrix relu(matrix m);

matrix diff_relu(matrix m);

matrix hard_tanh(matrix m);

matrix diff_hard_tanh(matrix m);

matrix leaky_relu(matrix m);

matrix diff_leaky_relu(matrix m);

matrix m_tanh(matrix m);


