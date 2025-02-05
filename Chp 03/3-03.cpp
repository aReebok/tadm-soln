// Linear time algorithm to REVERSE singly linkedlist
#include <iostream>
#include <vector>
using namespace std;

struct Node{
    int item;
    Node* next = nullptr;
};

Node* RecursiveReverseLinkedList(Node* head) {
    if (head == nullptr || head->next == nullptr) 
        return head;

    // reverse the rest of the list: 
    Node* revlisthead = RecursiveReverseLinkedList(head->next);
    // rev list is the rest of the list reversed, attach to head...
    head->next->next = head;
    head->next = nullptr;
    return revlisthead;
}

Node* IterativeReverseLinkedList(Node* head) {
    Node* tmp;
    Node* prev = NULL;
    Node* curr = head;
    while (curr != nullptr) {
        tmp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = tmp;
    }
    return prev;
}

void deleteLinkedList(Node* head) {
    while (head != nullptr) {
        Node* tempHead = head;
        head = head->next;
        delete tempHead;
    }
}

Node* createReversedLinkedList(vector<int> v) {
    Node* head = nullptr;
    for (int e: v) {
        Node* tempNode = new Node;
        tempNode->item = e;
        tempNode->next = head;
        head = tempNode;
    }
    return head;
} 

void printLinkedList(Node* head) {
    Node* tempHead = head;
    cout << " [ ";
    while(tempHead != nullptr) {
        cout << tempHead->item << ", ";
        tempHead = tempHead->next;
    }
    cout << " ] " << endl;
}

int main() {
    vector<int> vec = {1,2,3,4,5,6,7};
    Node* linkedList = createReversedLinkedList(vec);
    printLinkedList(linkedList);
    linkedList = IterativeReverseLinkedList(linkedList);
    printLinkedList(linkedList);    
    linkedList = RecursiveReverseLinkedList(linkedList);
    printLinkedList(linkedList);
    deleteLinkedList(linkedList);
}