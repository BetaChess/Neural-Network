#include "stdafx.h"

#include <string>
#include <cmath>
#include <iostream>

#include "Neural classes.h"
#include "words.h"

const double e = 2.71828182846;

words word;

double to_pos(double input) {
	if (input < 0) {
		return -input;
	}
	else {
		return input;
	}
}

hidden::hidden() : Fvalue(0.1), value(0.1), type(""), layer(1)
{

}

void hidden::convert(std::string typeD) {
	double temp = Fvalue;
	//std::cout << "f " << temp << std::endl;
	bool m = false;
	if (typeD == "to0.5") {
		if (temp < 0) {
			temp = temp * (-1);
			m = true;
		}

		while (temp > 1000)
		{
			temp = temp / 10;
		}
		temp = (1 - 100 / (100 + temp));
		if (m) {
			temp = temp * (-1);
		}
	}
	else if (typeD == "sig") {
		if (temp < 0) {
			temp = temp * (-1);
		}
		while (temp > 10)
		{
			temp = temp / 10;
		}
		temp = temp * (-1);
		temp = 1 / (1 + pow(e, -temp)) - 0.5;
	}
	else if (typeD == "pos_add") {
		while ((temp > 1 && temp != 1) || (temp < 0 && (temp < -1 || temp == -1))) {
			temp = temp / 10;
		}
		if (temp < 0) {
			temp = temp * -1;
		}
	}
	else {
		while ((temp > 1 && temp != 1) || (temp < 0 && (temp < -1 || temp == -1))) {
			temp = temp / 10;
		}
	}
	value = temp;
}

axon::axon() : weight(0), input(0), inputLayer(0), output(0), outputLayer(0)
{

}

mutation::mutation() 
{
	mutateChance = (rand() % 100) / 100.0;
	small = 0.5;
	medium = (rand() % 100) / 100.0 / 2.0;
	large = 0.5 - medium;
	mtChange = (rand() % 100) / 100.0 / 4.0;
	major = (rand() % 100) / 100.0;
	reverse = (rand() % 100) / 100.0;
	remove = 1.0 - reverse;
}

