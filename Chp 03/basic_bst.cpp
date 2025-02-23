#include <iostream>
#include <iomanip> 
using namespace std;

struct treenode {
    int val;
    treenode* left;
    treenode* right;
    treenode(int x): val(x), left(nullptr), right(nullptr){}
};

/**
 * Traversals 
 */
void inorder(treenode* root, vector<int>& inorder_store){
    if (!root) return;
    inorder(root->left, inorder_store);
    inorder_store.push_back(root->val);
    inorder(root->right, inorder_store);
}
void preoder(treenode* root, vector<int>& preorder_store) {
    if (!root) return;
    preorder_store.push_back(root->val);
    preoder(root->left, preorder_store);
    preoder(root->right, preorder_store);
}

void postorder(treenode* root, vector<int>& postorder_store) {
    if (!root) return;
    postorder(root->left, postorder_store);
    postorder(root->right, postorder_store);
    postorder_store.push_back(root->val);
}

treenode* search(treenode* root, int key) {
    if (!root || root->val == key) return root;
    if (root->val > key) return search(root->left, key);
    return search(root->right, key);
}   

treenode* searchiter(treenode* root, int key) {
    if (!root) return nullptr;
    while (root) {
        if (root->val == key) { return root; }
        root = (root->val > key) ? root->left : root->right;
    }
    return nullptr;
}

treenode* insert(treenode*& root, int x) {
    if (!root) return new treenode(x);
    if (root->val > x) root->left = insert(root->left, x);
    else root->right = insert(root->right, x);
    return root;
}

treenode* insertiter(treenode*& root, int key){
    if (!root) return new treenode(key);
    treenode* it = root;
    treenode* parent = nullptr;
    while (it) {
        parent = it;
        it = (it->val > key) ? it->left : it->right;    
    }

    if (parent->val > key) parent->left = new treenode(key);
    else parent->right = new treenode(key);
    return root;
}

treenode* remove(treenode* root, int key) {
    // hint: return treenode* new root, because the root may change on delete call
    if (!root) return root;
    if (root->val > key) {
        root->left = remove(root->left, key);
    } else if (root->val < key) {   
        root->right = remove(root->right, key);
    } else { // we've found the node to delete
        // 0 or one children
        if (!root->left) return root->right;
        if (!root->right) return root->left;
        
        // 2 children -> swap with successor node, 
        //                  and delete successor node [left-most node on right subtree]
        treenode* curr = root->right;
        while (curr->left) curr = curr->left;

        root->val = curr->val;
        root->right = remove(root->right, root->val);
    }
    return root;
}

void assignNewChild(treenode*& root, treenode*& parent, treenode* old_child, treenode* new_child) {
    if (!parent) root = new_child;
    else if (parent->left == old_child) parent->left = new_child;
    else parent->right = new_child;
    delete old_child; // Free memory
}

treenode* removeiter(treenode* root, int key) {
    if (!root) return nullptr;

    treenode* it = root; 
    treenode* parent = nullptr;

    while (it && it->val != key) {
        parent = it;
        it = (it->val > key) ? it->left: it->right;
    }
    if (!it) return root;

    if (!it->right) {    // cases 1,2: 0 or 1 child:
        assignNewChild(root, parent, it, it->left);
    } else if (!it->left) {
        assignNewChild(root, parent, it, it->right);
    } else { 
        // case 3: 2 children: find successor
        treenode* successor = it->right;
        treenode* successorParent = it;
        while (successor->left) {
            successorParent = successor;
            successor = successor->left;
        }

        it->val = successor->val;
        assignNewChild(root, successorParent, successor, successor->right);
    }

    return root;
}

// treenode* successor(treenode* root, int key) {
//     return nullptr;
// }


treenode* minimum(treenode* root) {
    if (!root) return nullptr;
    while(root->left)
        root = root->left;
    return root;
}

treenode* maximum(treenode* root) {
    if (!root) return nullptr;
    while(root->right)
        root = root->right;
    return root;
}

treenode* inorderSuccessor(treenode* root, int key) {
    
    treenode* successor = nullptr;
    while(root) {
        if (root->val <= key) {
            root = root->right;
        } else {
            successor = root;
            root = root->left;
        }    
    }
    return successor;
}


treenode* inorderPredecessor(treenode* root, int key) {
    if (searchiter(root, key) == nullptr) return nullptr;
    treenode* predecessor = nullptr;
    while(root) {
        if (key <= root->val) {
            root = root->left;
        } else {
            predecessor = root;
            root = root->right;
        }    
    }
    return predecessor;
}


treenode* inorderSuccessorIter(treenode* root, int key) { 
    /**
     * Sucessor of the node is either it's parent, or the left-most node in the right subtree.
     */
    if (!root) return nullptr;
    treenode* successorNode = nullptr;
    treenode* it = root;
    while((it->right || it->left) && it->val != key) {
        successorNode = it;
        it = (it->val > key) ? it->left : it->right;
    } 

    if (!it) return nullptr; // key not found

    if (it->right) {
        successorNode = it->right;
        while(successorNode && successorNode->left) successorNode = successorNode->right;
    }
    return successorNode;
}




