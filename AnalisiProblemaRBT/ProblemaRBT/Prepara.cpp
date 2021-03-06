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
		int min = -len / 2;
        int max = len / 2;
		std::mt19937 generator;

		// Once per programme, before first use of generator
		generator.seed((unsigned int)std::time(0));

		std::uniform_int_distribution<uint32_t> dice(min, max+1);

		//int random = dice(generator);

		for (int i = 0; i < lenVettore; i++) {
			long seed = dice(generator);
			//std::cout << seed << " ";
			this->vettoreOriginale[i] = seed;
			
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
		int min = -len / 2;
        int max = len / 2;
		std::mt19937 generator;

		// Once per programme, before first use of generator
		generator.seed((unsigned int)std::time(0));

		std::uniform_int_distribution<uint32_t> dice(min, max+1);

		//int random = dice(generator);

		for (int i = 0; i < lenVettore; i++) {
			long seed = dice(generator);
			//std::cout << seed << " ";
			this->vettoreOriginale[i] = seed;
			
		}
	}
};
