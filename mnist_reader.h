#pragma once
#include "Framework.h"
#include <fstream>

uint32_t swap_endian(uint32_t val);

class mnist_reader
{
public:
	mnist_reader();
	void open_mnist(const char* image_filename, const char* label_filename);
	matrix* get_batch(int batch_size);
	matrix* get_label_batch(int batch_size);

	void get_random_batch(int batch_size, matrix* out_b, matrix* out_labels);

	matrix* get_total_batch();
	matrix* get_total_labels();

	bool check_batching();
	void reset_batcher();
private:
	matrix* mnist_table;
	matrix* mnist_label_table;

	int num_records;
	int mnist_batch_iterator;
	int mnist_label_batch_iterator;

	bool batch_ended;

};
