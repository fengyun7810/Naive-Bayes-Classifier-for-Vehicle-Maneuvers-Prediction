#ifndef CLASSIFIER_H
#define CLASSIFIER_H
#include <iostream>
#include <sstream>
#include <fstream>
#include <math.h>
#include <vector>

using namespace std;

class GNB {
public:

	vector<string> possible_labels = {"left","keep","right"};


	/**
  	* Constructor
  	*/
 	GNB();

	/**
 	* Destructor
 	*/
 	virtual ~GNB();





	// Mean and Variance 2D vectors
	vector<vector<double>> means{3, {0, 0, 0, 0}};
	vector<vector<double>> variance{3, {0, 0, 0, 0}};

	// label counter to keep count of each label, double type for straight forward double/double for mean calc
	vector<double> counter{0, 0, 0};

	// prediction prob
 	void train(vector<vector<double> > data, vector<string>  labels);

  	string predict(vector<double>);

};

#endif



