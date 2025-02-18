#include <iostream>
#include <climits>
#include <stack>
using namespace std;

/** 
 * Problem: given a tree, balance the tree
 *  if we brute force, we can balance the tree by in order traversal into another DS, and then taking the middle
 *  Otherwise the solution should be checking the height of the left subtree and the right subtree to make sure the 
 *  absolute difference is not greater than 1. 
 * 
 * Additional Problems included: Is BST Balanced?, Is BST valid?,         
 */


struct treenode {
    int val;
    treenode* left;
    treenode* right;
    treenode(int x) : val(x), left(nullptr),  right(nullptr) {};
};

void deletebst(treenode* root){
    if (root == nullptr) return;
    deletebst(root->left);
    deletebst(root->right);
    delete root;
    root = nullptr;
}

void inordercopy(treenode* root, vector<int>& inorder_store) {
    if (root == nullptr) return;
    inordercopy(root->left, inorder_store);
    // visit the node in order
    inorder_store.push_back(root->val);
    inordercopy(root->right, inorder_store);
}

treenode* RebuildBalancedBSTHelper(vector<int>& inorder_arr, int l, int r) {
    if (l > r) return nullptr; 

    int mid = (l + r) / 2;
    treenode* current = new treenode(inorder_arr[mid]);
    current->left = RebuildBalancedBSTHelper(inorder_arr, l, mid-1);
    current->right = RebuildBalancedBSTHelper(inorder_arr, mid+1, r);
    
    return current;
}

treenode* RebuildBalancedBST(treenode* root) {
    /**
     * BRUTE FORCE 
     * First we can flatten the BST In-order into an array
     * Then recursively get the center of the subtree linked list on left and right
     * 0 1 2 3 4 5 6 7 8 9
     *         *          
     * 0 1 2 3<4>5 6 7 8 9
     *   *           *    
     * ...
     */

    if (root == nullptr) return nullptr;
    vector<int> inorder;
    inordercopy(root, inorder);
    // recursively build subtree (in preorder: root->left->right)
    return RebuildBalancedBSTHelper(inorder, 0, inorder.size()-1);
}

treenode* BalanceBSTInPlace(treenode* root);

/**
 * 
 * Below are functions implemented to understand this problem
 * and learn more about Balanced BST
 * 
 */

int isBalanced(treenode* root) {
    if (root == nullptr) return 0;
    int leftHeight = isBalanced(root->left);
    if (leftHeight == -1) return -1;
    int rightHeight = isBalanced(root->right);
    if (rightHeight == -1) return -1;
    if (abs(leftHeight-rightHeight) > 1) return -1;
    return 1 + max(leftHeight, rightHeight);
}

int treeHeight(treenode* root) {
    if (root == nullptr) return 0;
    int l = treeHeight(root->left);
    int r = treeHeight(root->right);
    return 1 + max(l, r);
}

int isValidBinaryTreeInOrder(treenode* root, treenode* prev) {
    /**
     * In-Order approach, tracks previous value
     */
    if (root == nullptr) return true;

    if (!isValidBinaryTreeInOrder(root->left, prev)) return false;
    if (prev && prev->val > root->val) return false;
    prev = root;
    return isValidBinaryTreeInOrder(root->right, prev);
}

bool isValidBinaryTreeMinMax(treenode* root, long long int low, long long int high) {
    /**
     * Uses pre-order traversal
     */
    if (root == nullptr) return true;
    if (root->val < low || root->val > high) return false;
    if (!isValidBinaryTreeMinMax(root->left, low, root->val)) return false;
    if (!isValidBinaryTreeMinMax(root->right, root->val, high)) return false;
    return true;
}

bool isValidBSTIterative(treenode* root) {
    if (root == nullptr) return true;
    stack<treenode*> s;  
    /**
     * Inorder traversal using stack
     */
    treenode* temp = root;
    treenode* prev = nullptr;

    while (temp || !s.empty()) {
        while (temp != nullptr) {
            s.push(temp);
            temp = temp->left;
        }

        treenode* curr = s.top();
        s.pop();
        if (prev && curr->val <= prev->val) return false;
        prev = curr;

        if (curr->right != nullptr) temp = curr->right;
    }

    return true;
}


bool isValidBinaryTree(treenode* root) {
    // wrapper function
    // In-Order Implementation
    return isValidBinaryTreeInOrder(root, nullptr);
    // In-Order Iterative Implementation
    return isValidBSTIterative(root);
    // Min/Max Implementation
    return isValidBinaryTreeMinMax(root, LLONG_MIN, LLONG_MAX);
}

/***
 * Below is testing code for 
 *      1. Is Valid BST
 *      2. Is Balanced BST
 *      3. Balance BST
 */


void testIsValidBST() {
    cout << "=====================================" << endl;
    cout << "   ** Testing IsValidBST Function **  " << endl;
    cout << "=====================================" << endl;

    // Test case 1: Valid BST
    treenode* root1 = new treenode(2);
    root1->left = new treenode(1);
    root1->right = new treenode(3);
    cout << "[Test Case 1] Valid BST: " << (isValidBinaryTree(root1) ? "✔ Passed" : "✘ Failed") << endl;

    // Test case 2: Invalid BST
    treenode* root2 = new treenode(1);
    root2->left = new treenode(2);
    root2->right = new treenode(3);
    cout << "[Test Case 2] Invalid BST: " << (isValidBinaryTree(root2) == false ? "✔ Passed" : "✘ Failed") << endl;

    // Test case 3: Empty tree
    treenode* root3 = nullptr;
    cout << "[Test Case 3] Empty Tree: " << (isValidBinaryTree(root3) ? "✔ Passed" : "✘ Failed") << endl;

    // Test case 4: Single node tree
    treenode* root4 = new treenode(1);
    cout << "[Test Case 4] Single Node: " << (isValidBinaryTree(root4) ? "✔ Passed" : "✘ Failed") << endl;

    cout << "=====================================" << endl;
    cout << "   ** End of IsValidBST Function **  " << endl;
    cout << "=====================================\n" << endl;
}

