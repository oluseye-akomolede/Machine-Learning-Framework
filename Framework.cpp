#include "Framework.h"

matrix::matrix()
{
	rows = 0;
	columns = 0;
	data = NULL;

}

matrix::matrix(const matrix &m)
{
	rows = m.get_rows();
	columns = m.get_columns();
	data = (float*)malloc(sizeof(float) * rows * columns);
	
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			data[i * columns + j] = m.get_data(i, j);
		}
	}

}

matrix::matrix(int r, int c)
{
	rows = r;
	columns = c;

	data = (float*)malloc(sizeof(float) * rows * columns);
	
	

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			data[i * columns + j] = 0;
		}
	}

}

matrix::~matrix()
{
	clear();
}

matrix matrix::T()
{
	matrix m(columns, rows);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			m.set_data(j, i, data[i*columns + j]);

		}
	}

	return m;
}


matrix_iterator matrix::operator[](int i)
{
	matrix_iterator m(i, rows, columns, data);
	return m;
}

matrix matrix::operator*(matrix m)
{
	if (get_columns() != m.get_rows())
	{
		throw("Matrix dimensions do not match!");
	}
	else
	{
		
		int rs = get_rows();
		int cs = get_columns();
		int cs2 = m.get_columns();

		//matrix* out = new matrix(rs, cs2);
		matrix out(rs, cs2);

		for (int i = 0; i < rs; i++)
		{
			for (int k = 0; k < cs; k++)
			{
				for (int j = 0; j < cs2; j++)
				{
					out.set_data(i, j, out.get_data(i,j) + (data[i*columns + k] * m.get_data(k, j)));
				}
			}
		}
		return out;
	}

	
}

matrix matrix::operator*(float input)
{
	int rs = rows;
	int cs = columns;
	matrix output(rs, cs);

	for (int i = 0; i < rs; i++)
	{
		for (int j = 0; j < cs; j++)
		{
			output.set_data(i,j, data[i * columns + j] * input);
		}
	}
	return output;
}

matrix matrix::operator+(float input)
{
	int rs = rows;
	int cs = columns;
	matrix output(rs, cs);

	for (int i = 0; i < rs; i++)
	{
		for (int j = 0; j < cs; j++)
		{
			output.set_data(i, j, data[i * columns + j] + input);
		}
	}

	return output;
}

matrix matrix::operator+(matrix m)
{
	auto rs = m.get_rows();
	auto cs = m.get_columns();
	matrix out;

	if (rs != get_rows() || cs != get_columns())
	{
		throw("Matrix dimensions must match under addition!");
	}
	else
	{
		out.set_dims(rs, cs);
		for (int i = 0; i < rs; i++)
		{
			for (int j = 0; j < cs; j++)
			{
				out.set_data(i, j, (data[i*columns + j] + m.get_data(i, j)));
			}
		}
	}

	return out;
}

matrix matrix::operator-(matrix m)
{
	auto rs = m.get_rows();
	auto cs = m.get_columns();
	matrix out;

	if (rs != get_rows() || cs != get_columns())
	{
		throw("Matrix dimensions must match under subtraction!");
	}
	else
	{
		out.set_dims(rs, cs);
		for (int i = 0; i < rs; i++)
		{
			for (int j = 0; j < cs; j++)
			{
				out.set_data(i, j, (data[i*columns + j] - m.get_data(i, j)));
			}
		}
	}

	return out;
}

matrix matrix::operator-(float input)
{
	int rs = rows;
	int cs = columns;
	matrix output(rs, cs);

	for (int i = 0; i < rs; i++)
	{
		for (int j = 0; j < cs; j++)
		{
			output.set_data(i, j, data[i * columns + j] - input);
		}
	}

	return output;
}

void matrix::operator=(matrix m)
{
	int rs = m.get_rows();
	int cs = m.get_columns();

	set_dims(rs, cs);

	for (int i = 0; i < rs; i++)
	{
		for (int j = 0; j < cs; j++)
		{
			data[i*columns + j] = m.get_data(i, j);
		}
	}
}

matrix matrix::operator^(matrix m)
{
	auto rs = m.get_rows();
	auto cs = m.get_columns();
	matrix out;

	if (rs != get_rows() || cs != get_columns())
	{
		throw("Matrix dimensions must match under subtraction!");
	}
	else
	{
		out.set_dims(rs, cs);
		for (int i = 0; i < rs; i++)
		{
			for (int j = 0; j < cs; j++)
			{
				out.set_data(i, j, (data[i*columns + j] * m.get_data(i, j)));
			}
		}
	}

	return out;
}

void matrix::set_dims(int r, int c)
{
	if (rows > 0) //if there's anything to delete
	{
		free(data);
		data = NULL;
	}

	//set new dimensions

	rows = r;
	columns = c;
	data = (float*)malloc(sizeof(float) * rows * columns);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			data[i * columns + j] = (float)0;
		}
	}

}

int matrix::get_rows() const
{
	return rows;
}


int matrix::get_columns() const
{
	return columns;
}



void matrix::set_data(int i, int j, float d_in)
{
	data[i*columns + j] = d_in;
}

float matrix::get_data(int i, int j) const
{
	return data[i*columns + j];
}

float* matrix::get_data_address(int i, int j)
{
	return &data[i*columns + j];
}

float* matrix::get_data_ptr() const
{
	return data;
}

void matrix::clear()
{
	rows = 0;
	columns = 0;
	if (data != NULL)
	{
		free(data);
		data = NULL;
	}
	
}



matrix_iterator::matrix_iterator(int in, int nr, int nc, float* data_ptr_in)
{
	i = in;
	num_rows = nr;
	num_cols = nc;
	data_ptr = data_ptr_in;
}

