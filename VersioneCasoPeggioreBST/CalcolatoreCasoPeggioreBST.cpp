﻿#include <iostream>
#include <chrono>
#include <algorithm>
#include <vector>
#include <fstream>
#include "Lambda.h"
#include "Prepara.cpp"
#include "AVLTree.cpp"
#include "BinarySearchTree.cpp"

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


const string stringaSempre = "t";
/*
EFFETTO: Esegue gli inserimeti all'interno dell'albero e
ritorna il tempo che ci mette a fare l'operazione
*/
double inserimento(AVL::node*& avl, int repetitionsCounter, double erroreMassimolong, long risoluzione, Prepara* vettore);
double inserimento(BST::node*& bst, int numeroElementi, double erroreMinimo, long risoluzione, Prepara* vettore);

double calcolaDeviazione(vector<double> tempi, double, int repetitionsCounter);

int main() {

	//Calcolo la granularit�
	long risoluzione = getRobustResolution();
	double erroreMassimo = 0.01;					//1%
	double tMin = risoluzione / erroreMassimo + risoluzione;

	//Lambda
	Prepara* vettore = new Prepara(MAX_VAL);

	
	//Tree
	AVL::node* avl = AVL::node::create(10, stringaSempre);
	BST::node* bst = BST::node::create(10, stringaSempre);

	//Campionamento
	long minSize = 1000;
	long maxSize = MAX_VAL;
	long samples = 50;
	int numeroElementi = 0, prevNumeroElementi = 0;
	int numeroIterazioni = 50;

	//Calcolo dei tempi
	for (int i = 0; i < samples; i++) {
		//Calcolo il numero di elementi
		double base = exp((log(maxSize) - log(minSize)) / (samples - 1));
		long coefficiente = minSize;
		prevNumeroElementi = numeroElementi;
		numeroElementi = round(coefficiente * pow(base, i));

		//AVL Tree
		long totalTimeAVL = 0;
		vector<double> tempMemAVL{};
		for (int iter = 0; iter < numeroIterazioni; iter++) {
			//Pulizia dell'albero
			avl = AVL::node::clear(avl);
			avl = nullptr;
			//Conto il tempo che ci metto a fare gli iserimenti
			double start = inserimento(avl, numeroElementi, erroreMassimo, risoluzione, vettore);
			//Somma dei tempo
			totalTimeAVL += start;
			//Salvataggio del tempo per calcolo della varianza
			tempMemAVL.push_back(start);
		}

		//Calcolo del tempo ammortizzato
		double tempoAmmortizzatoAVL = (double)totalTimeAVL / numeroIterazioni;
		double deviazioneAVL = calcolaDeviazione(tempMemAVL, tempoAmmortizzatoAVL, numeroElementi);

		
		
		
		//BS Tree
		long totalTimeBST = 0;
		vector<double> tempMemBST{};
		for (int iter = 0; iter < numeroIterazioni; iter++) {
			//Pulizia dell'albero
			bst = BST::node::clear(bst);
			bst = nullptr;
			//Conto il tempo che ci metto a fare gli iserimenti
			double start = inserimento(bst, numeroElementi, erroreMassimo, risoluzione, vettore);
			//Somma dei tempo
			totalTimeBST += start;
			//Salvataggio del tempo per calcolo della varianza
			tempMemBST.push_back(start);
		}

		//Calcolo del tempo ammortizzato
		double tempoAmmortizzatoBST = (double)totalTimeBST / numeroIterazioni;
		double deviazioneBST = calcolaDeviazione(tempMemAVL, tempoAmmortizzatoBST, numeroElementi);
		
		//RB Tree




		vettore->riprepara(numeroElementi);
		//Stampa
		cout << numeroElementi << " " << tempoAmmortizzatoAVL << " " << deviazioneAVL << " " << tempoAmmortizzatoBST << " " << deviazioneBST << endl;
		cerr << numeroElementi << " " << tempoAmmortizzatoAVL << " " << deviazioneAVL << " " << tempoAmmortizzatoBST << " " << deviazioneBST << endl;
	}

	return 0;
}



//IMPLEMENTAZIONE:

double calcolaDeviazione(vector<double> tempi, double tempoammortizzato, int repetitionsCounter) {
	double deviazione = 0;
	for (double time : tempi) {
		deviazione += pow(time - tempoammortizzato, 2);
	}

	return (sqrt(deviazione / repetitionsCounter));
}


double inserimento(AVL::node*& avl, int numeroElementi, double erroreMinimo, long risoluzione, Prepara* vettore) {
	long timeS, timeE;
	int c = 0, c1 = 0;
	timeS = nanosec();
	do {
		for (int i = 0; i < numeroElementi; i++) {
			if (avl == nullptr) {
				avl = AVL::node::create(vettore->at(i), stringaSempre);
				c1++;
			}
			else if (!AVL::node::contains(avl, vettore->at(i))) {
				avl = AVL::node::insert(avl, vettore->at(i), stringaSempre);
				c1++;
			}
		}
		timeE = nanosec();
		c++;
	} while (timeE - timeS <= risoluzione * (1.0 / erroreMinimo) + 1.0);
	return ((timeE - timeS) / c) / c1;
}


double inserimento(BST::node*& bst, int numeroElementi, double erroreMinimo, long risoluzione, Prepara* vettore) {
	long timeS, timeE;
	int c = 0, c1 = 0;
	timeS = nanosec();
	do {
		for (int i = 0; i < numeroElementi; i++) {
			if (bst == nullptr) {
				bst = BST::node::create(vettore->at(i), stringaSempre);
				c1++;
			}
			else if (!BST::node::contains(bst, vettore->at(i))) {
				BST::node::insert(bst, vettore->at(i), stringaSempre);
				c1++;
			}
		}
		timeE = nanosec();
		c++;
	} while (timeE - timeS <= risoluzione * (1.0 / erroreMinimo) + 1.0);
	return ((timeE - timeS) / c) / c1;
}