#include <iostream>
#include <sstream>
#include <fstream>
#include <math.h>
#include <vector>
#include "classifier.h"
/**
 * Initializes GNB
 */
GNB::GNB() {

}

GNB::~GNB() {}

void GNB::train(vector<vector<double>> data, vector<string> labels)
{
	/*
		Trains the classifier with N data points and labels.

		INPUTS
		data - array of N observations
		  - Each observation is a tuple with 4 values: s, d, 
		    s_dot and d_dot.
		  - Example : [
			  	[3.5, 0.1, 5.9, -0.02],
			  	[8.0, -0.3, 3.0, 2.2],
			  	...
		  	]

		labels - array of N labels
		  - Each label is one of "left", "keep", or "right".
	*/

 	// Loop limit variables
	const int data_points = static_cast<int>(data.size());
	const int states = static_cast<int>(data[0].size());
	const int label_count = static_cast<int>(possible_labels.size());


	// Calculate Means
	// Collect and sum states based on label
	for(int i = 0; i < data_points; ++i)
	{
		for(int j = 0; j < states; ++j)
		{
			if(labels[i] == "left")
			{
				means[0][j] += data[i][j];
				if(j == states - 1)	counter[0] += 1;		// increment counter at the last iteration
			}
			else if(labels[i] == "keep")
			{
				means[1][j] += data[i][j];
				if(j == states - 1)	counter[1] += 1;		// increment counter at the last iteration
			}
			else
			{
				means[2][j] += data[i][j];
				if(j == states - 1)	counter[2] += 1;		// increment counter at the last iteration
			}
		}
	}

	// Divide sums from above by counts to get mean
	for(int i = 0; i < label_count; ++i)
	{
		for(int j = 0; j < states; ++j)
		{
			means[i][j] /= counter[i];			
		}
	}
	

	// Calculates Variance
	// Collect Squared Sum
	for(int i = 0; i < data_points; ++i)
	{
		for(int j = 0; j < states; ++j)
		{
			if(labels[i] == "left")
			{
				double del = pow((data[i][j] - means[0][j]), 2);
				variance[0][j] += del;	
			}
			else if(labels[i] == "keep")
			{
				double del = pow((data[i][j] - means[1][j]), 2);
				variance[1][j] += del;
			}
			else
			{
				double del = pow((data[i][j] - means[2][j]), 2);
				variance[2][j] += del;
			}
		}
	}

	// Divide Sums from above by counts to get variance
	for(int i = 0; i < label_count; ++i)
	{
		for(int j = 0; j < states; ++j)
		{
			variance[i][j] /= (counter[i]-1);			
		}
	}


	/*
	// Prints Means
	for(int i = 0; i < label_count; ++i)
	{
		for(int j = 0; j < states; ++j)
		{
			std::cout << means[i][j] << "\t\t";			
		}
		std::cout << counter[i] << std::endl;
	}

	std::cout << std::endl;

	// Prints Variance 
	for(int i = 0; i < label_count; ++i)
	{
		for(int j = 0; j < states; ++j)
		{
			std::cout << variance[i][j] << "\t\t";			
		}
		std::cout << counter[i] << std::endl;
	}
	*/

}

string GNB::predict(vector<double> obs)
{
	/*
		Once trained, this method is called and expected to return 
		a predicted behavior for the given observation.

		INPUTS

		observation - a 4 tuple with s, d, s_dot, d_dot.
		  - Example: [3.5, 0.1, 8.5, -0.2]

		OUTPUT

		A label representing the best guess of the classifier. Can
		be one of "left", "keep" or "right".
		"""
		# TODO - complete this
	*/

	// Iteration Parameters
	const int obs_len = static_cast<int>(obs.size());
	const int label_count = static_cast<int>(possible_labels.size());

	const double pi = 3.14159265;


	// Calculate Probability Densities
	vector<vector<double>> pred{3, {0, 0, 0, 0}};

	for(int i = 0; i < label_count; ++i)
	{
		for(int j = 0; j < obs_len; ++j)
		{
			double denom = sqrt( 2 * pi *  variance[i][j]);
			double exp_val = -pow( (obs[j] - means[i][j]), 2) / (2 * variance[i][j]);

			pred[i][j] = (1 / denom) * exp(exp_val);
			//std::cout << pred[i][j] << " ";
		}
		//std::cout << "\n";
		
	}

	// Calculate product of Probability Densities
	vector<double> prob_prod {0, 0, 0};

	for(int i = 0; i < label_count; ++i)
	{
		double temp_prod{1};
		for(int j = 0; j < obs_len; ++j)
		{
			temp_prod *= pred[i][j];
		}
		prob_prod[i] = temp_prod * (counter[i]/750);		
		//std::cout << prob_prod[i] << " ";
	}

	int pred_label{0};
	double max_pred{0};
	for(int i = 0; i < label_count; ++i)
	{
		if(max_pred < prob_prod[i])
		{
			max_pred = prob_prod[i];
			pred_label = i;
		}
	}

	return this->possible_labels[pred_label];

}