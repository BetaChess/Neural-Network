#pragma once
#ifndef NEURAL_CLASSES_H_
#define NEURAL_CLASSES_H_

class hidden {
public:
	hidden();
	
	
	double value;
	std::string type = "sig";
	int layer;

	void convert(std::string typeD);
	double Fvalue;
};

class axon {
public:
	axon();

	double weight;
	int input;
	int inputLayer;
	int output;
	int outputLayer;
};

class mutation {
public:
	mutation();

	//copy constructer
	mutation(const mutation& source);

	//overloaded assignment operator
	mutation& operator=(const mutation& source);


	double mutateChance;
	double small;
	double medium;
	double large;

	double major;
	double reverse;
	double remove;

	double mtChange;

	void mutateStats();
};

class network {
	//friend std::ostream& operator<<(std::ostream& os, const network& gc);

public:
	

	mutation mutchance;
	void createArrays(int inputs, int layers, int hiddenperlayer, int outputs, int axons, int genomee);
	int MaxPLayerC = 0;
	std::string NTYPE = "standard";
	double * Ninput;
	hidden ** Nhidden;
	axon * Naxon;
	double * NGENOME;
	std::string * types;
	double fitness = 0;
	double successrate = 0;
	int ident = 0;

	//data
	int Nlayers;
	int Nhiddenperlayer;
	int Ninputs;
	int NAxons;
	int Noutputs;


	network();
	//copy constructer
	network(const network& source);

	//overloaded assignment operator
	network& operator=(const network& source);

	//destructer
	~network();

	//functions
	void Randomize(int);
	void SetAxonData(int inputs, int hiddenperlayer, int layers, int outputs, int axonsC);
	void Calculate(int axonscount, int outputs);
	void SethiddenTYPES(std::string *);
	void FINDFITNESS(int outputs, int inputs, int axons);
	void SetDETECTORS(std::string testWord);
	void mutate(int axons);
	void reset();
};

#endif