#include <iostream>
using namespace std;

/** 
 * Design a DS to support O(logn) time operations 
 *      O(logn) will require a self balancing tree
 *  1. Insert(x,T); insert item X in set T
 *  2. Delete(k,T): delete the kth smallest element from T
 *  3. Member(x,T): return true iff x in T
 *
 */

struct T {
    int val;
    T* left;
    T* right; 
    T(int x): val(x), left(nullptr), right(nullptr){}
};

void Insert(int x, T* t);
void Delete(int k, T* t);
bool Member(int x, T* t);

void Insert(int x, T* t) {
    if (t == nullptr) {
        t = new T(x);
        return;
    }
    
    if ( x < t->val ) {
        Insert(x, t->left);
    } else {
        Insert(x, t->right);
    }
} 

void Delete(int k, T* t) {
    /**
     * TO DO 
     */
}

bool Member(int x, T* t) { // O(logn)
    if (t == nullptr) return false;
    if (t->val == x) return true;
    if (t->val > x) return Member(x, t->left);
    if (t->val < x) return Member(x, t->right);
}

void writeInorderSequence(T* t, vector<int>& seq) {
    if (t == nullptr) return;
    writeInorderSequence(t->left, seq);
    // visit the node, write it into vector
    seq.push_back(t->val);
    writeInorderSequence(t->right, seq);
}

T* constructBST(vector<int> nums, int l, int r) {
    if (l > r) return nullptr;
    int m = (r+l)/2;
    T* tmp = new T(nums[m]);
    tmp->left = constructBST(nums, l, m-1);
    tmp->right = constructBST(nums, m+1, r);

    return tmp;
}

T* Balance(T* t) {
    /**  using auxiliary space */
    // Step 1: [Write out tree to a vector in-order traversal] 
    // Step 2: recursively construct the tree by using middle of
    //          vector as the root node
    
    vector<int> inorder_seq;
    writeInorderSequence(t, inorder_seq);
    return constructBST(inorder_seq, 0, inorder_seq.size()-1);
}


int main() {
    return 0;
}