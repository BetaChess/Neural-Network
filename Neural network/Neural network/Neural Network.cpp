// Neural network.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <omp.h>


#include "words.h"
#include "Neural classes.h"

words word2;




//TEMPORARY USERINPUT DATA
std::string userSIn;
int userIntIn;
double userDouIn;
bool userBooIn;
char userChIn;

// data stream decalration
std::ifstream fileI;
std::ofstream fileO;

// menu data + navigation
std::string nav;
int CHOSENNETWORK = 0;

//
int OPTIONLOAD = 0;
bool optionload = false;
//

// User/network options, changeable.
std::string SAVEID = ""; // if not set by user or save, this will be chosen automatically/randomly.
std::string * TypesIL;
bool typesILMade = false;
int INPUTS = 15; // may not need to be changed, 10 by default.
int LAYERS = 5; //this does not include input or output, only hidden layers, 1 by default.
int HIDDENPERLAYER = 45; //this should be changed in most cases, 25 by default.
int OUTPUTS = 2; //this may need to be changed, 2 by default.
int AXONS; // this needs more precise calculation, which is not possible without loops and if statements.

network Networks[1000];
network sortingwork[1000];


void SortNetworks(bool deep) {
	if (deep) {
		for (int i = 0; i < 1000; i++) {
			double highest = 0.0;
			int highId = 0;

			for (int x = 0; x < 1000; x++) {
				//måske + istedet for * ?
				if (((/*Networks[x].successrate*1.5 + */Networks[x].fitness / 2000.0) > highest) && (Networks[x].ident != -1)) {
					highest = /*Networks[x].successrate*1.5 + */Networks[x].fitness / 2000.0;
					highId = x;
				}
			}
			for (int x = 0; x < AXONS; x++) {
				sortingwork[i].Naxon[x].weight = Networks[highId].Naxon[x].weight;
				sortingwork[i].NGENOME[x] = Networks[highId].NGENOME[x];
			}

			sortingwork[i].mutchance.large = Networks[highId].mutchance.large;
			sortingwork[i].mutchance.major = Networks[highId].mutchance.major;
			sortingwork[i].mutchance.medium = Networks[highId].mutchance.medium;
			sortingwork[i].mutchance.mtChange = Networks[highId].mutchance.mtChange;
			sortingwork[i].mutchance.mutateChance = Networks[highId].mutchance.mutateChance;
			sortingwork[i].mutchance.remove = Networks[highId].mutchance.remove;
			sortingwork[i].mutchance.reverse = Networks[highId].mutchance.reverse;
			sortingwork[i].mutchance.small = Networks[highId].mutchance.small;

			sortingwork[i].successrate = Networks[highId].successrate;
			sortingwork[i].fitness = Networks[highId].fitness;
			Networks[highId].ident = -1;
		}
	}
	else {
		std::cerr << "ERROR: code not written yet";
		std::exit(6);
	}


	for (int i = 0; i < 1000; i++) {
		Networks[i].successrate = sortingwork[i].successrate;
		Networks[i].fitness = sortingwork[i].fitness;

		for (int x = 0; x < AXONS; x++) {
			Networks[i].Naxon[x].weight = sortingwork[i].Naxon[x].weight;
			Networks[i].NGENOME[x] = sortingwork[i].NGENOME[x];
		}

		Networks[i].mutchance.large = sortingwork[i].mutchance.large;
		Networks[i].mutchance.major = sortingwork[i].mutchance.major;
		Networks[i].mutchance.medium = sortingwork[i].mutchance.medium;
		Networks[i].mutchance.mtChange = sortingwork[i].mutchance.mtChange;
		Networks[i].mutchance.mutateChance = sortingwork[i].mutchance.mutateChance;
		Networks[i].mutchance.remove = sortingwork[i].mutchance.remove;
		Networks[i].mutchance.reverse = sortingwork[i].mutchance.reverse;
		Networks[i].mutchance.small = sortingwork[i].mutchance.small;
	}
	for (int i = 0; i < 1000; i++) {
		Networks[i].ident = 0;
	}
	/*for (int i = 0; i < 1000; i++) {
		Networks[i].FINDFITNESS(OUTPUTS, INPUTS, AXONS);
		std::cout << Networks[i].successrate << "\n";
	}*/
}

