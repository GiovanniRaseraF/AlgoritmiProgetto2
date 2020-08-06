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
    static int getheight(node* root){
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
    static node* destra(node* root)  {  
        if(root == nullptr) return nullptr;

        node* x = root->left, *T2 = x->right;  
        //Esecuzione della Rotazione
        x->right = root;  root->left = T2;  
        //A questo punto devo aggiornare le atezze  
        root->height = max(getheight(root->left), getheight(root->right)) + 1;  
        x->height = max(getheight(x->left), getheight(x->right)) + 1;  
        //Alla fine rotorno il nodo che ora diventa root 
        return x;  
    } 

    //Sinistra
    /*
    EFFETTO:    Esegue la rotazione verso sinistra
    PRE:        Devono essere presenti dei nodi
                root non deve essere nullptr
    */
    static node* sinistra(node* root)  {  
        if(root == nullptr) return nullptr;

        node *y = root->right, *T2 = y->left;  
        //Esecuzione della Rotazione
        y->left = root;  root->right = T2;  
        //A questo punto devo aggiornare le atezze  
        root->height = max(getheight(root->left), getheight(root->right)) + 1;  
        y->height = max(getheight(y->left), getheight(y->right)) + 1;  
        //Alla fine rotorno il nodo che ora diventa root 
        return y;  
    } 

    /*
    EFFETTO:    Ritorna il fattore di bilanciamento
    RETURN:     0 se la root è null opure sono perfettamente bilaniciati
                1 se c'e piu peso a sinista
                - 1 se c'e piu peso a destra
    */
    static int valoreBilanciamento(node* root){
        if(root == nullptr) return 0;
        return getheight(root->left) - getheight(root->right);
    }

    /*
    EFFETTO:    Inserimento di un nodo nell'albero

    */
    static node* insert(node* root, int key, string val){
        //Caso Base
        if (root == nullptr)  return create(key, val);  
        //Vaso di andare verso sinistra o verso desta
        if (key < root->key)        root->left = insert(root->left, key, val);  
        else if (key > root->key)   root->right = insert(root->right, key, val);
        //Caso impossibile  
        else return root;  
  
        //Aggionamento delle altezze
        root->height = 1 + max(getheight(root->left),  getheight(root->right));  
        int bilanciamento = valoreBilanciamento(root);  
  
        //A questo punto devo ribilanciare l'albero

        // ho piu nodi a sinistra  
        if (bilanciamento > 1 && key < root->left->key)    return destra(root);  
        // ho piu nodi a destra  
        if (bilanciamento < -1 && key > root->right->key)  return sinistra(root);  
        //Ribilanciamento ricorsivo
        if (bilanciamento > 1 && key > root->left->key)  {  
            root->left = sinistra(root->left);  
            return destra(root);  
        }    
        if (bilanciamento < -1 && key < root->right->key)  {  
            root->right = destra(root->right);  
            return sinistra(root);  
        } 
        //Ritorno il nodo
        return root;  
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
        while (iter->key != key)
            if (iter->key < key) iter = iter->right;
            else iter = iter->left;

        return iter;
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
			delete(root);
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
			cout << root->key << ":" << root->val<<":"<<root->height<<" ";
			show(root->left);
			show(root->right);
		}
	}
  
    static node* remove(node* root, int key)  {  
        //Caso Base
        if (root == nullptr)  return root;  
        //Mi sposo ricorsivamente verso il basso
        if ( key < root->key )      root->left = remove(root->left, key);  
        else if( key > root->key )  root->right = remove(root->right, key);  
        else{  
            //Controllo se sono un figlio unico
            if( (root->left == nullptr) || (root->right == nullptr) )  {  
                node* temp = root->left ?  root->left : root->right;  
                if (temp == nullptr)  {  
                    temp = root;  
                    root = nullptr;  
                }  
                else  *root = *temp;
                //Eliminazione del nodo  
                delete(temp);  
            }  else{   
                node* temp = minValueNode(root->right);  
                //Copio i dati
                root->key = temp->key;
                root->val = temp->val;  

                root->right = remove(root->right,  temp->key);  
            }  
        }  
    
        if (root == NULL)  return root;  
        //Aggiornamento delle altezze
        root->height = 1 + max(getheight(root->left),  getheight(root->right));  
        //Sistemo il bilanciamento
        int bilanciamento = valoreBilanciamento(root);  
        // Caso sinistro
        if (bilanciamento > 1 &&  valoreBilanciamento(root->left) >= 0)  return destra(root);  
        if (bilanciamento > 1 &&  valoreBilanciamento(root->left) < 0)  {  
            root->left = sinistra(root->left);  
            return destra(root);  
        }  
        if (bilanciamento < -1 &&  valoreBilanciamento(root->right) <= 0)  return sinista(root);    
        if (bilanciamento < -1 &&  valoreBilanciamento(root->right) > 0)  {  
            root->right = destra(root->right);  
            return sinistra(root);  
        }  
    
        return root;  
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
            string val{};
            int key = 0;
            s >> key;
            s >> val;

            if (rbt == nullptr)     rbt = node::create(key, val);
            else rbt = node::insert(rbt, key, val);

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

        else if(opzione =="exit") { finito = true; }

        opzione = "";
    }
    return 0;
}