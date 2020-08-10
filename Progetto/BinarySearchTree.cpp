#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
#include <sstream>

using namespace std;
namespace BST{
	class node {
	public:
		//Attributi
		int key;
		string val;
		node *left;
		node* right;

		//Costruttore del nodo
		node(int key, const string &val) {
			this->key = key;
			this->val = val;
			this->left = nullptr;
			this->right = nullptr;
		}

		~node() {}

		//Funzioni statiche per la gestione
		static node *create(int key, const string &val) {
			return new node(key, val);
		}

		/*
		EFFETTO:		Inserisce un nuovo nodo
		FUNZIONAMENTO:	key1 <= root < key2
		DESCRIZIONE:	insert k v: inserisce un nuovo nodo nell'albero binario di ricerca, 
						con chiave k di tipo intero e valore v di tipo stringa 
						(si assuma che l'albero non contenga gi� un nodo con chiave k)
		*/
		static void insert(node* root, int key, const string &val) {
			//Destra
			if (root->key < key)
				if (root->right == nullptr) root->right = create(key, val);
				else						insert(root->right, key, val);

			//Sinistra
			else
				if (root->left == nullptr)	root->left = create(key, val);
				else						insert(root->left, key, val);
			
		}

		/*
		EFFETTO:		Cerca una certa chiave all'interno dell'albero
		FUNZIONAMENTO:	key1 <= root < key2
		DESCRIZIONE:	find k: trova nell'albero il nodo con chiave numerica k e restituisce il valore 
						(di tipo stringa) associato a tale nodo (come sopra, si assuma che tale nodo esista)
		*/
		static node* find(node *root, int key) {
			node* iter = root;
			//Ricerco il nodo
			while (iter != nullptr && iter->key != key)
				if (iter->key < key) iter = iter->right;
				else iter = iter->left;

			return iter;
		}

		
        /*
        EFFETTO: Ritorna vero se l'elemento è presente
        */
        static bool contains(node* root, int key){
            if(node::find(root, key) == nullptr) return false;
            return true; 
        }


		/*
		EFFETTO:		Elimita tutto l'albero compresa la root
		FUNZIONAMENTO:	POSTORDER
		DESCRIZIONE:	clear: rimuove tutti i nodi dall'albero, che diventer� quindi vuoto
		*/
		static node* clear(node *root) {
			if (root == nullptr) return nullptr;
			//Elimino la le foglie
			if (root->left == nullptr && root->right == nullptr) {
				delete root;
				return nullptr;
			}
			else {
				//Elimino ricorsivamente i figli
				if (root->left != nullptr) root->left = clear(root->left);
				if (root->right != nullptr) root->right = clear(root->right);
				//Elimino la root
				return clear(root);
				
			}
		}

		/*
		EFFETTO:		esegue una visita nell'albero
		FUNZIONAMENTO:	PREORDER
		DESCRIZIONE:	show: visualizza l'albero corrente
		*/
		static void show(node *root) {
			if (root == nullptr)		cout << "NULL ";
			else {
				cout << root->key << ":" << root->val<<" ";
				show(root->left);
				show(root->right);
			}
		}

		/*
		EFFETTO: Trova il valore minimo nell'albero
		*/
		static node* min(node* root){
			node* iter = root;
			
			//Trova il minimo andando a sinista
			while (iter && iter->left != nullptr)
				iter = iter->left;

			return iter;
		}

		/*
		EFFETTO:		elimina un elemento dall'albero
		FUNZIONAMENTO:	CERCA IL SUCCESSORE
		*/
		static node* remove(node *root, int key) {
			//Caso base
			if (root == nullptr)		return root;
			if (key < root->key)		root->left = remove(root->left, key); 
			else if (key > root->key)	root->right = remove(root->right, key);

			//Hanno lo stesso valore
			else{
				//Nodi con sono un figlio
				if (root->left == nullptr){
					node* temp = root->right;
					delete(root);
					return temp;
				}
				else if (root->right == nullptr){
					node* temp = root->left;
					delete(root);
					return temp;
				}

				//Prendo il piu piccolo elemento del sottoalbero destro
				node* temp = min(root->right);

				//Sposto i valori
				root->key = temp->key;
				root->val = temp->val+"";

				//Rimuovo il successore 
				root->right = remove(root->right, temp->key);
			}
			return root;
		}

	};

	//Function Wrapper
    class Tree : public Lambda{
        public:

        node* root;

		Tree(){
            this->root = nullptr;
        }
        void insert(int key, const string& val) override { 
            if(root == nullptr)     root = node::create(key, val);
            else                    node::insert(root, key, val);
        }

        void clear() override {
            node::clear(this->root);
            this->root = nullptr;
        }

        bool contains(int key) override {
            return node::contains(this->root, key);
        }
    };
}

/*
int main() {
	//Inizializzazione della BST
	node *bst= nullptr;

	//LOOP DELLE OPZIONI
	bool finito = false;
	string line = "", opzione = "";

	while (!finito) {
		//std::cout << "Opzione:>>";
		getline(std::cin, line);
		std::istringstream s(line);
		s >> opzione;
		if (opzione == "exit") { finito = true; }

		else if (opzione == "insert") {
			string val;
			int key = 0;
			s >> key;
			s >> val;

			if (bst == nullptr)     bst = node::create(key, val);
			else                    node::insert(bst, key, val);

			cout << "" << endl;
		}

		else if (opzione == "show") {
			node::show(bst);
			cout << "" << endl;
		}

		else if (opzione == "find") {
			int key = 0;
			s >> key;

			node* res = node::find(bst, key);
			cout << res->val;
			cout << "" << endl;
		}

		else if (opzione == "remove") {
			int key = 0;
			s >> key;

			bst = node::remove(bst, key);
		}

		else { finito = true; }
	}
	return 0;
	node* root = node::create(10, "ten");
	node::insert(root, 5, "five");
	node::insert(root, 2, "two");
	node::insert(root, 100, "h");
	node::insert(root, 23, "tue3");
	node::insert(root, 45, "qc");
	node::insert(root, 200, "2c");
	node::insert(root, 1, "uno");
	node::insert(root, 8, "otto");
	node::show(root);
	cout << endl;

	root = node::remove(root, 10);


	root = node::clear(root);
	node::show(root);
	
}
*/