void mutation::mutateStats() {
	double temp = (rand() % 100) / 100.0;
	double change;

	//First mutate mutation value mutation value.
	if (temp <= 0.1) {
		double change = 0;

		temp = (rand() % 100) / 100.0;
		if (temp <= 0.5) {
			change = (rand() % 100) / 100.0;
		}
		else {
			change = -(rand() % 100) / 100.0;
		}

		mtChange += change;

		if (mtChange < 0.05) {
			mtChange = 0.05;
		}
		else if (mtChange > 0.9) {
			mtChange = 0.9;
		}
	}

	//Change orther mut values using mtChange Variable.
	temp = (rand() % 100) / 100.0;
	if (temp <= mtChange) {
		temp = (rand() % 100) / 100.0;

		//mutate large chance
		if (temp <= 1 / 7.0) {
			temp = (rand() % 100) / 100.0;

			if (temp <= 0.5) {
				change = (rand() % 100) / 100.0 / 4.0;
			}
			else {
				change = -(rand() % 100) / 100.0 / 4.0;
			}

			large += change;

			for (int i = 0; i < (to_pos(change) * 100); i++) {
				temp = (rand() % 100) / 100.0;

				if (temp <= 0.5) {
					small -= 0.01;
				}
				else {
					medium -= 0.01;
				}
			}
		}

		//mutate Major chance
		else if (temp <= 2 / 7.0) {
			temp = (rand() % 100) / 100.0;

			if (temp <= 0.5) {
				change = (rand() % 100) / 100.0 / 4.0;
			}
			else {
				change = -(rand() % 100) / 100.0 / 4.0;
			}

			major += change;
		}

		//mutate medium change
		else if (temp <= 3 / 7.0) {
			temp = (rand() % 100) / 100.0;

			if (temp <= 0.5) {
				change = (rand() % 100) / 100.0 / 4.0;
			}
			else {
				change = -(rand() % 100) / 100.0 / 4.0;
			}

			medium += change;

			for (int i = 0; i < (to_pos(change) * 100); i++) {
				temp = (rand() % 100) / 100.0;

				if (temp <= 0.5) {
					small -= 0.01;
				}
				else {
					large -= 0.01;
				}
			}
		}

		//mutate mutateChance
		else if (temp <= 4 / 7.0) {
			temp = (rand() % 100) / 100.0;

			temp = (rand() % 100) / 100.0;

			if (temp <= 0.5) {
				change = (rand() % 100) / 100.0 / 4.0;
			}
			else {
				change = -(rand() % 100) / 100.0 / 4.0;
			}

			mutateChance += change;
		}

		//mutate Remove chance
		else if (temp <= 5 / 7.0) {
			temp = (rand() % 100) / 100.0;

			temp = (rand() % 100) / 100.0;

			if (temp <= 0.5) {
				change = (rand() % 100) / 100.0 / 4.0;
			}
			else {
				change = -(rand() % 100) / 100.0 / 4.0;
			}

			remove += change;

			reverse -= change;
		}

		//mutate reverse chance
		else if (temp <= 6 / 7.0) {
			temp = (rand() % 100) / 100.0;

			temp = (rand() % 100) / 100.0;

			if (temp <= 0.5) {
				change = (rand() % 100) / 100.0 / 4.0;
			}
			else {
				change = -(rand() % 100) / 100.0 / 4.0;
			}

			reverse += change;

			remove -= change;
		}

		//mutate small chance
		else if (temp <= 1) {
			temp = (rand() % 100) / 100.0;

			if (temp <= 0.5) {
				change = (rand() % 100) / 100.0 / 4.0;
			}
			else {
				change = -(rand() % 100) / 100.0 / 4.0;
			}

			small += change;

			for (int i = 0; i < (to_pos(change) * 100); i++) {
				temp = (rand() % 100) / 100.0;

				if (temp <= 0.5) {
					large -= 0.01;
				}
				else {
					medium -= 0.01;
				}
			}
		}

		else {
			std::exit(-1);
		}
	}

	//check values
b2:
	if (remove < 0.01) {
		remove = 0.01;
	}
	else if (remove > 0.98) {
		remove = 0.98;
	}
	if (reverse < 0.01) {
		reverse = 0.01;
	}
	else if (reverse > 0.98) {
		reverse = 0.98;
	}

	if (remove + reverse != 1) {
		change = 1 - remove + reverse;

		temp = (rand() % 100) / 100.0;
		if (temp <= 0.5) {
			remove += change;
		}
		else {
			reverse += change;
		}
	}

	if (major < 0.01) {
		major = 0.01;
	}
	else if (major > 0.45) {
		major = 0.4;
	}

	if (small < 0.01) {
		small = 0.01;
	}
	else if (small > 0.98) {
		small = 0.98;
	}
	if (medium < 0.01) {
		medium = 0.01;
	}
	else if (medium > 0.98) {
		medium = 0.98;
	}
	if (large < 0.01) {
		large = 0.01;
	}
	else if (large > 0.98) {
		large = 0.98;
	}
	if (mutateChance < 0.05) {
		mutateChance = 0.1;
	}

	if (large + medium + small != 1) {
	b1:
		change = 1 - (large + medium + small);

		temp = (rand() % 100) / 100.0;
		if (temp <= 1 / 3.0) {
			small += change;
		}
		else if (temp <= 2 / 3.0) {
			medium += change;
		}
		else if (temp <= 3 / 3.0) {
			large += change;
		}
		else {
			std::exit(-100000);
		}
		//std::cout << (mutchance.large + mutchance.medium + mutchance.small);
		if (large + medium + small != 1) {
			goto b1;
		}
		goto b2;
	}
}

// copy constructer
mutation::mutation(const mutation& source)
{
	std::cout << "invoked copy constructer \n";

	mutateChance = source.mutateChance;
	small = source.small;
	medium = source.medium;
	large = source.large;
	major = source.major;
	reverse = source.reverse;
	remove = source.remove;
}