void matrix_iterator::set_i(int in)
{
	i = in;
}

void matrix_iterator::set_rows_cols(int i, int j)
{
	num_rows = i;
	num_cols = j;
}

void matrix_iterator::set_ptr(float* data_ptr_in)
{
	data_ptr = data_ptr_in;
}

float matrix_iterator::operator[](int j)
{
	if (j >= num_cols)
	{
		throw("Array index out of bounds! j:%i", j);
	}
	else
	{
		return data_ptr[(i * num_cols) + j];
	}
	
}

matrix_unit_test::matrix_unit_test()
{
	int q_rows = 20;
	int q_columns = 30;
	int b_rows = 20;
	int b_columns = 20;
	matrix q(q_rows, q_columns);
	matrix b(b_rows, b_columns);

	for (int i = 0; i < b_rows; i++)
	{
		for (int j = 0; j < b_columns; j++)
		{
			if (i == j)
			{
				b.set_data(i, j, 1);
			}
			else
			{
				b.set_data(i, j, 0);
			}
		}
	}

	int iter = 0;

	for (int i = 0; i < q_rows; i++)
	{
		for (int j = 0; j < q_columns; j++)
		{
			iter++;
			q.set_data(i, j, iter);
		}
	}

	matrix a = (b * q);


	for (int i = 0; i < q_rows; i++)
	{
		for (int j = 0; j < q_columns; j++)
		{
			if (q[i][j] != a[i][j])
			{
				throw("Matrix Error! %f != %f", q[i][j], a[i][j]);
			}
			else
			{
				std::cout << "q value: " << q[i][j] << std::endl;
				std::cout << "q mem address: " << q.get_data_address(i, j) << std::endl;
					
				std::cout << "a value: " << a[i][j] << std::endl;
				std::cout << "a mem address: " << a.get_data_address(i, j) << std::endl;
			}
		}
	}

	std::cout << "Test ended successfully!" << std::endl;
}

matrix sigm(matrix m)
{
	int rs = m.get_rows();
	int cs = m.get_columns();
	matrix out(rs, cs);
	for (int i = 0; i < rs; i++)
	{
		for (int j = 0; j < cs; j++)
		{
			out.set_data(i, j, 1 / (1 + exp(-1 * m.get_data(i, j))));
		}

	}

	return out;
}

matrix relu(matrix m)
{
	int rs = m.get_rows();
	int cs = m.get_columns();
	matrix out(rs, cs);
	for (int i = 0; i < rs; i++)
	{
		for (int j = 0; j < cs; j++)
		{
			float g_data = m.get_data(i, j);

			if (g_data > 0)
			{
				out.set_data(i, j, g_data);
			}
			else
			{
				out.set_data(i, j, (float)0);
			}

		}

	}

	return out;
}

matrix diff_relu(matrix m)
{
	int rs = m.get_rows();
	int cs = m.get_columns();
	matrix out(rs, cs);
	for (int i = 0; i < rs; i++)
	{
		for (int j = 0; j < cs; j++)
		{
			float g_data = m.get_data(i, j);

			if (g_data > 0)
			{
				out.set_data(i, j, (float)1);
			}
			else
			{
				out.set_data(i, j, (float)0);
			}

		}

	}

	return out;
}

matrix hard_tanh(matrix m)
{
	int rs = m.get_rows();
	int cs = m.get_columns();
	matrix out(rs, cs);
	for (int i = 0; i < rs; i++)
	{
		for (int j = 0; j < cs; j++)
		{
			float g_data = m.get_data(i, j);

			if (g_data > 1)
			{
				out.set_data(i, j, (float)1);
			}
			else if (g_data < -1)
			{
				out.set_data(i, j, (float)-1);
			}
			else
			{
				out.set_data(i, j, m.get_data(i, j));
			}

		}

	}

	return out;
}

matrix diff_hard_tanh(matrix m)
{
	int rs = m.get_rows();
	int cs = m.get_columns();
	matrix out(rs, cs);
	for (int i = 0; i < rs; i++)
	{
		for (int j = 0; j < cs; j++)
		{
			float g_data = m.get_data(i, j);

			if (g_data > 1)
			{
				out.set_data(i, j, (float)0);
			}
			else if (g_data < -1)
			{
				out.set_data(i, j, (float)0);
			}
			else
			{
				out.set_data(i, j, (float)1);
			}

		}

	}

	return out;
}

matrix leaky_relu(matrix m)
{
	int rs = m.get_rows();
	int cs = m.get_columns();
	float neg_alpha = 0.01;
	matrix out(rs, cs);
	for (int i = 0; i < rs; i++)
	{
		for (int j = 0; j < cs; j++)
		{
			float g_data = m.get_data(i, j);

			if (g_data > 0)
			{
				out.set_data(i, j, g_data);
			}
			else
			{
				out.set_data(i, j, neg_alpha * g_data);
			}

		}

	}

	return out;
}

matrix diff_leaky_relu(matrix m)
{
	int rs = m.get_rows();
	int cs = m.get_columns();
	float neg_alpha = 0.01;
	matrix out(rs, cs);
	for (int i = 0; i < rs; i++)
	{
		for (int j = 0; j < cs; j++)
		{
			float g_data = m.get_data(i, j);

			if (g_data > 0)
			{
				out.set_data(i, j, (float)1);
			}
			else
			{
				out.set_data(i, j, -1 * neg_alpha);
			}

		}

	}

	return out;
}

matrix m_tanh(matrix m)
{
	int rs = m.get_rows();
	int cs = m.get_columns();
	matrix out(rs, cs);

	for (int i = 0; i < rs; i++)
	{
		for (int j = 0; j < cs; j++)
		{
			out.set_data(i, j, (float)tanh(m[i][j]));
		}
	}

	return out;
}