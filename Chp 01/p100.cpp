#include <iostream>
using namespace std;

int algorithm(int n) {
    int cycles = 1;
    while (n != 1) {
        cycles++;
        if (n % 2) n = 3*n + 1;
        else n = n/2;
    }
    return cycles;
}

int algorithmPair (int n1, int n2) {
    int largestCycle = 0;
    for (int i = n1; i <= n2; i++) {
        largestCycle = max(largestCycle, algorithm(i));
    }
    return largestCycle;
}

int main() {
    int in1 = 1;
    int in2 = 10;
    cout << in1 << " " << in2 << " " <<algorithmPair (in1,in2) << endl;
    in1 = 100;
    in2 = 200;
    cout << in1 << " " << in2 << " " <<algorithmPair (in1,in2) << endl;
    in1 = 201;
    in2 = 210;
    cout << in1 << " " << in2 << " " <<algorithmPair (in1,in2) << endl;
    in1 = 900;
    in2 = 1000;
    cout << in1 << " " << in2 << " " <<algorithmPair (in1,in2) << endl;
}