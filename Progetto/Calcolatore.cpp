#include <iostream>
#include <chrono>
#include <algorithm>
#include <vector>
#include <fstream>
#include "Lambda.h"
#include "Utils.h"
#include "AVLTree.cpp"
#include "BinarySearchTree.cpp"
#include "RedBlackTree.cpp"

#define MAX_VAL 1000000
#define DEBUG_CODE true

using namespace std;
using namespace std::chrono;
typedef duration<long, nanoseconds::period> nanosecondi;

//FUNZIONI:
long getDuration(steady_clock::time_point start, steady_clock::time_point end) {
	return duration_cast<nanosecondi>(end - start).count();
}

long getResolution() {
	steady_clock::time_point start = steady_clock::now(), end;
	do {
		end = steady_clock::now();
	} while (start == end);
	return getDuration(start, end);
}

long getRobustResolution() {
	vector<long> res(1000);
	for (int i = 0; i < 1000; i++)
		res[i] = getResolution();
	std::sort(res.begin(), res.end());
	return res[res.size() / 2];
}

/*
EFFETTO: nanosecondi
*/
long nanosec() { return duration_cast<nanosecondi>(steady_clock::now().time_since_epoch()).count(); }


/*
EFFETTO: Esegue gli inserimeti all'interno dell'albero e 
ritorna il tempo che ci mette a fare l'operazione
*/
long inserimento(AVL::node* avl, int repetitionsCounter, double erroreMassimo);


int main() {

	//Calcolo la granularit�
	long risoluzione = getRobustResolution();
	double erroreMassimo = 0.01;					//1%
	double tMin = risoluzione / erroreMassimo + risoluzione;

	//Vettore
	int* vettore = new int[MAX_VAL] {};

	//Lambda
	AVL::node* avl = AVL::node::create(10, "hello");

	//Tree
	

	//Campionamento
	long minSize = 100;
	long maxSize = MAX_VAL;
	long samples = 100;
	int numeroElementi = 0, prevNumeroElementi = 0;
	int numeroIterazioni = 50;
	int repetitionsCounter = 0;

	//Calcolo dei tempi
	for (int i = 0; i < samples; i++) {
		//Calcolo il numero di elementi
		double base = exp((log(maxSize) - log(minSize)) / (samples - 1));
		repetitionsCounter = (int) ((long) initialRepetition * pow(base, i));
		long coefficiente = minSize;
		prevNumeroElementi = numeroElementi;
		numeroElementi = round(coefficiente * pow(base, i));

		//AVL Tree
        long totalTimeAVL = 0f;
		vector<long> tempMem{};
		for(int iter = 0; iter < numeroIterazioni; iter++){
			//Pulizia dell'albero
			AVL::node::clean(avl);
			//Conto il tempo che ci metto a fare gli iserimenti
			long start = inserimento(avl, repetitionsCounter, erroreMassimo);
			//Somma dei tempo
			totalTimeAVL += start;
			//Salvataggio del tempo per calcolo della varianza
			tempMem.push_back(start);
		}

		//Calcolo del tempo ammortizzato
		long tempoAmmortizzatoAVL = totalTimeAVL / repetitionsCounter;
		long deviazioneAVL = calcolaDeviazione(tempMemAVL, repetitionsCounter);


		//HEAP
		

		//MOM
		

		

		//Stampa
		

	}

	return 0;
}



//IMPLEMENTAZIONE: