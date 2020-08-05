#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
#include <sstream>
using namespace std;

/*
 *  SPECIFICA:  L'albero AVL è un albero binario di ricerca bilanciato in cui il 
                coefficiente di bilanciamento per ciascun nodo 
                    - vale 1, 
                    - 0 
                    - oppure -1 (nel caso di un albero AVL completo tutti i coefficienti di bilanciamento sono uguali a 0).

 *  PROPRIETA': Viene definito il coefficiente di bilanciamento come la differenza tra le altezze, 
                rispettivamente, del sottoalbero sinistro e del sottoalbero destro di un nodo:
                    - b(n)=h(n.l)-h(n.r)  
 */
class node {
public:
    //Attributi
    int key;
    string val;
    node* father;
    node* left;
    node* right;
    int height;

    //Costruttore del nodo
    node(int key, string val) {
        this->key = key;
        this->val = val;
        this->father = nullptr;
        this->left = nullptr;
        this->right = nullptr;
        this->height = 1;
    }

    ~node() {}

    //Funzioni statiche per la gestione
    static node* create(int key, string val) {
        return new node(key, val);
    }

    /*
    EFFETTO:    Ritorna l'altezza dell'albero
	*/
    static int getHeight(node* root){
        if(root == nullptr) return 0;
        return root->height;
    }

    //Rotazioni
    //Destra
    /*
    EFFETTO:    Esegue la rotazione verso destra
    PRE:        Devono essere presenti dei nodi
                root non deve essere nullptr
    */
    node* destra(node* root)  {  
        if(root == nullptr) return nullptr

        node *x = root->left, T2 = x->right;  
        //Esecuzione della Rotazione
        x->right = root;  root->left = T2;  
        //A questo punto devo aggiornare le atezze  
        root->height = max(height(root->left), height(root->right)) + 1;  
        x->height = max(height(x->left), height(x->right)) + 1;  
        //Alla fine rotorno il nodo che ora diventa root 
        return x;  
    } 

    //Sinistra
    /*
    EFFETTO:    Esegue la rotazione verso sinistra
    PRE:        Devono essere presenti dei nodi
                root non deve essere nullptr
    */
    node* sinistra(node* root)  {  
        if(root == nullptr) return nullptr

        node *y = root->right, T2 = y->left;  
        //Esecuzione della Rotazione
        y->left = root;  root->right = T2;  
        //A questo punto devo aggiornare le atezze  
        root->height = max(height(root->left), height(root->right)) + 1;  
        y->height = max(height(y->left), height(y->right)) + 1;  
        //Alla fine rotorno il nodo che ora diventa root 
        return x;  
    } 

    /*
    EFFETTO:    Ritorna il fattore di bilanciamento
    RETURN:     0 se la root è null opure sono perfettamente bilaniciati
                1 se c'e piu peso a sinista
                - 1 se c'e piu peso a destra
    */
    int valoreBilanciamento(node* root){
        if(root == nullptr) return 0;
        return getHeight(root->left) - getHeight(root->right);
    }
    
};


//Main
int main() {
    //Inizializzazione della RBT
    node* rbt = nullptr;

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

            if (rbt == nullptr)     rbt = node::create(key, val);
            else                    rbt = node::insert(rbt, key, val);

        }

        else if (opzione == "show") {
            node::show(rbt);
            cout << "" << endl;
        }

        else if (opzione == "find") {
            int key = 0;
            s >> key;

            node* res = node::find(rbt, key);
            cout << res->val;
            cout << "" << endl;
        }

        else if (opzione == "remove") {
            int key = 0;
            s >> key;

            rbt = node::remove(rbt, key);
        }

        else if (opzione == "left") {
            int key = 0;
            s >> key;

            node* toRotate = node::find(rbt, key);
            rbt = node::rotateL(rbt, toRotate);
        }
        else if (opzione == "right") {
            int key = 0;
            s >> key;

            node* toRotate = node::find(rbt, key);
            rbt = node::rotateR(rbt, toRotate);
        }

        else if (opzione == "check") {
            cout << ((node::check(rbt))? "GOOD" : "BAD!!!!");
            cout << endl;
        }

        else if(opzione =="exit") { finito = true; }

        opzione = "";
    }
    return 0;
}