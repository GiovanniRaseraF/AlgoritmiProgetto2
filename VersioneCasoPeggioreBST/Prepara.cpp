#pragma once
#include "Lambda.h"
#include <time.h>
#include <math.h>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <random>

class Prepara : public Lambda {
public:
	int* vettoreOriginale;
	int len;

	Prepara(int lenVettore) {
		this->vettoreOriginale = new int[lenVettore];
		len = lenVettore;
		//int random = dice(generator);

		for (int i = 0; i < lenVettore; i++) {
			//std::cout << seed << " ";
			this->vettoreOriginale[i] = i;
			
		}
	}

	int at(int i){
		return this->vettoreOriginale[i];
	}

	int execute(int* vettore, int start, int finish, int k) {
		for (int i = 0; i < finish + 1; i++) {
			vettore[i] = this->vettoreOriginale[i];
		}
		return 0;
	}

	void riprepara(int lenVettore) {
		//int random = dice(generator);
		for (int i = 0; i < lenVettore; i++) {
			//std::cout << seed << " ";
			this->vettoreOriginale[i] = i;
			
		}
	}
};
