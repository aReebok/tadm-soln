#include <iostream>
#include <queue>
using namespace std;

/**
 * two elements of a BST have been swapped by mistake.
 * give an O(n) algo to find these pair to swap back.
 * 
 * For this problem set up, I will need:
 *      1. TreeNode struct
 *      2. BST Insert function
 *      3. Print BST function
 *      4. swapNode, findNode
 *      5. destroy BST
 * To solve the problem I write IncorrectPair using technique:
 *      DFS: In-order traversal, passing in pointers (prev_root, root, first_elem, second_elem)
 */

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int n) : val(n), left(nullptr), right(nullptr) {}
};

TreeNode* InsertBST(TreeNode* root, int val) {
    if (root == nullptr) {
        TreeNode* newNode = new TreeNode(val);
        return newNode;
    }

    if (root->val > val) { // left subtree
        root->left = InsertBST(root->left, val);
    } else { // right subtree
        root->right = InsertBST(root->right, val);
    }

    return root;
} 

TreeNode* FindNode(TreeNode* root, int val) {
    if (root == nullptr) return root;
    if (root->val == val) return root;

    if (root->val > val) return FindNode(root->left, val);
    return FindNode(root->right, val);
} 

void swapNodes(TreeNode* root, int swap_1, int swap_2) {
    TreeNode* n1 = FindNode(root, swap_1);
    TreeNode* n2 = FindNode(root, swap_2);
    // perform swap of values
    int temp = n1->val;
    n1->val = n2->val;
    n2->val = temp;
}

void swapNodes(TreeNode* n1, TreeNode* n2) {
    // perform swap of values
    int temp = n1->val;
    n1->val = n2->val;
    n2->val = temp;
}


void PrintBST(TreeNode* root) {
    if (root == nullptr) {
        cout << "Empty Tree\n";
        return;
    } 

    queue<TreeNode*> q;
    int level = 0; // print our the height of tree
    int count = 0;
    q.push(root);

    while (!q.empty()) {
        level++; 
        count = q.size();
        for(int i = 0; i < count; i++) { // traverse one level at a time
            TreeNode* currNode = q.front();
            q.pop();
            cout << currNode->val << " ";
            if (currNode->left != nullptr) q.push(currNode->left);
            if (currNode->right != nullptr) q.push(currNode->right);
        }
        cout << endl;
    }

    cout << "The height of the tree: " << level << endl; 
}

void DestroyBST(TreeNode* root) {
    // post-order traversal: 
    // first destory the l, r subtrees, then destroy the root. 
    if (root == nullptr) return;
    DestroyBST(root->left);
    DestroyBST(root->right);
    free(root);
}

/**
 * We will need to traverse the tree in IN-Order dfs 
 * 
 */
void CorrectBST (TreeNode* root, TreeNode* prevRoot, TreeNode* &first, TreeNode* &second){
    // basecase 
    if (root == nullptr) return; 
    CorrectBST(root->left, prevRoot, first, second);
    // visit the node -- and do our work here

    if (first == nullptr && prevRoot->val > root->val) first = prevRoot;
    if (first != nullptr && prevRoot->val > root->val) second = root;
    prevRoot = root;

    CorrectBST(root->right, prevRoot, first, second);
} 

void printInOrder(TreeNode* root) {
    if (root == nullptr) return;
    printInOrder(root->left);
    cout << root->val << " ";
    printInOrder(root->right);
}

int main() {
    TreeNode* root = nullptr;
    root = InsertBST(root, 3);
    root = InsertBST(root, 1);
    root = InsertBST(root, 7);
    root = InsertBST(root, 5);
    root = InsertBST(root, 10);

    // Print the original tree
    cout << "Original Tree:\n";
    PrintBST(root);

    // Swapping nodes with set() function
    cout << "\nAfter Swapping 3 with 7:\n";
    swapNodes(root, 3, 7);  // Swap node 3 with 7
    PrintBST(root);

    // correctBST 
    cout << "\nCorrecting bst..:\n";
    TreeNode* first = nullptr;
    TreeNode* second = nullptr;
    TreeNode* prevRoot = new TreeNode(INT_MIN);

    CorrectBST(root, prevRoot, first, second);
    free(prevRoot);
    swapNodes(first, second);
    PrintBST(root);

    // Swapping nodes with set() function
    cout << "\nAfter Swapping 1 with 10 :\n";
    swapNodes(root, 1, 10);  // Swap node 3 with 7
    printInOrder(root);
    cout << endl;

    // correctBST 
    cout << "\nCorrecting bst..:\n";
    
    first = second = nullptr;
    TreeNode* prevRoot2 = new TreeNode(INT_MIN);
    CorrectBST(root, prevRoot2, first, second);
    free(prevRoot2);
    swapNodes(first, second);
    printInOrder(root);
    cout << endl;

    
    DestroyBST(root);

}