void network::FINDFITNESS(int outputs, int inputs, int axons) {
	//write custom code here

	reset();

	successrate = 0;
	fitness = 0;

	int tempo = 0;
	for (int y = 0; y < outputs; y++) {

		for (int x = 0; x < 1000; x++) {
			//std::cout << word2.Lang[y][x];
			SetDETECTORS(word2.Lang[y][x]);
			//std::cout << y << " " << x << "\n";
			Calculate(NAxons, Noutputs);

			double tester = 0;
			int answer = -1;
			for (int i = 0; i < Noutputs; i++) {
				if (Nhidden[Nlayers - 1][i].value > tester) {
					answer = i;
					tester = Nhidden[Nlayers - 1][answer].value;
				}
			}
			if (answer == y) {
				tempo++;
				fitness += Nhidden[Nlayers - 1][answer].value;
			}
			else if (answer != y && answer != -1) {
				fitness -= Nhidden[Nlayers - 1][answer].value;
			}
			else if (answer == -1) {
				//exit(1);
			}
		}
	}

	//std::cout << tempo << " \n";
	successrate = tempo / 2000.0;
}

void breedNet(int in1, int in2) {
	for (int i = 0; i < 2; i++) {
		double temp = (rand() % 100) / 100.0;
		if (temp >= 0.5) {
			Networks[in1 + i + 500].mutchance.mutateChance = Networks[in1].mutchance.mutateChance;
			Networks[in1 + i + 500].mutchance.large = Networks[in1].mutchance.large;
			Networks[in1 + i + 500].mutchance.major = Networks[in1].mutchance.major;
			Networks[in1 + i + 500].mutchance.medium = Networks[in1].mutchance.medium;
			Networks[in1 + i + 500].mutchance.mtChange = Networks[in1].mutchance.mtChange;
			Networks[in1 + i + 500].mutchance.remove = Networks[in1].mutchance.remove;
			Networks[in1 + i + 500].mutchance.reverse = Networks[in1].mutchance.reverse;
			Networks[in1 + i + 500].mutchance.small = Networks[in1].mutchance.small;
		}

		for (int x = 0; x < AXONS; x++) {
			double temp = (rand() % 100)/100.0;

			if (temp >= 0.5) {
				Networks[in1 + i + 500].Naxon[x].weight = Networks[in1].Naxon[x].weight;
			}
			else {
				Networks[in1 + i + 500].Naxon[x].weight = Networks[in2].Naxon[x].weight;
			}
		}
		Networks[in1 + i + 500].successrate = -0.1;
		Networks[in1 + i + 500].fitness = -0.1;
	}
}

void CALCULATEAXONS() {
	AXONS = INPUTS*HIDDENPERLAYER + OUTPUTS*HIDDENPERLAYER;
	if (LAYERS-2 == 1) {
	
	}
	else if (LAYERS-2 == 0) {
		AXONS = INPUTS*OUTPUTS;
	}
	else if( LAYERS-2 > 1) {
		for (int i = 0; i < LAYERS-3; i++) {
			AXONS = (AXONS + HIDDENPERLAYER*HIDDENPERLAYER);
		}
	}
	else {
		std::cerr << "ERROR: negative layers. Really?" << std::endl;
		exit(2);
	}
	std::cout << AXONS << "\n";
}

std::string NameGenerator() {
	std::string temp;
	
	for (int i = 0; i < 5; i++) {
		
		int temp2 = (rand() % 10);
		temp = temp + std::to_string(temp2);
	}
	return temp;
}

