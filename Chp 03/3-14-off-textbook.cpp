#include <iostream>
#include <vector>
using namespace std;

/**
 * Singly Linked Lists merging 
 *      Iterative
 *      Recursive solution
 */

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int n) : val(n), next(nullptr) {} 
};

void InsertAtHead(ListNode* &head, int val) {
    ListNode* newNode = new ListNode(val);
    newNode->next = head;
    head = newNode;
}

void PrintSinglyLinkedList(ListNode* head) {
    if (head == nullptr) {
        cout << endl;
        return;
    }
    cout << head->val << " ";
    PrintSinglyLinkedList(head->next);
}

void DestroyLinkedList(ListNode* &head) {
    if (head == nullptr) return;
    DestroyLinkedList(head->next);
    delete head;
    head = nullptr;
}

ListNode* CreateLinkedListUsingVector(vector<int> ll_vector) {
    reverse(ll_vector.begin(), ll_vector.end());
    ListNode* head = nullptr;
    ListNode* newNode = nullptr;
    for (int val: ll_vector) {
        newNode = new ListNode(val);
        InsertAtHead(head, val);
    }

    return head;
}

ListNode* MergeTwoLinkedList(ListNode* v1, ListNode* v2) {
    /**
     * Iterative solution 
     */
    if (v1 == nullptr && v2 == nullptr) return nullptr;
    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    while(v1 && v2) {
        if (v1->val < v2->val) {
            if (!head) head = v1;
            else tail->next = v1;
            tail = v1;
            v1 = v1->next;
        } else {
            if (!head) head = v2;
            else tail->next = v2;
            tail = v2;
            v2 = v2->next;
        }
    }

    if (v1 != nullptr) {
        if (!head) head = v1;
        else tail->next = v1;
    } 
    
    if (v2 != nullptr) {
        if (!head) head = v2;
        else tail->next = v2;
    }

    return head;

}

ListNode* MergeTwoLinkedListRecursive(ListNode* v1, ListNode* v2, ListNode* &head, ListNode* &tail) {
    /**
     * Recursive solution 
     */
    if (!v1 && !v2) return head;
    
    if (v1 && !v2) {
        if (head == nullptr) head = v1;
        else tail->next = v1;
        return head;
    }

    if (!v1 && v2) {
        if (head == nullptr) head = v2;
        else tail->next = v2;
        return head;
    } 

    if (v1->val < v2->val) {
        if (head == nullptr) head = v1;
        else tail->next = v1;
        tail = v1;
        v1 = v1->next;
        head = MergeTwoLinkedListRecursive(v1,v2,head,tail);
    } else {
        if (head == nullptr) head = v2;
        else tail->next = v2;
        tail = v2;
        v2 = v2->next;
        head = MergeTwoLinkedListRecursive(v1,v2,head,tail);
    }

    return head;
}

ListNode* LeetCodeMergeTwoLinkedListRecursive(ListNode* list1, ListNode* list2) {
    if (!list1 || !list2) {
        return list1 ? list1 : list2;
    }

    if (list1->val > list2->val) {
        swap(list1, list2);
    }

    list1->next = LeetCodeMergeTwoLinkedListRecursive(list1->next, list2);
    return list1;
}


int main() {

    ListNode* mySinglyLinkedList1 = CreateLinkedListUsingVector({1,2,5});
    ListNode* mySinglyLinkedList2 = CreateLinkedListUsingVector({1,3,4});
    cout << "First Linked List: \t";
    PrintSinglyLinkedList(mySinglyLinkedList1); 

    cout << "Second Linked List: \t";
    PrintSinglyLinkedList(mySinglyLinkedList2);

    ListNode* h = nullptr;
    ListNode* t = nullptr;
    ListNode* head = MergeTwoLinkedListRecursive(mySinglyLinkedList1, mySinglyLinkedList2, h, t);

    cout << "Merged Linked List: \t";
    PrintSinglyLinkedList(head);

    DestroyLinkedList(head);


    return 0;
}