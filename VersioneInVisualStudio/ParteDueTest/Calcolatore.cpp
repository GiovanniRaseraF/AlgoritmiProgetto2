#include <iostream>
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


/*
EFFETTO: Esegue gli inserimeti all'interno dell'albero e
ritorna il tempo che ci mette a fare l'operazione
*/
double inserimento(AVL::node* avl, int repetitionsCounter, double erroreMassimolong, long risoluzione, Prepara* vettore);


double calcolaDeviazione(vector<double> tempi, double, int repetitionsCounter);

int main() {

	//Calcolo la granularit�
	long risoluzione = getRobustResolution();
	double erroreMassimo = 0.01;					//1%
	double tMin = risoluzione / erroreMassimo + risoluzione;

	//Lambda
	Prepara* vettore = new Prepara(MAX_VAL);

	//Tree
	AVL::node* avl = AVL::node::create(10, "hello");

	//Campionamento
	long minSize = 100;
	long maxSize = MAX_VAL;
	long samples = 100;
	int numeroElementi = 0, prevNumeroElementi = 0;
	int initialRepetition = 1000;
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
			AVL::node::clear(avl);
			avl = nullptr;
			//Conto il tempo che ci metto a fare gli iserimenti
			double start = inserimento(avl, numeroElementi, erroreMassimo, risoluzione, vettore);
			//Somma dei tempo
			totalTimeAVL += start;
			//Salvataggio del tempo per calcolo della varianza
			tempMemAVL.push_back(start);
		}

		//Calcolo del tempo ammortizzato
		double tempoAmmortizzatoAVL = (double)totalTimeAVL / (double)numeroIterazioni;
		double deviazioneAVL = calcolaDeviazione(tempMemAVL, tempoAmmortizzatoAVL, numeroElementi);

		cout << numeroElementi << " " << tempoAmmortizzatoAVL << " " << deviazioneAVL << endl;
		//HEAP


		//MOM




		//Stampa


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


double inserimento(AVL::node* avl, int numeroElementi, double erroreMinimo, long risoluzione, Prepara* vettore) {
	long timeS, timeE;
	int c = 0, c1 = 0;
	timeS = nanosec();
	do {
		for (int i = 0; i < numeroElementi; i++) {
			if (avl == nullptr) {
				avl = AVL::node::create(vettore->at(i), "test");
				c1++;
			}
			else if (AVL::node::contains(avl, vettore->at(i))) {
				AVL::node::insert(avl, vettore->at(i), "test");
				c1++;
			}
		}
		timeE = nanosec();
		c++;
	} while (timeE - timeS <= risoluzione * (1.0 / erroreMinimo) + 1.0);
	return ((timeE - timeS) / c) / c1;
}