void saveall() {
	system(("cmd /c if not exist savedata\\AI\\" + SAVEID + " mkdir savedata\\AI\\" + SAVEID).c_str());
	fileO.open("savedata/AI/" + SAVEID + "/" + SAVEID +" options.dat");
	int count = 0;

	//raw options
	fileO << INPUTS << std::endl;
	fileO << LAYERS << std::endl;
	fileO << HIDDENPERLAYER << std::endl;
	fileO << OUTPUTS << std::endl;

	fileO.close();
	fileO.open("savedata/AI/" + SAVEID + "/" + SAVEID + " L_options.dat");

	//layer options
	for (int i = 0; i < LAYERS; i++) {
		fileO << Networks[0].types[i] << std::endl;
	}
	fileO.close();

	system(("cmd /c if not exist savedata\\AI\\" + SAVEID + "\\" + SAVEID + "_Networks" + " mkdir savedata\\AI\\" + SAVEID + "\\" +SAVEID + "_Networks").c_str());
	//mutation variables
	for (int i = 0; i < 1000; i++) {
		system(("cmd /c if not exist savedata\\AI\\" + SAVEID + "\\" + SAVEID + "_Networks\\" + SAVEID + std::to_string(i) + " mkdir savedata\\AI\\" + SAVEID + "\\" + SAVEID + "_Networks\\" + SAVEID + std::to_string(i)).c_str());

		fileO.open("savedata/AI/" + SAVEID + "/" + SAVEID + "_Networks/" + SAVEID + std::to_string(i) + "/" + SAVEID + "_MUTATION.dat");

		fileO << Networks[i].mutchance.large << std::endl;
		fileO << Networks[i].mutchance.major << std::endl;
		fileO << Networks[i].mutchance.medium << std::endl;
		fileO << Networks[i].mutchance.mtChange << std::endl;
		fileO << Networks[i].mutchance.mutateChance << std::endl;
		fileO << Networks[i].mutchance.remove << std::endl;
		fileO << Networks[i].mutchance.reverse << std::endl;
		fileO << Networks[i].mutchance.small << std::endl;

		fileO.close();
		

		//Genome saving
		fileO.open("savedata/AI/" + SAVEID + "/" + SAVEID + "_Networks/" + SAVEID + std::to_string(i) + "/" + SAVEID + "_GENOME.dat");
		for (int x = 0; x < AXONS; x++) {
			fileO << Networks[i].Naxon[x].weight << std::endl;
			
		}
		if (i % 10 == 0) {
			count++;
			if (count % 10 == 0) {
				std::cout << count << "% done saving .." << std::endl;
			}
		}
		fileO.close();
	}


	
}


int PR; // number of processors

