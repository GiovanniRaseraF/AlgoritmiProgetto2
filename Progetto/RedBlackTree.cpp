
#include <iostream>
#include <sstream>
#include <string>
#include "Lambda.h"
using namespace std;
namespace RBT {
    enum Color { RED, BLACK };

    class node {
    public:
        int key;
        string val;
        bool color;
        node* left, * right, * father;


        // Constructor 
        node(int key, const string& val) {
            this->key = key;
            this->val = val;
            left = right = father = nullptr;
            this->color = RED;
        }

        ~node() {}
    };

    /*
    *  SPECIFICA:  Un RBT è un BST in cui ogni nodo x ha un'informazione
                    aggiuntiva x.color e devono valere:
                        1 - Il colore deve essere R o B
                        2 - Ogni figlio NULL è B
                        3 - Ogni nodo R ha figli B
                        4 - In ogni nodo x, il numero di nodi B nel cammino x-foglia è sempre lo stesso
                        5 - La radice è B

    * PROPRIETA':  - Se sciendo nei nodi non è detto che l'altezzanera cali
                    - Per ogni nodo x il piu lungo cammino x-foglia è lungo al massimo 2 * BH(x) quindi H(x) <= 2 * BH(x)
                    - Togliando tutti i nodi rossi, resta almeno un albero binario completo di BH(T) fatto solo da nodi neri 
                        -> Quindi N > 2^(BH(t)) - 1
                        -> (  H(T) <= 2 * BH(T)  &&   N > 2^(BH(T)) - 1)      ->        BH(T) >= H(T) / 2
                        -> H(T) <= 2 * log2(N + 1)

    * TEOREMI:     - Se T è un RBT allora H = Teta(lg(N))
    */

    class TreeRBT  {
    public:
        node* root;
        void rotateL(node*&, node*&);
        void rotateR(node*&, node*&);
        void insertFix(node*&, node*&);
        void insert(const int& n, const string& val);
        // Constructor 
        TreeRBT() { root = nullptr; }
    };


     /*
    EFFETTO:		Inserisce un nuovo nodo
    FUNZIONAMENTO:	key1 <= root < key2
    DESCRIZIONE:	insert k v: inserisce un nuovo nodo nell'albero binario di ricerca,
                    con chiave k di tipo intero e valore v di tipo stringa
                    (si assuma che l'albero non contenga già un nodo con chiave k)
    */
    node* insertBST(node* root, node* puntatore) {
        if (root == nullptr) return puntatore;
        if (puntatore->key < root->key) {
            root->left = insertBST(root->left, puntatore);
            root->left->father = root;
        }
        else if (puntatore->key > root->key) {
            root->right = insertBST(root->right, puntatore);
            root->right->father = root;
        }
        return root;
    }

    //Operazioni Importanti

    /*
    EFFETTO:        Rotazione verso sinistra
    */
    void TreeRBT::rotateL(node*& root, node*& puntatore) {
        node* fakeR = puntatore->right;
        puntatore->right = fakeR->left;

        if (puntatore->right != nullptr)    puntatore->right->father = puntatore;
        fakeR->father = puntatore->father;

        if (puntatore->father == nullptr)   root = fakeR;
        else if (puntatore == puntatore->father->left)  puntatore->father->left = fakeR;
        else
            puntatore->father->right = fakeR;

        fakeR->left = puntatore;
        puntatore->father = fakeR;
    }

    /*
    EFFETTO:        Rotazione verso destra
    */
    void TreeRBT::rotateR(node*& root, node*& puntatore) {
        node* fakeL = puntatore->left;
        puntatore->left = fakeL->right;

        if (puntatore->left != nullptr) puntatore->left->father = puntatore;
        fakeL->father = puntatore->father;

        if (puntatore->father == nullptr)   root = fakeL;
        else if (puntatore == puntatore->father->left)   puntatore->father->left = fakeL;
        else
            puntatore->father->right = fakeL;

        fakeL->right = puntatore;
        puntatore->father = fakeL;
    }