//overloaded assignmetn operator
mutation& mutation::operator=(const mutation& source)
{
	std::cout << "overloaded assignment invoked \n";

	//check for self assignment
	if (this == &source) {
		return *this;
	}

	mutateChance = source.mutateChance;
	small = source.small;
	medium = source.medium;
	large = source.large;
	major = source.major;
	reverse = source.reverse;
	remove = source.remove;
}


network::network() 
{
	
}

network::network(const network& source)
{
	std::cout << "invoked copy constructer \n";
	createArrays(source.Ninputs, source.Nlayers, source.Nhiddenperlayer, source.Noutputs, source.NAxons, source.NAxons);
	successrate = source.successrate;
	fitness = source.fitness;
	NTYPE = source.NTYPE;

	for (int i = 0; i < NAxons; i++) {
		Naxon[i].weight = source.Naxon[i].weight;
		NGENOME[i] = source.NGENOME[i];
	}
	for (int i = 0; i < Nlayers; i++) {
		types[i] = source.types[i];
	}
}

//overloaded assignment operator
network& network::operator=(const network&source)
{
	std::cout << "overloaded assignment invoked \n";

	//check for self assignment
	if (this == &source) {
		return *this;
	}

	createArrays(source.Ninputs, source.Nlayers, source.Nhiddenperlayer, source.Noutputs, source.NAxons, source.NAxons);
	successrate = source.successrate;
	fitness = source.fitness;
	NTYPE = source.NTYPE;

	for (int i = 0; i < NAxons; i++) {
		Naxon[i].weight = source.Naxon[i].weight;
		NGENOME[i] = source.NGENOME[i];
	}
	for (int i = 0; i < Nlayers; i++) {
		types[i] = source.types[i];
	}

	return *this;
}

//destructer 
network::~network()
{
	//std::cout << "destructer invoked \n";

	delete[] Naxon;
	delete[] NGENOME;
	delete[] Nhidden;
	delete[] Ninput;
	delete[] types;
}

void  network::SethiddenTYPES(std::string * input) {
	for (int i = 0; i < Nlayers; i++) {
		for (int x = 0; x < Nhiddenperlayer; x++) {
			Nhidden[i][x].type = input[i];
		}
	}
}

void network::createArrays(int inputs, int layers, int hiddenplayer, int outputs, int axons, int genomee) {
	if (inputs > hiddenplayer) {
		MaxPLayerC = inputs;
	}
	else if (outputs > hiddenplayer) {
		MaxPLayerC = outputs;
	}
	else {
		MaxPLayerC = hiddenplayer;
	}

	Nlayers = layers;
	Nhiddenperlayer = hiddenplayer;
	NAxons = genomee;
	Ninputs = inputs;
	Noutputs = outputs;

	Ninput = new double[inputs];
	Nhidden = new hidden*[layers];
	Nhidden[0] = new hidden[MaxPLayerC];
	for (int i = 1; i < layers - 1; i++) {
		Nhidden[i] = new hidden[MaxPLayerC];
	}
	Nhidden[layers - 1] = new hidden[MaxPLayerC];
	Naxon = new axon[genomee];
	NGENOME = new double[genomee];
	types = new std::string[layers];
}

void network::Randomize(int axon) {
	for (int i = 0; i < axon; i++) {
		int temp = (rand() % 100);
		double temp2 = ((rand() % 100) / 100.0);
		if (temp >= 50 || temp2 == 0) {
			NGENOME[i] = temp2;
			Naxon[i].weight = temp2;
		}
		else {
			NGENOME[i] = -(temp2);
			Naxon[i].weight = -(temp2);
		}
	}
}

void network::SetAxonData(int inputs, int hiddenperlayer, int layers, int outputs, int axonsC) {
	if (NTYPE == "standard") {
		int count = 0;
		int temp = 0;
		int NON = 0;
		int OLN = 1;
		int Next_output_Axon_C;

		// first layer (i.e. input to hidden or output)
		if (layers == 2) {
			NON = outputs;
			Next_output_Axon_C = inputs * outputs;
		}
		else {
			NON = hiddenperlayer;
			Next_output_Axon_C = hiddenperlayer * inputs;
		}
		for (int i = 0; i < axonsC; i++) {

			if (i == Next_output_Axon_C) {
				OLN++;
				count = 0;
				if (OLN == layers) {
					NON = hiddenperlayer*outputs;
					Next_output_Axon_C = axonsC;
				}
				else {
					NON = hiddenperlayer;
					Next_output_Axon_C += hiddenperlayer*hiddenperlayer;
				}
			}

			if ((i != 0) && (i % NON == 0)) {
				count++;
			}
			Naxon[i].input = count;
			Naxon[i].output = i % NON ;
			Naxon[i].outputLayer = OLN;
			Naxon[i].inputLayer = OLN - 1;

		}
	}
}

