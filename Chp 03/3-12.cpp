/**
 * Maximum depth of a binary tree is the number of dnoes on the path from the root down to the most distant leaf node
 * give an O(n) algo to find the maximum depth of a binary tree with n nodes. -- dfs
 */

#include<iostream>
#include <queue>
using namespace std;

struct binarytree {
    int data;
    binarytree* l = nullptr;
    binarytree* r = nullptr;
};

binarytree* node(int d) {
    binarytree* n = new binarytree();
    n->data = d;
    return n; 
}

binarytree* example() {
    // example tree from: 
    // https://media.geeksforgeeks.org/wp-content/uploads/20241029100402817236/remove-nodes-from-binary-tree-such-that-sum-of-all-remaining-root-to-leaf-paths-is-atleast-k.webp
    binarytree* root = new binarytree();
    root->data = 5;
    root->l = node(4);
    root->r = node(3);

    binarytree* curr = root;
    curr = root->r;
    curr->r = node(9); 
    
    curr = root->l;
    curr->l = node(9);
    curr->r = node(8);

    curr = curr->r;
    curr->r = node(11);
    curr->l = node(5);

    curr = curr->l;
    curr->l = node(6);
    curr->r = node(2);

    return root;
}

void printbinarytree(binarytree* root) {
    queue<binarytree*> btq;
    btq.push(root);
    cout << "[ ";
    while(!btq.empty()) {
        binarytree* curr = btq.front();
        btq.pop();
        if (curr) { /* make sure to check that the current value is NOT NULL*/
            cout << curr->data << " ";
            btq.push(curr->l);
            btq.push(curr->r);
        }
    }
    cout << "]\n";
}

void deletetree(binarytree* root) {
    // code to delete binary tree and free all nodes
    if (root == nullptr) return;
    deletetree(root->l);
    deletetree(root->r);
    delete root;
}

int maxdepthDFS(binarytree* root) {
    if (root == nullptr) return 0; // basecase
    int leftSubTreeDepth = maxdepthDFS(root->l) + 1;
    int rightSubTreeDepth = maxdepthDFS(root->r) + 1;
    return max(leftSubTreeDepth, rightSubTreeDepth);
}

int maxdepthBFS(binarytree* root) {
    if (root == nullptr) return 0;
    queue<binarytree*> btq;
    int depth = 0;
    btq.push(root);
    while(!btq.empty()) {
        int levelSize = btq.size();
        depth++;

        // process all the elements at the current level
        for (int i = 0; i < levelSize; i++) {
            binarytree* curr = btq.front();
            btq.pop();
            if (curr->l) btq.push(curr->l); // Push left child if exists
            if (curr->r) btq.push(curr->r); // Push right child if exists
        }
    }
    return depth;
}

void runPrinter(void (*printFunc)(binarytree*), const string printFuncName, binarytree* root) {
    cout << "Printed by " << printFuncName << ": [ ";
    printFunc(root);
    cout << "]" << endl;
} 

void preorderDFS(binarytree* root) {
    if (root == nullptr) return;
    cout << root->data << " ";
    preorderDFS(root->l);
    preorderDFS(root->r); 
} 

void inorderDFS(binarytree* root) {
    if (root == nullptr) return;
    inorderDFS(root->l);
    cout << root->data << " ";
    inorderDFS(root->r); 
} 

void postorderDFS(binarytree* root) {
    if (root == nullptr) return;
    postorderDFS(root->l);
    postorderDFS(root->r); 
    cout << root->data << " ";
} 

int main() {

    // Create the example binary tree
    binarytree* root = example();

    // Print the binary tree
    cout << "Binary Tree: ";
    printbinarytree(root);
    cout << "Maximum depth of Binary Tree (dfs):" << maxdepthDFS(root) << endl; // expected: 4
    cout << "Maximum depth of Binary Tree (bfs):" << maxdepthDFS(root) << endl; // expected: 4

    runPrinter(preorderDFS, "Pre-Order DFS", root);
    runPrinter(inorderDFS, "In-Order DFS", root);
    runPrinter(postorderDFS, "Post-Order DFS", root);

    deletetree(root);
    return 0;
}