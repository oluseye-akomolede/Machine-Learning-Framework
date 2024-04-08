#include <iostream>
#include "NN_test.h"
#include "nn_optimizer.h"
#include "mnist_reader.h"
#include <chrono>

using namespace std;

int main()
{
	mnist_reader mr;
	mr.open_mnist("C:\\Users\\seye1\\OneDrive\\Documents\\Research\\ML Architecture\\FrameworkFiles\\MNIST\\archive\\train-images.idx3-ubyte",
				  "C:\\Users\\seye1\\OneDrive\\Documents\\Research\\ML Architecture\\FrameworkFiles\\MNIST\\archive\\train-labels.idx1-ubyte");
	NN_test my_nn;
	nn_optimizer opti(0.02,0.025, (float)log(0.99),(float)log(0.99));
	

	int batch_size = 32;
	int num_epochs = 100;
	int num_epochs_update = 10;

	float curr_alpha;
	float curr_beta;


	for (int q = 0; q < num_epochs; q++)
	{
		//auto old_duration = chrono::round<chrono::milliseconds>(chrono::duration<double>{1000});
		while (mr.check_batching() == false)
		{
			matrix* batch = mr.get_batch(batch_size);
			matrix* y_bs = mr.get_label_batch(batch_size);
			
			if (batch->get_columns() > 0)
			{
				
				curr_alpha = opti.get_current_alpha();
				curr_beta = opti.get_current_beta();
				//auto beg = chrono::high_resolution_clock::now();
				my_nn.train(*batch, *y_bs, curr_alpha, curr_beta);
				//auto end = chrono::high_resolution_clock::now();

				/*auto duration = chrono::duration_cast<chrono::milliseconds>(end - beg);
				if (duration < old_duration)
				{
					old_duration = duration;
					cout << "Minimum elapsed time: " << duration.count() << endl;
				}*/
				

				
				batch->clear();
				y_bs->clear();

				delete batch;
				delete y_bs;
			}
		}
		mr.reset_batcher();

		if (q % 1 == 0)
		{
			matrix* batch = mr.get_batch(100);
			matrix* y_bs = mr.get_label_batch(100);
			float pred_rate = my_nn.evaluate(*batch, *y_bs);
			cout << "Iteration: " << q << endl << "Training data prediction rate: " << pred_rate << endl;

			batch->clear();
			y_bs->clear();

			delete batch;
			delete y_bs;
		}

		mr.reset_batcher();

		if (q % num_epochs_update == 0)
		{
			opti.update_alpha_beta(q / num_epochs_update, q / num_epochs_update);
		}

	}

	mr.open_mnist("C:\\Users\\seye1\\OneDrive\\Documents\\Research\\ML Architecture\\FrameworkFiles\\MNIST\\archive\\t10k-images.idx3-ubyte",
				  "C:\\Users\\seye1\\OneDrive\\Documents\\Research\\ML Architecture\\FrameworkFiles\\MNIST\\archive\\t10k-labels.idx1-ubyte");

	cout << "Final Evaluation" << endl;
	matrix* batch = mr.get_total_batch();
	matrix* y_bs = mr.get_total_labels();

	float pred_rate = my_nn.evaluate(*batch, *y_bs);
	cout << "Final prediction rate: " << pred_rate << endl;

	batch->clear();
	y_bs->clear();

	delete batch;
	delete y_bs;

	

	return 0;
}