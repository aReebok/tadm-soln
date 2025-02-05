/**
 * 
 * Given two binary search trees, merge them into one Doubly Linked List.
 * First implement ONE BST to one sorted doubly linked list.
 *      1. Print In Order
 *      2. linkedlist printer front and back traversal
 *      3. insert in tree
 *      4. implement BST to LinkedList
 */

#include <iostream>
#include <queue>
#include <thread>  // For sleep_for
#include <chrono>  // For seconds

using namespace std;

struct treenode {
    int val;
    treenode* left;
    treenode* right;
    treenode(int x) : val(x), left(nullptr), right(nullptr) {};
};

treenode* InsertBST(treenode* root, int val) {
    if (root == nullptr) {
        treenode* newNode = new treenode(val);
        return newNode;
    }

    if (root->val > val) { // left subtree
        root->left = InsertBST(root->left, val);
    } else { // right subtree
        root->right = InsertBST(root->right, val);
    }

    return root;
} 

void destroyTree(treenode* root) {
    if (root == nullptr) return;
    destroyTree(root->left);
    destroyTree(root->right);
    delete root;
    root = nullptr;
}

void destroyLL(treenode* root) {
    if (root == nullptr) return;
    destroyLL(root->right);
    delete root;
    root = nullptr;
}


void PrintInOrderHelper(treenode* root){
    if(root == nullptr) return;
    PrintInOrderHelper(root->left);
    cout << root->val << " ";
    PrintInOrderHelper(root->right);
}

void PrintInOrder(treenode* root) {
    cout << "Printing In Order: [ ";
    PrintInOrderHelper(root);
    cout << "]" << endl;
}

int PrintBSTLevelOrder(treenode* root) {
    /** prints the BST in level order and returns the height of the tree */
    int height = 0;
    int currLevelSize = 0;
    if (root == nullptr) return height;
 
    cout << "Printing In Level: [ ";
    queue<treenode*> tree_q;
    tree_q.push(root);
    while(!tree_q.empty()) {
        height += 1;
        currLevelSize = tree_q.size();

        for (int i = 0; i < currLevelSize; i++) {
            treenode* curr = tree_q.front();
            tree_q.pop();
            cout << curr->val << " ";
            if (curr->left != nullptr) tree_q.push(curr->left);
            if (curr->right != nullptr) tree_q.push(curr->right);
        }
    }
    cout << "]" << endl;

    return height;
    
}

void PrintLinkedListFromHead(treenode* head) {
    cout << "*Inorder LL Print: ";
    treenode* temp = head;
    cout << "[ ";
    while (temp != nullptr) {
        cout << temp->val << " ";
        temp = temp->right;
    }

    cout << "]" << endl;
}

void PrintLinkedListFromTail(treenode* tail) {
    cout << "*Reverse LL Print: ";
    treenode* temp = tail;
    cout << "[ ";
    while (temp != nullptr) {
        cout << temp->val << " ";
        temp = temp->left;
    }

    cout << "]" << endl;
}

void TwoBSTtoDoublyLinkedList(treenode* root1, treenode* root2, treenode* &head, treenode* tail) {
    /**
     * 
     * THIS SOLUTION DOES NOT WORK... 
     * 
     * BRUTE FORCE way to do this is to insert all nodes of root2 into root1
     *      ISSUES is that it can result in an imbalanced tree
     *          We also make A LOT of redundant, recursive calls here
     *  
     * SOLN: one run by using 3 unique basecases
     *  1. when root1 and root2 == nullptr
     *  2. when root1 is NOT    null AND [either root2 is     null  or root1.val comes before root2.val]
     *  2. when root1 is either null  OR [       root2 is NOT null AND root1.val comes  after root2.val]
     */

    if (root1 == nullptr && root2 == nullptr) return;
    if (root1 != nullptr && (root2 == nullptr || root1->val < root2->val)) {
        // set root1 as the next element in tail    
        TwoBSTtoDoublyLinkedList(root1->left, root2, head, tail);
        if (head == nullptr) head = tail = root1;
        else {
            tail->right = root1;
            root1->left = tail;
            tail = root1;
        }

        TwoBSTtoDoublyLinkedList(root1->right, root2, head, tail);
    } else { 
        // either root1 value is NULL
        //     OR root2 value is NOT null AND root1.val is greater than root2.val
        // In either way we need to set root2 as the next elemenet in the tail
        TwoBSTtoDoublyLinkedList(root1, root2->left, head, tail);
        if (head == nullptr) head = tail = root2;
        else {
            tail->right = root2;
            root2->left = tail;
            tail = root2;
        }
        
        TwoBSTtoDoublyLinkedList(root1, root2->right, head, tail);
    }

}


void FlattenBST(treenode* root, treenode* &head, treenode* &tail) {
    if (root == nullptr) return;
    FlattenBST(root->left, head, tail);
    /* 
        Do work here to convert current inorder node to 
    */
    if (head == nullptr) {
        head = root;
    } else {
        tail->right = root;
        root->left = tail;
    }

    tail = root;
    FlattenBST(root->right, head, tail);
}

treenode* MergeTwoDoublyLinkedList(treenode* list1, treenode* list2) {
    if (!list1 || !list2) {
        return list1 ? list1 : list2;
    }

    if (list1->val > list2->val) {
        swap(list1, list2);
    }

    treenode* next = MergeTwoDoublyLinkedList(list1->right, list2);
    list1->right = next;
    next->left = list1;
    return list1;  
}

treenode* TwoBSTtoDoublyLinkedList(treenode* list1, treenode* list2) {
    treenode* head1 = nullptr;
    treenode* tail1 = nullptr;
    treenode* head2 = nullptr;
    treenode* tail2 = nullptr;
    FlattenBST(list1, head1, tail1);
    FlattenBST(list2, head2, tail2);
    return MergeTwoDoublyLinkedList(head1, head2);
}

treenode* GetTail(treenode* ll) {
    while (ll != nullptr && ll->right != nullptr) {
        ll = ll->right;
    } 
    
    return ll;
}



int main() {
    treenode* root = nullptr;
    root = InsertBST(root, 3);
    root = InsertBST(root, 1);
    root = InsertBST(root, 7);
    root = InsertBST(root, 5);
    root = InsertBST(root, 10);

    treenode* root2 = nullptr;
    root2 = InsertBST(root2, 6);
    root2 = InsertBST(root2, 2);
    root2 = InsertBST(root2, 4);
    root2 = InsertBST(root2, 0);
    root2 = InsertBST(root2, 9);
    root2 = InsertBST(root2, 8);
    root2 = InsertBST(root2, 11);


    /* Printing in order */    
    PrintInOrder(root);
    /* Printing in order */    
    PrintInOrder(root2);

    // Merge 2BST into one Doubly Linked List:
    treenode* dllhead = TwoBSTtoDoublyLinkedList(root, root2);
    // /* print linked list forward*/
    PrintLinkedListFromHead(dllhead);
    // /* print linked list backwards*/
    PrintLinkedListFromTail(GetTail(dllhead));

    cout << "\nDestroying linked list and cleaning up... " << endl;
    destroyLL(dllhead);
    PrintLinkedListFromHead(dllhead);

}