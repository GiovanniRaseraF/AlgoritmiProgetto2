#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
#include <sstream>
#include "Lambda.h"
#include <vector>

using namespace std;
namespace RBT{
    enum color {
        RED, BLACK
    };
    typedef enum color Color;
    

    enum  class typeOfchild {
        ROOT, LEFT, RIGHT
    };
    typedef enum  typeOfchild typeChild;


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

    class node {
    public:
        //Attributi
        int key;
        string val;
        node* father;
        node* left;
        node* right;
        bool color;

        //Costruttore del nodo
        node(int key, const string& val) {
            this->key = key;
            this->val = val;
            this->father = nullptr;
            this->left = nullptr;
            this->right = nullptr;
            this->color = Color::BLACK;
        }

        ~node() {}

        //Funzioni statiche per la gestione
        static node* create(int key, const string& val) {
            return new node(key, val);
        }

        /*
		EFFETTO:		Elimita tutto l'albero compresa la root
		FUNZIONAMENTO:	POSTORDER
		DESCRIZIONE:	clear: rimuove tutti i nodi dall'albero, che diventer� quindi vuoto
		*/
        static node* clear(node*& root) {
            if (root == nullptr) return nullptr;
            //Elimino la le foglie
            if (root->left == nullptr && root->right == nullptr) {
                delete root;
                root = nullptr;
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
        EFFETTO:        Trova il valore minimo nell'albero
        */
        static node* min(node*& root) {
            node* iter = root;

            //Trova il minimo andando a sinista
            while (iter && iter->left != nullptr)
                iter = iter->left;

            return iter;
        }

        /*
        EFFETTO:		Inserisce un nuovo nodo
        FUNZIONAMENTO:	key1 <= root < key2
        DESCRIZIONE:	insert k v: inserisce un nuovo nodo nell'albero binario di ricerca,
                        con chiave k di tipo intero e valore v di tipo stringa
                        (si assuma che l'albero non contenga già un nodo con chiave k)
        */
        static node* insertBST(node*& root, int key, const string& val) {
            //Destra
            if (root->key < key)
                if (root->right == nullptr) {
                    root->right = create(key, val);
                    root->right->father = root;
                    return root->right;
                }
                else		    return insertBST(root->right, key, val);

            //Sinistra
            else
                if (root->left == nullptr) {
                    root->left = create(key, val);
                    root->left->father = root;
                    return root->left;
                }
                else            return insertBST(root->left, key, val);
        }

        //Operazioni Importanti


        /*
        EFFETTO:        Rotazione verso destra
        */
        static node* rotateR(node*& T, node*& X) {
            node* fakeFather = create(0, "");
            //Controllo se sono nella root
            if (T == X) {
                X->father = fakeFather;
                fakeFather->left = X;
            }

            //Normale esecuzione
            node* xFather = X->father;
            node* xLeft = X->left;
            bool isXLeftChild = (xFather->left) == X;

            if (isXLeftChild) {
                //metto y al posto di x
                xFather->left = xLeft;
                xLeft->father = xFather;
            }
            else {
                //metto y al posto di x
                xFather->right = xLeft;
                xLeft->father = xFather;
            }

            //Metto apposto il figlio di y come figlio sinistro di x
            X->left = xLeft->right;
            if (xLeft->right != nullptr) xLeft->right->father = X;
            //Attacco x come figlio destro di y
            xLeft->right = X;
            X->father = xLeft;

            //Ritorno la nuova root
            if (T == X) {
                delete(fakeFather);
                xLeft->father = nullptr;
                return xLeft;
            }

            return T;
        }

        /*
        EFFETTO:        Rotazione verso sinistra
        */
        static node *rotateL(node*& T, node*& X) {
            node* fakeFather = create(0, "");
            //Controllo se sono nella root
            if (T == X) {
                X->father = fakeFather;
                fakeFather->left = X;
            }

            //Normale esecuzione
            node* xFather = X->father;
            node* xRight = X->right;
            bool isXLeftChild = (xFather->left) == X;

            if (isXLeftChild) {
                //metto y al posto di x
                xFather->left = xRight;
                xRight->father = xFather;
            }
            else {
                //metto y al posto di x
                xFather->right = xRight;
                xRight->father = xFather;
            }

            //Metto apposto il figlio di y come figlio sinistro di x
            
            X->right = xRight->left;
            if(xRight->left != nullptr) xRight->left->father = X;
            //Attacco x come figlio destro di y
            xRight->left = X;
            X->father = xRight;

            //Ritorno la nuova root
            if (T == X) {
                delete(fakeFather);
                xRight->father = nullptr;
                return xRight;
            }

            return T;
        }

        /*
        EFFETTO:        Mi dice il colore di n, se n è una foglia di dice che è black
        */
        static bool getColor(node* n) { return (n == nullptr ? Color::BLACK : n->color); }

        /*
        EFFETTO:        Mi dice se il n è la root oppure figlio destro o sinistro
        */
        static typeChild childPosition(node*& n) {
            if (n->father == nullptr) return typeChild::ROOT;
            return (n->father->left == n) ? typeChild::LEFT : typeChild::RIGHT;
        }

        /*
        EFFETTO:        Ritorna lo zio di dell nodo scielto
        */
        static node* uncle(node*& n) {
            node *father = n->father;
            if (node::childPosition(father) == typeChild::LEFT)
                return father->father->right;
            else
                return father->father->left;
        }

        /*
        EFFETTO:        Ritorna il nonno del nodo
        */
        static node* grandfather(node*& n) {
            return n->father->father;
        }
    
        /*
        EFFETTO:        Elimina un elemento dall'albero
        FUNZIONAMENTO:  
        
        */
        static node* remove(node* root, int key) {
            return nullptr;
        }

        /*
        EFFETTO:        Inserisce un nuovo nodo
        FUNZIONAMENTO:  1 - La chiave k è in un nodo x che ha due figli null
                        2 - Inserisco x in T utilizzando le procedure dei BST
                        3 - Si colora di RED cosi sicuramente le altezze nere sono corrette
                        4 - Se x.parent è RED si usato rotazione e ricolorazione per sistemare il problema verso la radice
                        5 - In ogni istante può succedere solo che ho un RED con figlio RED
        */
        static node *insert(node*& root, int key, const string& val) {
        
            //Inserimento normale
            node *inserted = node::insertBST(root, key, val);
            inserted->color = Color::RED;
            
            while (true) {
                //Caso Base
                if (node::getColor(inserted->father) == Color::BLACK) return root;

                //Scegli caso
                node* u = node::uncle(inserted);
                node* g = node::grandfather(inserted);
                node* p = inserted->father;

                if (node::getColor(u) == Color::BLACK && (node::childPosition(inserted) == node::childPosition(p))) {
                    if (node::childPosition(inserted) == typeChild::LEFT)
                        root = rotateR(root, g);
                    else
                        root = rotateL(root, g);

                    p->color = Color::BLACK;
                    g->color = Color::RED;
                    return root;
                }
                else if (node::getColor(u) == Color::BLACK && (node::childPosition(inserted) != node::childPosition(p))) {
                    if (node::childPosition(inserted) == typeChild::RIGHT) {
                        root = rotateL(root, p);
                        inserted = inserted->left;
                    }
                    else {
                        root = rotateR(root, p);
                        inserted = inserted->right;
                    }
                }
                else {
                    p->color = Color::BLACK;
                    u->color = Color::BLACK;
                    g->color = Color::RED;
                    inserted = g;
                    if(root == inserted) g->color = Color::BLACK;
                }
            }
            return root;

        }

        /*
        EFFETTO:        Ritorna true se l'ambero BST ha tutti i puntatori giusti
        */
        static bool checkBST(node* root) {
            if (root == nullptr) return true;

            //Controllo che i puntatori sia giusti
            if (root->left != nullptr) {
                if (root->left->father == root) return true && check(root->left);
                else return false;
            }

            if (root->right != nullptr) {
                if (root->right->father == root) return true && check(root->right);
                else return false;
            }
            return true;
        }

        /*
        EFFETTO:        Ritorna true se l'ambero RBT ha tutti i puntatori giusti
                        e tutti i colori giusti
        */
        static bool check(node *root) {
            if (root == nullptr) return true;
            
            bool rootC = root->color;
            bool res = true;
            if (rootC == Color::RED) {
                //NON deve esserci red figlio di red
                if (root->left != nullptr) {
                    if (root->left->father == root && root->left->color == Color::BLACK) res = true && check(root->left);
                    else return false;
                }

                if (root->right != nullptr) {
                    if (root->right->father == root && root->right->color == Color::BLACK) res =  true && check(root->right);
                    else return false;
                }
            }else{
                if (root->left != nullptr) {
                    if (root->left->father == root) res =  true && check(root->left);
                    else return false;
                }

                if (root->right != nullptr) {
                    if (root->right->father == root)  res = true && check(root->right);
                    else return false;
                }
            }

            return res;
        }
    };


    //Function Wrapper
    class Tree : public Lambda {
    public:
        node* root;

        Tree() {
            this->root = nullptr;
        }

        void insert(int key, const string& val) override {
            if (root == nullptr)     root = node::create(key, val);
            else                    root = node::insert(root, key, val);
        }

        void clear() override {
            node::clear(this->root);
            this->root = nullptr;
        }
    };
}
