#include <iostream>
#include <climits>
#include <stack>
using namespace std;

/** 
 * Problems: 
 *  3-15 given a tree, balance the tree
 *      if we brute force, we can balance the tree by in order traversal into another DS, and then taking the middle
 *      Otherwise the solution should be checking the height of the left subtree and the right subtree to make sure the 
 *      absolute difference is not greater than 1. 
 * 
 *  3-17 given an n-node Binary Search tree
 *      in O(n) time complexity return whether the tree is balanced or not
 * 
 * Additional Problems included: Is BST valid?, Shortest BST Path, Longest BST path.
 *      
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
    int m = (l + r) / 2;
    treenode* current = new treenode(inorder_arr[m]);
    current->left = RebuildBalancedBSTHelper(inorder_arr, l, m-1);
    current->right = RebuildBalancedBSTHelper(inorder_arr, m+1, r);

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
    return 1 + max(treeHeight(root->left), treeHeight(root->right));
}

int LongestBSTPath(treenode* root) {
    if (root == nullptr) return -1; // emptry tree cannot have any edges.
    int l = LongestBSTPath(root->left);
    int r = LongestBSTPath(root->right);
    return 1 + max(l, r);
}

int ShortestBSTPath(treenode* root) {
    if (root == nullptr) return -1; 
    if (!root->right) return 1 + ShortestBSTPath(root->left);
    if (!root->left) return 1 + ShortestBSTPath(root->right);
    return 1 + min(ShortestBSTPath(root->left), ShortestBSTPath(root->right));
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
 *      4. BST Path - Shortest and Longest path in BST
 */



#include <iostream>
#include <climits> // For INT_MAX and INT_MIN
using namespace std;

void testBSTPaths() {
    cout << "=====================================" << endl;
    cout << "   ** Testing BST Path Functions **  " << endl;
    cout << "=====================================" << endl;

    // Test case 1: Perfectly balanced tree
    treenode* root1 = new treenode(1);
    root1->left = new treenode(2);
    root1->right = new treenode(3);
    root1->left->left = new treenode(4);
    root1->left->right = new treenode(5);
    root1->right->left = new treenode(6);
    root1->right->right = new treenode(7);
    cout << "[Test Case 1] Balanced Tree: " << endl;
    cout << "  Longest Path: " << LongestBSTPath(root1) << " (Expected: 2) " << endl;
    cout << "  Shortest Path: " << ShortestBSTPath(root1) << " (Expected: 2) " << endl;
    cout << "-------------------------------------" << endl;

    // Test case 2: Left-skewed tree (like a linked list)
    treenode* root2 = new treenode(1);
    root2->left = new treenode(2);
    root2->left->left = new treenode(3);
    root2->left->left->left = new treenode(4);
    cout << "[Test Case 2] Left-Skewed Tree: " << endl;
    cout << "  Longest Path: " << LongestBSTPath(root2) << " (Expected: 3) " << endl;
    cout << "  Shortest Path: " << ShortestBSTPath(root2) << " (Expected: 3) " << endl;
    cout << "-------------------------------------" << endl;

    // Test case 3: Right-skewed tree (like a linked list)
    treenode* root3 = new treenode(1);
    root3->right = new treenode(2);
    root3->right->right = new treenode(3);
    root3->right->right->right = new treenode(4);
    cout << "[Test Case 3] Right-Skewed Tree: " << endl;
    cout << "  Longest Path: " << LongestBSTPath(root3) << " (Expected: 3) " << endl;
    cout << "  Shortest Path: " << ShortestBSTPath(root3) << " (Expected: 3) " << endl;
    cout << "-------------------------------------" << endl;

    // Test case 4: Unbalanced tree with mixed height
    treenode* root4 = new treenode(1);
    root4->left = new treenode(2);
    root4->right = new treenode(3);
    root4->left->left = new treenode(4);
    root4->left->left->left = new treenode(5);
    cout << "[Test Case 4] Mixed Unbalanced Tree: " << endl;
    cout << "  Longest Path: " << LongestBSTPath(root4) << " (Expected: 3) " << endl;
    cout << "  Shortest Path: " << ShortestBSTPath(root4) << " (Expected: 1) " << endl;
    cout << "-------------------------------------" << endl;

    // Test case 5: Single-node tree
    treenode* root5 = new treenode(1);
    cout << "[Test Case 5] Single Node Tree: " << endl;
    cout << "  Longest Path: " << LongestBSTPath(root5) << " (Expected: 0) " << endl;
    cout << "  Shortest Path: " << ShortestBSTPath(root5) << " (Expected: 0) " << endl;
    cout << "-------------------------------------" << endl;

    // Test case 6: Empty tree
    treenode* root6 = nullptr;
    cout << "[Test Case 6] Empty Tree: " << endl;
    cout << "  Longest Path: " << LongestBSTPath(root6) << " (Expected: -1) " << endl;
    cout << "  Shortest Path: " << ShortestBSTPath(root6) << " (Expected: -1) " << endl;

    cout << "=====================================" << endl;
    cout << "   ** End of BST Path Functions **   " << endl;
    cout << "=====================================\n" << endl;
}


