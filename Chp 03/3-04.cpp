#include <iostream>
#include <vector>
using namespace std;

// Write an implementation of Stack S that supports S.push(x), S.pop(), S.findmin();

class Stack {
private:
    int size;
    int minimum;
    vector<int> S;
public:
    Stack() : size(0), minimum(INT_MAX)  {}

    int empty() {
        return (size <= 0);
    }

    void push(int n) {
        if (empty()) minimum = n;
        else minimum = min(minimum, n);
        S.push_back(n);
        size++;
    }

    int top() {
        if (empty()) {
            cout << "Warning: Stack underflow!" << endl;
            return -1;
        }
        //cout << S[size-1] << endl;
        return S[size-1];
    }

    void pop() {
        if (empty()) {
            cout << "Warning: Stack underflow!" << endl;
            return;
        }
        if (minimum == top()) {
            minimum = INT_MAX;
            // find next minimum:
            for (int i = 0; i < size-1; i++) minimum = min(minimum, S[i]);
        }
        size--;    
    }


    void printStack() {
        cout << "[ ";
        for (int i = size - 1; i >= 0; i--) {
            cout << S[i] << ", ";
        }
        cout << " ]" << endl;
    }

    int findmin(){
        printStack();
        if (empty()) return -1;
        cout << "curr min: " << minimum << endl; 
        return minimum;
    }

};

int main() {
    Stack s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(0);
    s.findmin();
    s.pop();
    s.top();
    s.findmin();
    s.push(0);
    s.printStack();
    s.findmin();
    s.pop();
    s.pop();
    s.pop();
    s.findmin();
    s.pop();
    s.pop();
    s.pop();
    s.pop();
    s.pop();
    return 0;
}