void testIsBalanced() {
    cout << "=====================================" << endl;
    cout << "   ** Testing IsBalanced Function ** " << endl;
    cout << "=====================================" << endl;

    // Test case 1: Balanced tree
    treenode* root1 = new treenode(1);
    root1->left = new treenode(2);
    root1->right = new treenode(3);
    root1->left->left = new treenode(4);
    root1->left->right = new treenode(5);
    root1->right->right = new treenode(6);
    cout << "[Test Case 1] Balanced Tree: " << (isBalanced(root1) != -1 ? "✔ Passed" : "✘ Failed") << endl;

    // Test case 2: Unbalanced Tree
    treenode* root2 = new treenode(1);
    root2->left = new treenode(2);
    root2->left->left = new treenode(3);
    root2->left->left->left = new treenode(4);
    cout << "[Test Case 2] Unbalanced Tree: " << (isBalanced(root2) ? "✔ Passed" : "✘ Failed") << endl;

    // Test case 3: Empty tree
    treenode* root3 = nullptr;
    cout << "[Test Case 3] Empty Tree: " << (isBalanced(root3) != -1 ? "✔ Passed" : "✘ Failed") << endl;

    // Test case 4: Single node tree
    treenode* root4 = new treenode(1);
    cout << "[Test Case 4] Single Node: " << (isBalanced(root4) != -1 ? "✔ Passed" : "✘ Failed") << endl;

    cout << "=====================================" << endl;
    cout << "   ** End of IsBalanced Function **  " << endl;
    cout << "=====================================\n" << endl;
}

void printInOrder(treenode* root) {
    if (!root) return;
    printInOrder(root->left);
    cout << root->val << " ";
    printInOrder(root->right);
}

void testRebuildBalancedBST() {
    cout << "=====================================" << endl;
    cout << "   ** Testing RebuildBalancedBST **   " << endl;
    cout << "=====================================" << endl;

    // Test Case 1: Right-skewed (Unbalanced) Tree
    treenode* root1 = new treenode(10);
    root1->right = new treenode(20);
    root1->right->right = new treenode(30);
    root1->right->right->right = new treenode(40);
    root1->right->right->right->right = new treenode(50);

    cout << "[Test Case 1] Before Balancing: ";
    printInOrder(root1);
    cout << endl;
    root1 = RebuildBalancedBST(root1);
    cout << "[Test Case 1] After Balancing: ";
    printInOrder(root1);
    cout << endl;
    cout << "[Test Case 1] Is Balanced? " << (isBalanced(root1) ? "✔ Passed" : "✘ Failed") << endl;
    cout << "-------------------------------------" << endl;

    // Test Case 2: Left-skewed (Unbalanced) Tree
    treenode* root2 = new treenode(50);
    root2->left = new treenode(40);
    root2->left->left = new treenode(30);
    root2->left->left->left = new treenode(20);
    root2->left->left->left->left = new treenode(10);

    cout << "[Test Case 2] Before Balancing: ";
    printInOrder(root2);
    cout << endl;
    root2 = RebuildBalancedBST(root2);
    cout << "[Test Case 2] After Balancing: ";
    printInOrder(root2);
    cout << endl;
    cout << "[Test Case 2] Is Balanced? " << (isBalanced(root2) ? "✔ Passed" : "✘ Failed") << endl;
    cout << "-------------------------------------" << endl;

    // Test Case 3: Already Balanced Tree
    treenode* root3 = new treenode(30);
    root3->left = new treenode(20);
    root3->right = new treenode(40);
    root3->left->left = new treenode(10);
    root3->right->right = new treenode(50);

    cout << "[Test Case 3] Before Balancing: ";
    printInOrder(root3);
    cout << endl;
    root3 = RebuildBalancedBST(root3);
    cout << "[Test Case 3] After Balancing: ";
    printInOrder(root3);
    cout << endl;
    cout << "[Test Case 3] Is Balanced? " << (isBalanced(root3) ? "✔ Passed" : "✘ Failed") << endl;
    cout << "-------------------------------------" << endl;

    // Test Case 4: Single Node Tree
    treenode* root4 = new treenode(10);

    cout << "[Test Case 4] Before Balancing: ";
    printInOrder(root4);
    cout << endl;
    root4 = RebuildBalancedBST(root4);
    cout << "[Test Case 4] After Balancing: ";
    printInOrder(root4);
    cout << endl;
    cout << "[Test Case 4] Is Balanced? " << (isBalanced(root4) ? "✔ Passed" : "✘ Failed") << endl;
    cout << "-------------------------------------" << endl;

    // Test Case 5: Empty Tree
    treenode* root5 = nullptr;
    cout << "[Test Case 5] Before Balancing: (Empty Tree)" << endl;
    root5 = RebuildBalancedBST(root5);
    cout << "[Test Case 5] After Balancing: (Empty Tree)" << endl;
    cout << "[Test Case 5] Is Balanced? " << (isBalanced(root5) ? "✔ Passed" : "✘ Failed") << endl;

    cout << "=====================================" << endl;
    cout << "  ** End of RebuildBalancedBST **    " << endl;
    cout << "=====================================\n" << endl;
}

int main() {
    testIsBalanced();
    testIsValidBST();
    testRebuildBalancedBST();
    return 0;
}