    /*
    EFFETTO:        Inserisce un nuovo nodo
    FUNZIONAMENTO:  1 - La chiave k è in un nodo x che ha due figli null
                    2 - Inserisco x in T utilizzando le procedure dei BST
                    3 - Si colora di RED cosi sicuramente le altezze nere sono corrette
                    4 - Se x.parent è RED si usato rotazione e ricolorazione per sistemare il problema verso la radice
                    5 - In ogni istante può succedere solo che ho un RED con figlio RED
    */
    void TreeRBT::insertFix(node*& root, node*& pt) {
        node* fakeFather = nullptr;
        node* fakeGrandFather = nullptr;

        while ((pt != root) && (pt->color != BLACK) && (pt->father->color == RED)){
            fakeFather = pt->father;
            fakeGrandFather = pt->father->father;
            //Caso uno
            if (fakeFather == fakeGrandFather->left){
                node* uncle_pt = fakeGrandFather->right;
                if (uncle_pt != nullptr && uncle_pt->color == RED){
                    fakeGrandFather->color = RED;
                    fakeFather->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = fakeGrandFather;
                }else{
                    if (pt == fakeFather->right){
                        rotateL(root, fakeFather);
                        pt = fakeFather;
                        fakeFather = pt->father;
                    }
                    rotateR(root, fakeGrandFather);
                    swap(fakeFather->color, fakeGrandFather->color);
                    pt = fakeFather;
                }
            //Caso due
            }else{
                node* uncle_pt = fakeGrandFather->left;
                if ((uncle_pt != nullptr) && (uncle_pt->color == RED)){
                    fakeGrandFather->color = RED;
                    fakeFather->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = fakeGrandFather;
                }else{
                    if (pt == fakeFather->left){
                        rotateR(root, fakeFather);
                        pt = fakeFather;
                        fakeFather = pt->father;
                    }
                    rotateL(root, fakeGrandFather);
                    swap(fakeFather->color, fakeGrandFather->color);
                    pt = fakeFather;
                }
            }
        }
        root->color = BLACK;
    }

    /*
    EFFETTO: Inserisce un elemento nell'albero
    */
    void TreeRBT::insert(const int& key, const string& val) {
        node* pt = new node(key, val);
        root = insertBST(root, pt);s 
        insertFix(root, pt);
    }


     /*
    EFFETTO:        Elimita tutto l'albero compresa la root
    FUNZIONAMENTO:  POSTORDER
    DESCRIZIONE:    clear: rimuove tutti i nodi dall'albero, che diventer quindi vuoto
    */
    static node* clear(node* root) {
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
    EFFETTO:		Cerca una certa chiave all'interno dell'albero
    FUNZIONAMENTO:	key1 <= root < key2
    DESCRIZIONE:	find k: trova nell'albero il nodo con chiave numerica k e restituisce il valore
                    (di tipo stringa) associato a tale nodo (come sopra, si assuma che tale nodo esista)
    */
    static node* find(node*& root, int key) {
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
    static bool contains(node*& root, int key) {
        if (RBT::find(root, key) == nullptr) return false;
        return true;
    }



    /*
    EFFETTO:        Ritorna true se l'ambero RBT ha tutti i puntatori giusti
                    e tutti i colori giusti
    */
    static bool check(node*& root) {
        if (root == nullptr) return true;

        bool res = true;
        if (root->color == Color::RED) {
            //NON deve esserci red figlio di red
            if (root->left != nullptr) {
                if (root->left->father == root && root->left->color == Color::BLACK) res = true && check(root->left);
                else return false;
            }

            if (root->right != nullptr) {
                if (root->right->father == root && root->right->color == Color::BLACK) res = true && check(root->right);
                else return false;
            }
        }
        else {
            if (root->left != nullptr) {
                if (root->left->father == root) res = true && check(root->left);
                else return false;
            }

            if (root->right != nullptr) {
                if (root->right->father == root)  res = true && check(root->right);
                else return false;
            }
        }

        return res;
    }

    /*
    EFFETTO:        esegue una visita nell'albero
    FUNZIONAMENTO:  PREORDER
    DESCRIZIONE:    show: visualizza l'albero corrente
    */
    static void show(node* root) {
        if (root == nullptr)            cout << "NULL ";
        else {
            string col;
            if (root->color == 0) col = "RED";
            else col = "BLACK";
            cout << root->key << ":" << root->val << ":" << col << " ";
            show(root->left);
            show(root->right);
        }
    }

    //Function Wrapper
    class Tree : public Lambda {
    public:
        TreeRBT root;

        Tree() {}

        void insert(int key, const string& val) override {
            root.insert(key, val);
        }

        void clear() override {
            root.root = RBT::clear(root.root);
        }

        bool contains(int key) override {
            return RBT::contains(root.root, key);
        }
    };
}
    

/*

int main() {
    //Inizializzazione della BST
    Tree bst;

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

            bst.insert(key, val);
      
            cout << "" << endl;
        }

        else if (opzione == "show") {
            show(bst.root);
            cout << "" << endl;
        }

        else if (opzione == "find") {
            int key = 0;
            s >> key;

            node* res = find(bst.root, key);
            cout << res->val;
            cout << "" << endl;
        }


        else { finito = true; }
    }
    return 0;
}