/** 
* TESTING Generated by ChatGPT
*/
void printTestResult(const string& testName, bool passed, int response = 0) {
    int width = 60;  // Total width for alignment
    cout << left << setw(width) << setfill('.') << testName 
         << (passed ? "✅ Passed" : "❌ Failed | Out: " + to_string(response)) << endl;
}

// Helper function for inorder traversal (for debugging)
void inorder(treenode* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->val << " ";
    inorder(root->right);
}

// Test suite
void runTests() {
    cout << "============================ BST TEST SUITE ============================\n";
    cout << left << setw(60) << "Test Case" << "Result" << endl;
    cout << "------------------------------------------------------------------------\n";

    // Initialize tree
    treenode* root = nullptr;

    // Test: Insert
    root = insert(root, 50);
    root = insertiter(root, 30);
    root = insertiter(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);
    
    printTestResult("Insert: Structure Built", root != nullptr);
    printTestResult("Search 50 (root)", search(root, 50) != nullptr);
    printTestResult("Search 30 (left child)", search(root, 30) != nullptr);
    printTestResult("Search 70 (right child)", searchiter(root, 70) != nullptr);
    printTestResult("Search 100 (non-existent)", searchiter(root, 100) == nullptr);
    cout << "========================================================================\n";

    printTestResult("Minimum of tree", minimum(root)->val == 20);
    printTestResult("Maximum of tree", maximum(root)->val == 80);
    cout << "========================================================================\n";

    printTestResult("Successor of 20 is 30", inorderSuccessor(root, 20) && inorderSuccessor(root, 20)->val == 30, inorderSuccessor(root, 20)->val);
    printTestResult("Successor of 30 is 40", inorderSuccessor(root, 30) && inorderSuccessor(root, 30)->val == 40, inorderSuccessor(root, 30)->val);
    printTestResult("Successor of 40 is 50", inorderSuccessor(root, 40) && inorderSuccessor(root, 40)->val == 50, inorderSuccessor(root, 20)->val);
    printTestResult("Successor of 50 is 60", inorderSuccessor(root, 50) && inorderSuccessor(root, 50)->val == 60, inorderSuccessor(root, 20)->val);
    printTestResult("Successor of 60 is 70", inorderSuccessor(root, 60) && inorderSuccessor(root, 60)->val == 70, inorderSuccessor(root, 20)->val);
    printTestResult("Successor of 70 is 80", inorderSuccessor(root, 70) && inorderSuccessor(root, 70)->val == 80, inorderSuccessor(root, 20)->val);
    printTestResult("Successor of 80 is NULL", inorderSuccessor(root, 80) == nullptr);
    printTestResult("Successor of non-existent 100 is NULL", inorderSuccessor(root, 100) == nullptr);

    // Predecessor tests
    printTestResult("Predecessor of 80 is 70", inorderPredecessor(root, 80) && inorderPredecessor(root, 80)->val == 70, inorderPredecessor(root, 80)->val);
    printTestResult("Predecessor of 70 is 60", inorderPredecessor(root, 70) && inorderPredecessor(root, 70)->val == 60, inorderPredecessor(root, 70)->val);
    printTestResult("Predecessor of 60 is 50", inorderPredecessor(root, 60) && inorderPredecessor(root, 60)->val == 50, inorderPredecessor(root, 60)->val);
    printTestResult("Predecessor of 50 is 40", inorderPredecessor(root, 50) && inorderPredecessor(root, 50)->val == 40, inorderPredecessor(root, 50)->val);
    printTestResult("Predecessor of 40 is 30", inorderPredecessor(root, 40) && inorderPredecessor(root, 40)->val == 30, inorderPredecessor(root, 40)->val);
    printTestResult("Predecessor of 30 is 20", inorderPredecessor(root, 30) && inorderPredecessor(root, 30)->val == 20, inorderPredecessor(root, 30)->val);
    printTestResult("Predecessor of 20 is NULL", inorderPredecessor(root, 20) == nullptr);
    printTestResult("Predecessor of non-existent 100 is NULL", inorderPredecessor(root, 100) == nullptr, inorderPredecessor(root, 100)->val);

    cout << "========================================================================\n";

    // Test: Remove Leaf Node
    root = removeiter(root, 20);
    printTestResult("Remove Leaf Node (20)", search(root, 20) == nullptr);

    // Test: Remove Node with One Child
    root = removeiter(root, 30);
    printTestResult("Remove Node with One Child (30)", search(root, 30) == nullptr);

    // Test: Remove Node with Two Children
    root = removeiter(root, 50);
    printTestResult("Remove Node with Two Children (50)", search(root, 50) == nullptr);

    // Test: Remove Root Node
    root = removeiter(root, 60);
    printTestResult("Remove Root Node (60)", search(root, 60) == nullptr);

    // Test: Remove Non-Existent Node
    treenode* prevRoot = root;
    root = removeiter(root, 100);
    printTestResult("Remove Non-Existent Node (100)", root == prevRoot); // Tree should remain unchanged

    cout << "========================================================================\n";
}



int main() {
    runTests();
    return 0;
}