#include <iostream>
#include <string>
#include <stack>
using namespace std;

int isCloseParen(char p) {
    return (p == ')');
}

int longestBalancedParen(string s) {
    int balancedParenCount = 0;
    stack<char> st;
    for (char c : s) {
        if (isCloseParen(c)) {
            // check if there is an open paren 
            if (!st.empty()) {
                st.pop();
                balancedParenCount++;
            } // else do nothing and keep going

        } else st.push(c);
    }
    return balancedParenCount*2;
}

int balancedParen(string s){
    stack<char> st;
    for (int i = 0; i < s.size(); i++) {
        if (isCloseParen(s[i])){
            if (st.empty()) return i; 
            else st.pop();
        } else {
            st.push(s[i]);
        }
    }
    if (!st.empty()) return st.size()-1;
    return -1;
}

void testBalancedParen(vector<string> tests) {
    for (string test: tests) {
        int res = balancedParen(test);
        if (res == -1) cout << "Paren \'" << test << "\' is balanced" << endl;
        else cout << "Paren \'"  << test << "\' is NOT balanced @ index " << res << endl;
    } 
}

int main() {
    vector<string> tests = {"((())())()", "(", ")", ")()(", "())"};
    testBalancedParen(tests);

    string longestBalancedParenTest = ")()(())()()))())))("; // return 12
    cout << "Longest Balanced Paren in " << longestBalancedParenTest << " is: " << longestBalancedParen(longestBalancedParenTest) << endl;
}