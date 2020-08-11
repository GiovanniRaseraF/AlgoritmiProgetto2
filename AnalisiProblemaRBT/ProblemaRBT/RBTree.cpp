
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

    void TreeRBT::insertFix(node*& root, node*& pt) {
        node* parent_pt = nullptr;
        node* grand_parent_pt = nullptr;

        while ((pt != root) && (pt->color != BLACK) && (pt->father->color == RED))
        {

            parent_pt = pt->father;
            grand_parent_pt = pt->father->father;

            /*  Case : A
                Parent of pt is left child of Grand-parent of pt */
            if (parent_pt == grand_parent_pt->left)
            {

                node* uncle_pt = grand_parent_pt->right;

                /* Case : 1
                   The uncle of pt is also red
                   Only Recoloring required */
                if (uncle_pt != nullptr && uncle_pt->color == RED)
                {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                }

                else
                {
                    /* Case : 2
                       pt is right child of its parent
                       Left-rotation required */
                    if (pt == parent_pt->right)
                    {
                        rotateL(root, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->father;
                    }

                    /* Case : 3
                       pt is left child of its parent
                       Right-rotation required */
                    rotateR(root, grand_parent_pt);
                    swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            }

            /* Case : B
               Parent of pt is right child of Grand-parent of pt */
            else
            {
                node* uncle_pt = grand_parent_pt->left;

                /*  Case : 1
                    The uncle of pt is also red
                    Only Recoloring required */
                if ((uncle_pt != nullptr) && (uncle_pt->color == RED))
                {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                }
                else
                {
                    /* Case : 2
                       pt is left child of its parent
                       Right-rotation required */
                    if (pt == parent_pt->left)
                    {
                        rotateR(root, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->father;
                    }

                    /* Case : 3
                       pt is right child of its parent
                       Left-rotation required */
                    rotateL(root, grand_parent_pt);
                    swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            }
        }

        root->color = BLACK;
    }

    // Function to insert a new node with given data 
    void TreeRBT::insert(const int& key, const string& val) {
        node* pt = new node(key, val);

        // Do a normal BST insert 
        root = insertBST(root, pt);

        // fix Red Black Tree violations 
        insertFix(root, pt);

    }


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



// Driver Code 

int mainnnnn()
{
    Tree tree;
    cin.get();
    cout << "Sto caricando gli elementi..." << endl;
    for (int i = 0; i < 10000000; i++) tree.insert(i, "");
    cout << "Caricati" << endl;

    cin.get();

    cout<<endl<<check(tree.root);
    //RBT::node::show(((RBT::Tree*)avl)->root);
    cout << "\nSto eliminando gli elementi.." << endl;
    tree.root = clear(tree.root);

    cout << "Eliminati" << endl;
    //RBT::node::show(((RBT::Tree*)avl)->root);

    cin.get();
    cin.get();

    

    return 0;
}
*/