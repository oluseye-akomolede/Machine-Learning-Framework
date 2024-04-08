#include "mnist_reader.h"

using namespace std;

mnist_reader::mnist_reader()
{
    mnist_table = NULL;
    mnist_label_table = NULL;

    num_records = 0;
    mnist_batch_iterator = 0;
    mnist_label_batch_iterator = 0;

   batch_ended = false;
}

void mnist_reader::open_mnist(const char* image_filename, const char* label_filename)
{
    std::ifstream image_file;
    std::ifstream label_file;
    image_file.open(image_filename, std::ios::in | std::ios::binary);
    label_file.open(label_filename, std::ios::in | std::ios::binary);

   

    uint32_t magic;
    uint32_t num_items;
    uint32_t num_labels;
    uint32_t rows;
    uint32_t cols;

    image_file.read(reinterpret_cast<char*>(&magic), 4);
    magic = swap_endian(magic);
    if (magic != 2051) {
        cout << "Incorrect image file magic: " << magic << endl;
        throw("Incorrect image file magic: ");
        return;
    }

    label_file.read(reinterpret_cast<char*>(&magic), 4);
    magic = swap_endian(magic);
    if (magic != 2049) {
        cout << "Incorrect image file magic: " << magic << endl;
        throw("Incorrect image file magic: ");
        return;
    }

    image_file.read(reinterpret_cast<char*>(&num_items), 4);
    num_items = swap_endian(num_items);
    label_file.read(reinterpret_cast<char*>(&num_labels), 4);
    num_labels = swap_endian(num_labels);
    if (num_items != num_labels) {
        cout << "image file nums should equal to label num" << endl;
        return;
    }

    num_records = num_items;

    image_file.read(reinterpret_cast<char*>(&rows), 4);
    rows = swap_endian(rows);
    image_file.read(reinterpret_cast<char*>(&cols), 4);
    cols = swap_endian(cols);

    mnist_table = new matrix(rows * cols, num_items);
    mnist_label_table = new matrix(10, num_items);


    for (int item_id = 0; item_id < num_items; ++item_id) 
    {
        char label;
        char* pixels = new char[rows * cols];
        float* fpixels = new float[rows * cols];
        // read image pixel
        image_file.read(pixels, ((int)rows) * ((int)cols));
        // read label
        label_file.read(&label, 1);

        int label_idx = (int)label;

        for (int i = 0; i < rows * cols; i++)
        {
            fpixels[i] = (float)((int)pixels[i]) / (float)255.0;
        }

        for (int i = 0; i < 10; i++)
        {
            if (i == label_idx)
            {
                mnist_label_table->set_data(i, item_id, 1.0);
            }
            else
            {
                mnist_label_table->set_data(i, item_id, 0.0);
            }
        }

        for (int i = 0; i < rows * cols; i++)
        {
            mnist_table->set_data(i, item_id, fpixels[i]);
        }

        
        delete[] pixels;
        delete[] fpixels;
    }

    image_file.close();
    label_file.close();
   
}

matrix* mnist_reader::get_batch(int batch_size)
{
    int test_ind = mnist_batch_iterator + batch_size - 1;
    int iterations = 0;
    matrix* out_matrix;
    if (test_ind >= (num_records-1))
    {
        batch_ended = true;
        iterations = num_records - mnist_batch_iterator;

        if (iterations <= 0)
        {
            out_matrix = new matrix(0, 0);
            mnist_batch_iterator = 0;
            return out_matrix;
        }
    }
    else
    {
        iterations = batch_size;
    }
    int rs = mnist_table->get_rows();
    out_matrix = new matrix(rs, iterations);

    for (int i = 0; i < iterations; i++)
    {

        for (int j = 0; j < rs; j++)
        {
            out_matrix->set_data(j, i, mnist_table->get_data(j, mnist_batch_iterator));
        }
        mnist_batch_iterator++;
    }

    if (batch_ended == true)
    {
        mnist_batch_iterator = 0;
    }

    return out_matrix;

}

matrix* mnist_reader::get_label_batch(int batch_size)
{
    int test_ind = mnist_label_batch_iterator + batch_size - 1;
    int iterations = 0;
    matrix* out_matrix;
    if (test_ind >= (num_records-1))
    {
        batch_ended = true;
        iterations = num_records - mnist_label_batch_iterator;

        if (iterations <= 0)
        {
            out_matrix = new matrix(0, 0);
            mnist_label_batch_iterator = 0;
            return out_matrix;
        }
    }
    else
    {
        iterations = batch_size;
    }
    int rs = mnist_label_table->get_rows();
    out_matrix = new matrix(rs, iterations);

    for (int i = 0; i < iterations; i++)
    {

        for (int j = 0; j < rs; j++)
        {
            out_matrix->set_data(j, i, mnist_label_table->get_data(j, mnist_label_batch_iterator));
        }
        mnist_label_batch_iterator++;
    }

    if (batch_ended == true)
    {
        mnist_label_batch_iterator = 0;
    }

    return out_matrix;
}

void mnist_reader::get_random_batch(int batch_size, matrix* out_b, matrix* out_label)
{
    int rs = mnist_label_table->get_rows();
    int rsb = mnist_table->get_rows();
    out_b = new matrix(rsb, batch_size);
    out_label = new matrix(rs, batch_size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, num_records);

    for (int i = 0; i < batch_size; i++)
    {
        int rand_int = distr(gen);
        for (int j = 0; j < rs; j++)
        {
            out_label->set_data(j, i, mnist_label_table->get_data(j, rand_int));
        }

        for (int j = 0; j < rsb; j++)
        {
            out_b->set_data(j, i, mnist_table->get_data(j, rand_int));
        }
    }
}

bool mnist_reader::check_batching()
{
    return batch_ended;
}

void mnist_reader::reset_batcher()
{
    batch_ended = false;
    mnist_label_batch_iterator = 0;
    mnist_batch_iterator = 0;
}

matrix* mnist_reader::get_total_batch()
{
    return mnist_table;
}

matrix* mnist_reader::get_total_labels()
{
    return mnist_label_table;
}

uint32_t swap_endian(uint32_t val) {
    val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
    return (val << 16) | (val >> 16);
}