int main()
{
	//set number of processors
	std::cout << "how many processors should the program use? \n";
	std::cin >> PR;
	omp_set_num_threads(PR);

	//set words
	word2.Lang = new std::string*[OUTPUTS];
	for (int i = 0; i < OUTPUTS; i++) {
		word2.Lang[i] = new std::string[1000];
		fileI.open("training_data/output" + std::to_string(i) + ".txt");
		int count2 = 0;
		while (count2 < 1000) {
			//std::getline(FILEI, Lang[i][count2]);
			fileI >> word2.Lang[i][count2];
			count2++;
		}
		fileI.close();
	}
	//ended


	std::cout << "do you want to set a custom seed? (y/n) (seeds have to be intergers) \n";
	std::cin >> userChIn;
	if (userChIn == 'y') {
		std::cin >> userIntIn;
		srand(userIntIn);
	}
	else {
		srand(time(NULL));
	}
	
	std::cout << "load AI? (y/n): " << std::endl;
	std::cin >> userChIn;
	if (userChIn == 'y') {
		nav = "LOADSAVE";
		goto check;
	}
	if (nav == "") {
		goto menu;
	}
main:
	for (int i = 0; i < 7; i++) {
		std::cout << std::endl;
	}
menu:
	// introduction to the commands
	std::cout << "(stop) will terminate the program, will also make a complete save by default. " << std::endl;
	std::cout << "(CN) this allows you to choose a network temporarily. (defaults to 0) " << std::endl;
	std::cout << "(new) creates a completely new AI. " << std::endl;
	std::cout << "(specify) will let you specify the specifics of your network" << std::endl;
	std::cout << "(specifyType) allows you to specify which type of hidden 'neuron', you want on each individual layer." << std::endl;
	std::cout << "(train) trains the network x number of times. Has subcommands for save options." << std::endl;
	std::cout << "(manualT) Manually input data. the command will return each output result. " << std::endl;
	std::cout << "(saveCN) saves the chosen network (uses CN).  " << std::endl;
	std::cout << "(SAVEALL) saves all networks in the current network group. " << std::endl;
	std::cout << "(testCN) tests the chosen network (uses CN). results will be displayed as a success" << std::endl;
	std::cout << "(TESTALL) this will test and sort all networks in a group." << std::endl;
	std::cout << "(loadN) load a single network, will overwrite the chosen network (uses CN)." << std::endl;
	std::cout << "(LOADSAVE) loads a network group, all networks will be overwritten. option to save will be given. " << std::endl;


	// basic instructions:
	std::cout << "Type: " << std::endl;
	std::cin >> nav;

	
check:
	if (nav == "stop") {
		goto end;
	}
	else if (nav == "CN") {
		std::cout << "which network do you want to select? " << std::endl;
		std::cin >> userIntIn;
		CHOSENNETWORK = userIntIn;

		goto main;
	}
	else if (nav == "new") {
		if (!optionload) {
			LAYERS += 2;
			optionload = true;
		}
		CALCULATEAXONS();
		std::cout << "creating arrays \n";
		for (int i = 0; i < 1000; i++) {
			Networks[i].createArrays(INPUTS, LAYERS, HIDDENPERLAYER, OUTPUTS, AXONS, AXONS);
		}
		for (int i = 0; i < 1000; i++) {
			sortingwork[i].createArrays(INPUTS, LAYERS, HIDDENPERLAYER, OUTPUTS, AXONS, AXONS);
		}
		for (int i = 0; i < 1000; i++) {
			Networks[i].Randomize(AXONS);
			Networks[i].SetAxonData(INPUTS, HIDDENPERLAYER, LAYERS, OUTPUTS, AXONS);
		}
		std::cout << "starting initial calculations.  \n";
		if (typesILMade) {}
		else {
			TypesIL = new std::string[LAYERS];
			for (int i = 0; i < LAYERS; i++) {
				TypesIL[i] = "add";
			}
			TypesIL[LAYERS - 1] = "pos_add";
			typesILMade = true;
		}
		for (int i = 0; i < 1000; i++) {
			for (int x = 0; x < LAYERS; x++) {
				Networks[i].types[x] = TypesIL[x];
			}
			Networks[i].SethiddenTYPES(TypesIL);
		}
		Networks[0].Calculate(AXONS, OUTPUTS);
		
		OPTIONLOAD = 1;
		/*for (int i = 0; i < AXONS; i++) {
			std::cout << Networks[0].Naxon[i].input << " _ " << Networks[0].Naxon[i].inputLayer << " _ " << Networks[0].Naxon[i].output << " _ " << Networks[0].Naxon[i].outputLayer << "\n";

		}*/

		goto main;
	}
	else if (nav == "specify") {
		if (OPTIONLOAD >= 1) {
			std::cerr << "ERROR: options can only be changed once per session, please restart to change options. " << std::endl;
			goto main;
		}
		std::cout << "how many inputs should the network have? " << std::endl;
		std::cin >> userIntIn;
		INPUTS = userIntIn;
		std::cout << "how many layers should the network have? (not including input and output)" << std::endl;
		std::cin >> userIntIn;
		LAYERS = userIntIn + 2;
		std::cout << "how many hidden 'neurons' should each layer have?" << std::endl;
		std::cin >> userIntIn;
		HIDDENPERLAYER = userIntIn;
		std::cout << "how many outputs should the network have? (this will determine the data, that will be tested, and also how much)" << std::endl;
		std::cin >> userIntIn;
		OUTPUTS = userIntIn;
		std::cout << "OPTIONS SET" << std::endl;
		optionload = true;

		goto main;
	}
	else if (nav == "specifyType") {
		if (OPTIONLOAD >= 1) {
			std::cerr << "ERROR: already runnning, cannot change settings. \n";
			goto main;
		}
		TypesIL = new std::string[LAYERS];
		typesILMade = true;
		std::cout << "please write one of the following things to make a valid layer. (to0.5, sig, add, pos_add) anything that is not valid will default to 'add'. add will also devide depending on max input on layer. " << std::endl;
		for (int i = 0; i < LAYERS; i++) {
			std::cout << i << std::endl;
			std::cin >> TypesIL[i];
		}
		for (int i = 0; i < 1000; i++) {
			Networks[i].SethiddenTYPES(TypesIL);
		}

		goto main;
	}
	else if (nav == "train") {
		bool saveEve = false;
		int saveEvery = -1;

		std::cout << "do you want to save the AI every few generations? (in case of crash or unexpected shutdown) (y/n) \n";
		std::cin >> userChIn;
		if (userChIn == 'y') {
			std::cout << "do you want to save under a custom name? (y/n) \n";
			std::cin >> userChIn;
			if (userChIn == 'y') {
				std::cout << "Name: " << std::endl;
				std::cin >> SAVEID;
				std::cout << "the AI will be saved as " << SAVEID << std::endl;
			}
			else {
				SAVEID = NameGenerator();
				std::cout << "The AI will be given a random default name, the name given is: " << SAVEID << std::endl;
				std::cin >> nav;
			}

			saveEve = true;
			
			std::cout << "how many generations should pass before the next autosave? \n";
			std::cin >> saveEvery;

			if (saveEvery <= 0) {
				std::cerr << "Error: invalid input";
				std::cin >> nav;
				std::exit(3);
			}
		}

	back1:
		std::cout << "run on time or generations? (t/g) \n";
		std::cin >> userChIn;
		//run on generations
		if (userChIn == 'g') {

			std::cout << "how many generations shall the AI train for? \n";
			std::cin >> userIntIn;


			//training starts here
			time_t time_temp;
			time(&time_temp);

			for (int i = 0; i < userIntIn; i++) {
				time_t time_temp3;
				time(&time_temp3);
				std::cout << "starting iteration " << i + 1 << " out of " << userIntIn << "\n";



#pragma omp parallel for
				for (int i = 0; i < 1000; i++) {
					Networks[i].FINDFITNESS(OUTPUTS, INPUTS, AXONS);
				}

				SortNetworks(true);

				if (i + 1 % saveEvery == 0 && i != 0) {
					saveall();
				}

				for (int i = 0; i < 500; i += 2) {
					breedNet(i, i + 1);
					Networks[i + 500].mutate(AXONS);
					Networks[i + 1 + 500].mutate(AXONS);
				}

				time_t time_temp2;
				time(&time_temp2);
				double seconds = difftime(time_temp2, time_temp3);

				std::cout << "Iteration " << i << " took " << seconds << " seconds to complete, continuing ... \n";
				std::cout << Networks[0].successrate << " _ " << Networks[0].fitness << " \n";
				std::cout << Networks[499].successrate << " _ " << Networks[499].fitness << " \n";
				std::cout << std::endl << std::endl;

			}
			time_t time_temp2;
			time(&time_temp2);
			double seconds = difftime(time_temp2, time_temp);
			std::cout << std::endl << "Training session took " << seconds << " seconds to complete, proceding to menu .." << std::endl << std::endl;
		}

		//run on time
		else if (userChIn == 't') {
			int days;
			int hours;
			int minutes;
			int Final_time;
			std::cout << "how many days shall this run? \n";
			std::cin >> days;
			std::cout << "how many hours shall this run? \n";
			std::cin >> hours;
			std::cout << "how many minutes shall this run? \n";
			std::cin >> minutes;
			std::cout << "how many seconds shall this run? \n";
			std::cin >> Final_time;

			hours += days * 24;
			minutes += hours * 60;
			Final_time += minutes * 60;

			time_t time_temp;
			time(&time_temp);

			double seconds = 0;
			int count = 1;
			while (seconds < Final_time) {
				
				std::cout << "starting iteration " << count << ". \n";

#pragma omp parallel for
				for (int i = 0; i < 1000; i++) {
					Networks[i].FINDFITNESS(OUTPUTS, INPUTS, AXONS);
				}

				SortNetworks(true);

				if (count % saveEvery == 0 && saveEvery != -1) {
					saveall();
				}

				for (int i = 0; i < 500; i += 2) {
					breedNet(i, i + 1);
					Networks[i + 500].mutate(AXONS);
					Networks[i + 1 + 500].mutate(AXONS);
				}
				
				std::cout << Networks[0].successrate << " _ " << Networks[0].fitness << " \n";
				std::cout << Networks[499].successrate << " _ " << Networks[499].fitness << " \n";
				std::cout << std::endl << std::endl;
				count++;

				

				time_t time_temp2;
				time(&time_temp2);
				seconds = difftime(time_temp2, time_temp);
			}
			

		}

		//invalid input
		else {
			std::cerr << "ERROR: invalid input \n ";
			goto back1;
		}
		goto main;
	}
	else if (nav == "manualT") {
		//write custom test function
		std::string testWord;
		std::cin >> testWord;

		Networks[CHOSENNETWORK].SetDETECTORS(testWord);
		Networks[CHOSENNETWORK].Calculate(AXONS, OUTPUTS);

		for (int i = 0; i < OUTPUTS; i++) {
			std::cout << "Output " << i << ": " << Networks[CHOSENNETWORK].Nhidden[LAYERS - 1][i].value << "\n";
		}
		
		goto main;
	}
	else if (nav == "saveCN") {

	} 
	else if (nav == "SAVEALL") {

		if (OPTIONLOAD == 0) {
			std::cerr << "ERROR: nothing to save" << std::endl;
			goto main;
		}

		if (SAVEID == "") {
			std::cout << "do you want to give the AI a custom name? (y/n)" << std::endl;
			std::cin >> userChIn;
			if (userChIn == 'y') {
				std::cout << "Name: " << std::endl;
				std::cin >> SAVEID;
				std::cout << "the AI will be saved as " << SAVEID << std::endl;
			}
			else {
				SAVEID = NameGenerator();
				std::cout << "The AI will be given a random default name, the name given is: " << SAVEID << std::endl;
				std::cin >> nav;
			}
		}

		saveall();

		goto main;
	}
	else if (nav == "testCN") {
		Networks[CHOSENNETWORK].FINDFITNESS(OUTPUTS, INPUTS, AXONS);
		std::cout << Networks[CHOSENNETWORK].successrate << " " << Networks[CHOSENNETWORK].fitness << "\n";
		std::cin >> nav;
		goto main;
	}
	else if (nav == "TESTALL") {
#pragma omp parallel for
		for (int i = 0; i < 1000; i++) {
			//std::cout << i << std::endl;
			Networks[i].FINDFITNESS(OUTPUTS, INPUTS, AXONS);
		}

		SortNetworks(true);

		std::cout << Networks[0].successrate << " _ " << Networks[0].fitness << " \n";
		std::cout << Networks[499].successrate << " _ " << Networks[499].fitness << " \n";
		std::cout << std::endl << std::endl;

		goto main;
	}
	else if (nav == "loadN") {

	}
	else if (nav == "LOADSAVE") {
		if (OPTIONLOAD >= 1) {
			std::cerr << "ERROR: options can only be changed once per session, please restart to change options. " << std::endl;
			goto main;
		}
		else {
			std::cout << "Which AI should be loaded? " << std::endl << "Name: " << std::endl;
			std::cin >> userSIn;
			SAVEID = userSIn;

			fileI.open("savedata/AI/" + SAVEID + "/" + SAVEID + " options.dat");
			if (fileI.fail()) {
				std::cerr << "ERROR: file not found" << std::endl;
				exit(5);
			}

			// Setting up the variables
			fileI >> INPUTS;
			fileI >> LAYERS;
			fileI >> HIDDENPERLAYER;
			fileI >> OUTPUTS;
			CALCULATEAXONS();

			fileI.close();

			//setting up layer data
			fileI.open("savedata/AI/" + SAVEID + "/" + SAVEID + " L_options.dat");
			TypesIL = new std::string[LAYERS];

			for (int i = 0; i < LAYERS; i++) {
				fileI >> TypesIL[i];
			}
			fileI.close();


			//getting the network ready for savefile loading
			for (int i = 0; i < 1000; i++) {
				Networks[i].createArrays(INPUTS, LAYERS, HIDDENPERLAYER, OUTPUTS, AXONS, AXONS);
				Networks[i].SethiddenTYPES(TypesIL);
			}

			for (int i = 0; i < 1000; i++) {
				sortingwork[i].createArrays(INPUTS, LAYERS, HIDDENPERLAYER, OUTPUTS, AXONS, AXONS);
			}

			// Setting the GENOMEs and mutation scores
			int count = 0;
			int nullcount = 0;
			double temp;
			for (int i = 0; i < 1000; i++) {
				fileI.open("savedata/AI/" + SAVEID + "/" + SAVEID + "_Networks/" + SAVEID + std::to_string(i) + "/" + SAVEID + "_GENOME.dat");

				fileI >> Networks[i].mutchance.large;
				fileI >> Networks[i].mutchance.major;
				fileI >> Networks[i].mutchance.medium;
				fileI >> Networks[i].mutchance.mtChange;
				fileI >> Networks[i].mutchance.mutateChance;
				fileI >> Networks[i].mutchance.remove;
				fileI >> Networks[i].mutchance.reverse;
				fileI >> Networks[i].mutchance.small;

				fileI.close();

				if (i % 10 == 0) {
					count++;
					std::cout << count << "% done .." << std::endl;
				}
				fileI.open("savedata/AI/" + SAVEID + "/" + SAVEID + "_Networks/" + SAVEID + std::to_string(i) + "/" + SAVEID + "_GENOME.dat");
				for (int x = 0; x < AXONS; x++) {
					fileI >> temp;
					
					if (temp == NULL && temp != 0) {
						nullcount++;
						std::cerr << temp << " " << "NULL" << " " << nullcount << std::endl;
					}
					Networks[i].NGENOME[x] = temp;
					Networks[i].Naxon[x].weight = temp;
				}
				fileI.close();
			}
			

			fileI.close();

			// setting axons
			for (int i = 0; i < 1000; i++) {
				Networks[i].SetAxonData(INPUTS, HIDDENPERLAYER, LAYERS, OUTPUTS, AXONS);
			}

			OPTIONLOAD = 1;

			goto main;
		}
	}
	else if (nav == "testCODE") {
		
		
		time_t time_temp;
		time(&time_temp);
		std::cout << "starting \n";

#pragma omp parallel for
		for (int i = 0; i < 1000; i++) {
			Networks[i].FINDFITNESS(OUTPUTS, INPUTS, AXONS);
		}
		SortNetworks(true);
		
		for (int i = 0; i < 500; i += 2) {
			breedNet(i, i + 1);
			Networks[i + 500].mutate(AXONS);
			Networks[i + 1 + 500].mutate(AXONS);
		}

		time_t time_temp2;
		time(&time_temp2);
		double seconds = difftime(time_temp2, time_temp);
		
		std::cout << Networks[0].successrate << " _ " << Networks[0].fitness << " \n";
		std::cout << seconds << " done \n";
		std::cin >> nav;
		
	}
	else if (nav == "LEVEL_PLAYING_FIELD") {
		for (int x = 0; x < 1000; x++) {
			for (int i = 0; i < AXONS; i++) {
				Networks[x].Naxon[i].weight = 0;
				Networks[x].NGENOME[i] = 0;
			}
		}
		goto main;
	}
	else if (nav == "fix") {
		for (int i = 0; i < 1000; i++) {
			Networks[i].mutchance.mutateStats();
		}
		goto main;
	}
	else {
		std::cerr << "ERROR: INVALID USERINPUT" << std::endl;
		goto main;
	}

end:
    return 0;
}