void network::Calculate(int axonscount, int outputs) {
	int temp = 1;

	for (int i = 0; i < axonscount; i++) {
		if (temp != Naxon[i].outputLayer) {
			for (int x = 0; x < MaxPLayerC; x++) {
				Nhidden[temp][x].convert(Nhidden[temp][x].type);
			}
			temp = Naxon[i].outputLayer;
		}


		Nhidden[Naxon[i].outputLayer][Naxon[i].output].Fvalue += Nhidden[Naxon[i].inputLayer][Naxon[i].input].value * Naxon[i].weight;
	}
	//std::cout << "ending \n";
	for (int i = 0; i < outputs; i++) {
		Nhidden[Nlayers - 1][i].convert(Nhidden[Nlayers - 1][i].type);
	}
}

void network::SetDETECTORS(std::string testWord) {
	//write custom code
	int length = testWord.length();

	reset();

	for (int i = 0; i < length; i++) {
		char in = testWord[i];
		Nhidden[0][i].value = word.char_to_int(in);
	}

}

void network::mutate(int axons) {
	double temp = (rand() % 100) / 100.0;
	double change;
	if (mutchance.mtChange < 0.05) {
		mutchance.mtChange = 0.3;
	}
	if (mutchance.major < 0.05) {
		mutchance.major = 0.1;
	}
	

	mutchance.mutateStats();

	//Mutate genes
	for (int i = 0; i < axons; i++) {
		temp = (rand() % 100) / 100.0;

		//if random number is less than or equal to mutatechance, start mutation sequence.
		if (temp <= mutchance.mutateChance) {
			//determine if a major or "minor" change shall be made.

			temp = (rand() % 100) / 100.0;
			//major change
			if (temp <= mutchance.major) {
				temp = (rand() % 100) / 100.0;

				if (temp <= mutchance.remove) {
					Naxon[i].weight = 0;
					NGENOME[i] = 0;
				}
				else {
					Naxon[i].weight = -Naxon[i].weight;
					NGENOME[i] = -NGENOME[i];
				}
			}

			//"minor" change
			else {
				temp = (rand() % 100) / 100.0;

				if ((mutchance.large + mutchance.medium + mutchance.small) != 1) {
					std::exit(-2);
				}

				else if (temp <= mutchance.large) {
					change = 0;

					while (change < 0.5) {
						change = (rand() % 100) / 100.0;
					}

					temp = (rand() % 100) / 100.0;
					if (temp <= 0.5) {
						change = -change;
					}

					Naxon[i].weight += change;
					NGENOME[i] += change;
				}

				else if (temp <= mutchance.medium + mutchance.large) {
					change = 0;

					while (change > 0.5 || change < 0.25) {
						change = (rand() % 100) / 100.0;
					}

					temp = (rand() % 100) / 100.0;
					if (temp <= 0.5) {
						change = -change;
					}

					Naxon[i].weight += change;
					NGENOME[i] += change;
				}

				else if (temp <= mutchance.small + mutchance.medium + mutchance.large) {
					change = (rand() % 10) / 100.0;

					temp = (rand() % 100) / 100.0;
					if (temp <= 0.5) {
						change = -change;
					}

					Naxon[i].weight += change;
					NGENOME[i] += change;
				}

				else {
					std::exit(-3);
				}
			}
		}
	}
}

void network::reset() {
	//std::cout << "starting \n";
	for (int i = 0; i < Nlayers; i++) {
		for (int x = 0; x < MaxPLayerC; x++) {
			Nhidden[i][x].Fvalue = 0;
			Nhidden[i][x].value = 0;
		}
	}
}