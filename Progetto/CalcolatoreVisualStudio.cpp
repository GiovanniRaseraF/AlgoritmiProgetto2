#include <iostream>
#include <chrono>
#include <algorithm>
#include <vector>
#include <fstream>
#include "Lambda.h"
#include "Prepara.cpp"
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
const string stringaSempre = "t";

/*
EFFETTO: Esegue gli inserimeti all'interno dell'albero e
ritorna il tempo che ci mette a fare l'operazione
*/
double inserimento(Lambda* tree, double Tmin, int numeroElementi, Prepara* vettore);
double* calcolatore(Lambda* tree, double tMin, int numeroElementi, Prepara* vettore);
double calcolaDeviazione(vector<double> tempi, double, int repetitionsCounter);

int main() {

	//Calcolo la granularit�
	long risoluzione = getRobustResolution();
	double erroreMassimo = 0.01;					//1%
	double tMin = risoluzione / erroreMassimo + risoluzione;

	//Lambda
	Prepara* vettore = new Prepara(MAX_VAL);

	//Tree
	AVL::Tree* avl = new AVL::Tree();
	BST::Tree* bst = new BST::Tree();
	RBT::Tree* rbt = new RBT::Tree();


	//Campionamento
	long minSize = 1000;
	long maxSize = MAX_VAL;
	long samples = 100;
	int numeroElementi = 0, prevNumeroElementi = 0;
	

	//Calcolo dei tempi
	for (int i = 0; i < samples; i++) {
		//Calcolo il numero di elementi
		double base = exp((log(maxSize) - log(minSize)) / (samples - 1));
		long coefficiente = minSize;
		prevNumeroElementi = numeroElementi;
		numeroElementi = round(coefficiente * pow(base, i));

		//AVL Tree
		double *AVLres = calcolatore(avl, tMin, numeroElementi, vettore);
		//Calcolo del tempo ammortizzato
		double tempoAmmortizzatoAVL = AVLres[0];
		double deviazioneAVL = AVLres[1];

	
		//BS Tree
		//RB Tree

		//Stampa
		cout << numeroElementi << " " << tempoAmmortizzatoAVL << " " << deviazioneAVL << endl;
		vettore->riprepara(numeroElementi);
	}

	return 0;
}



//IMPLEMENTAZIONE:

double calcolaDeviazione(vector<double> tempi, double tempoammortizzato, int repetitionsCounter) {
	double deviazione = 0;
	for (double time : tempi) deviazione += pow(time - tempoammortizzato, 2);
	return (sqrt(deviazione / repetitionsCounter));
}

double* calcolatore(Lambda* tree, double tMin, int numeroElementi, Prepara* vettore){
	int numeroIterazioni = 50;
	long totalTime = 0;
		vector<double> tempMem;
		for (int iter = 0; iter < numeroIterazioni; iter++) {
			//Pulizia dell'albero
			tree->clear();
			//Conto il tempo che ci metto a fare gli iserimenti
			double start = inserimento(tree, tMin, numeroElementi, vettore);
			//Somma dei tempo
			totalTime += start;
			//Salvataggio del tempo per calcolo della varianza
			tempMem.push_back(start);
		}

		//Calcolo del tempo ammortizzato
		double tempoAmmortizzato = (double)totalTime / numeroIterazioni;
		double deviazione = calcolaDeviazione(tempMem, tempoAmmortizzato, numeroElementi);
		return new double[2]{tempoAmmortizzato, deviazione};
}

double inserimento(Lambda* tree, double tMin, int numeroElementi, Prepara* vettore) {
	long timeS, timeE;
	int c = 0, c1 = 0;
	timeS = nanosec();

	do {
		for (int i = 0; i < numeroElementi; i++) {
			if (!tree->contains(vettore->at(i))) {
				tree->insert(vettore->at(i), stringaSempre);
				c1++;
			}
		}
		timeE = nanosec();
		c++;
	} while (timeE - timeS <= tMin);

	return ((timeE - timeS) / c) / c1;
}