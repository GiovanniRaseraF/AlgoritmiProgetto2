
#include <iostream>
using namespace std;

enum Color { RED, BLACK };

class node{
public:
    int key;
    string val;
    bool color;
    node* left,* right,* father;

    // Constructor 
    node(int key, const string& val){
        this->key = key;
        this->val = val;
        left = right = father = nullptr;
        this->color = RED;
    }

    ~node() {}
};


class Tree{
public:
    node* root;
    void rotateL(node*&, node*&);
    void rotateR(node*&, node*&);
    void fixViolation(node*&, node*&);
    void insert(const int& n, const string& val);
    // Constructor 
    Tree() { root = nullptr; }
};



node* insertBST(node* root, node* puntatore){
    if (root == nullptr) return puntatore;
    if (puntatore->key < root->key){
        root->left = insertBST(root->left, puntatore);
        root->left->father = root;
    }else if (puntatore->key > root->key){
        root->right = insertBST(root->right, puntatore);
        root->right->father = root;
    }
    return root;
}



void Tree::rotateL(node*& root, node*& puntatore){
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

void Tree::rotateR(node*& root, node*& puntatore){
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

void Tree::fixViolation(node*& root, node*& pt){
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
void Tree::insert(const int& key, const string& val)
{
    node* pt = new node(key, val);

    // Do a normal BST insert 
    root = insertBST(root, pt);

    // fix Red Black Tree violations 
    fixViolation(root, pt);
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
    




// Driver Code 
int main()
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