#include <iostream>
using namespace std;

struct treenode {
    int val;
    treenode* left;
    treenode* right;
    treenode(int x): val(x), left(nullptr), right(nullptr) {}
    treenode(int x, treenode* left, treenode* right): val(x), left(left), right(right) {}
};

treenode* leftmost(treenode* root) {
    while(root->left != nullptr) 
        root = root->left;
    return root;
}

treenode* rightmost(treenode* root) {
    while(root->right != nullptr)
        root = root->right;
    return root;
}

void findPreSuc(treenode* root, int key, treenode*& pre, treenode*& suc) {
    /**
     * This iterative approach finds predecessor and successor
     * 
     */
    while (root != nullptr) {
        if (root->val < key) {
            // set current root as pre 
            // since it's the most-recent value that is less than key
            pre = root;
            root = root->right; // go to right since value < key
        } else if (root->val > key) {
            // set current root as suc
            // since it's the most-recent 
            suc = root;
            root = root->left;
        } else {
            // the root node is equal to key 
            // if there is a left subtree, set right-most of left subtree as pre
            if (root->left) {
                pre = rightmost(root->left);
            }
            
            // if there is a right subtree, set left-most of right subtree as suc
            if (root->right) {
                suc = leftmost(root->right);
            }
        }
    }
}


int main() {
    // testing code from geeksforgeeks
    int key = 65;
  
    // Let us create the following BST
    //          50
    //       /     \
    //      30      70
    //     /  \    /  \
    //   20   40  60   80
    treenode *root = new treenode(50);
    root->left = new treenode(30);
    root->right = new treenode(70);
    root->left->left = new treenode(20);
    root->left->right = new treenode(40);
    root->right->right = new treenode(80);
    root->right->left = new treenode(60);

    treenode *pre = nullptr;
    treenode *suc = nullptr;

    findPreSuc(root, key, pre, suc);

    if (pre != nullptr)
        cout << "Predecessor is: " << pre->val << endl;
    else
        cout << "No Predecessor" << endl;

    if (suc != nullptr)
       cout << "Successor is: " << suc->val << endl;
    else
        cout << "No Successor" << endl;

    return 0;
}