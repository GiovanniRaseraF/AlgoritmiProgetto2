#include <iostream>
#include <chrono>
#include <algorithm>
#include <vector>
#include <fstream>
#include "Lambda.h"
#include "Prepara.cpp"
#include "AVLTree.cpp"
#include "BinarySearchTree.cpp"
using namespace std;
const string stringaSempre = "l";

int main() {
	AVL::node* avl = AVL::node::create(-1, stringaSempre);


	for (int i = 0; i < 1000000; i++) {
		AVL::node::insert(avl, i, stringaSempre);
	}

	cin.get();
	cin.get();

	AVL::node::clear(avl);
	

	cin.get();
	cin.get();
	return 0;
}