// Helper function to print the tree in-order
void printInOrder(treenode* root) {
    if (!root) return;
    printInOrder(root->left);
    cout << root->val << " ";
    printInOrder(root->right);
}

// Function to create test trees
void createTestTrees(treenode*& root1, treenode*& root2, treenode*& root3, treenode*& root4) {
    // Test Tree 1: Balanced BST
    root1 = new treenode(2);
    root1->left = new treenode(1);
    root1->right = new treenode(3);

    // Test Tree 2: Invalid BST
    root2 = new treenode(1);
    root2->left = new treenode(2);
    root2->right = new treenode(3);

    // Test Tree 3: Left-skewed tree (Unbalanced)
    root3 = new treenode(1);
    root3->left = new treenode(2);
    root3->left->left = new treenode(3);
    root3->left->left->left = new treenode(4);

    // Test Tree 4: Right-skewed tree (Unbalanced)
    root4 = new treenode(10);
    root4->right = new treenode(20);
    root4->right->right = new treenode(30);
    root4->right->right->right = new treenode(40);
    root4->right->right->right->right = new treenode(50);
}

// Consolidated test function generated by ChatGPT
void runTests() {
    cout << "=====================================" << endl;
    cout << "        ** Running All BST Tests **  " << endl;
    cout << "=====================================\n" << endl;

    treenode *root1, *root2, *root3, *root4, *root5 = nullptr, *root6 = new treenode(1);
    createTestTrees(root1, root2, root3, root4);

    // === IsValidBST Tests ===
    cout << "********** Testing IsValidBST **********" << endl;
    cout << "[Test 1] Valid BST: " << (isValidBinaryTree(root1) ? "✔ Passed" : "✘ Failed") << endl;
    cout << "[Test 2] Invalid BST: " << (!isValidBinaryTree(root2) ? "✔ Passed" : "✘ Failed") << endl;
    cout << "[Test 3] Empty Tree: " << (isValidBinaryTree(root5) ? "✔ Passed" : "✘ Failed") << endl;
    cout << "[Test 4] Single Node: " << (isValidBinaryTree(root6) ? "✔ Passed" : "✘ Failed") << endl;
    cout << "****************************************\n" << endl;

    // === IsBalanced Tests ===
    cout << "********** Testing IsBalanced **********" << endl;
    cout << "[Test 1] Balanced Tree: " << (isBalanced(root1) != -1 ? "✔ Passed" : "✘ Failed") << endl;
    cout << "[Test 2] Unbalanced Tree (Left Skewed): " << (isBalanced(root3) == -1 ? "✔ Passed" : "✘ Failed") << endl;
    cout << "[Test 3] Empty Tree: " << (isBalanced(root5) != -1 ? "✔ Passed" : "✘ Failed") << endl;
    cout << "[Test 4] Single Node: " << (isBalanced(root6) != -1 ? "✔ Passed" : "✘ Failed") << endl;
    cout << "****************************************\n" << endl;

    // === RebuildBalancedBST Tests ===
    cout << "******** Testing RebuildBalancedBST ********" << endl;

    cout << "[Test 1] Right-Skewed Tree (Before -> After):" << endl;
    printInOrder(root4); cout << " -> ";
    root4 = RebuildBalancedBST(root4);
    printInOrder(root4);
    cout << (isBalanced(root4) != -1 ? " ✔ Passed" : " ✘ Failed") << endl;
    cout << "---------------------------------------------" << endl;

    cout << "[Test 2] Left-Skewed Tree (Before -> After):" << endl;
    printInOrder(root3); cout << " -> ";
    root3 = RebuildBalancedBST(root3);
    printInOrder(root3);
    cout << (isBalanced(root3) != -1 ? " ✔ Passed" : " ✘ Failed") << endl;
    cout << "*********************************************\n" << endl;

    testBSTPaths();

    cout << "=====================================" << endl;
    cout << "        ** End of ALL BST Tests **       " << endl;
    cout << "=====================================\n" << endl;

    deletebst(root1);
    deletebst(root2);
    deletebst(root3);
    deletebst(root4);
    deletebst(root5);
    deletebst(root6);
}

int main() {
    runTests();
    return 0;
}
