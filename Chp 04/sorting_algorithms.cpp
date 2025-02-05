#include <iostream>
#include <vector> 
#include <queue> 
#include <cassert>
using namespace std;


void InsertionSort(vector<int> &arr) {
    for (int i = 1; i < arr.size(); i++ ) {
        int j = i;  
        while (j > 0 && arr[j] < arr[j-1]) {
            // SWAP elements
            int cur = arr[j];
            arr[j] = arr[j-1];
            arr[j-1] = cur;

            j--;
        }
    }
}

void SelectionSort(vector<int> &arr) {
    for (int i = 0; i < arr.size(); i++) {
        int currMinIndex = i;
        for (int j = i; j < arr.size(); j++) {
            if (arr[j] < arr[currMinIndex])
                currMinIndex = j;
        }
        
        // swap
        int curMin = arr[currMinIndex];
        arr[currMinIndex] = arr[i];
        arr[i] = curMin;
    }
}

void MergeWithQueue(vector<int> &arr, int l, int m, int r) {
    int n1 = (m - l) + 1;
    queue<int> q1;
    for (int i = 0; i < n1; i++)
        q1.push(arr[l + i]);

    int n2 = (r - m);
    queue<int> q2;
    for (int j = 0; j < n2; j++)
        q2.push(arr[m + 1 + j]);            // Coorected index from `M + J` to `M + J + 1`

    int k = l;
    while (!q1.empty() && !q2.empty()) {
        if (q1.front() < q2.front()) {
            arr[k] = q1.front();
            q1.pop();
        k++;
        } else {
            arr[k] = q2.front();
            q2.pop();
        k++;
        }

    }

    while(!q1.empty()) {
        arr[k] = q1.front();
        q1.pop();
        k++;
    }

    while(!q2.empty()) {
        arr[k] = q2.front();
        q2.pop(); 
        k++;
    }
}

void Merge(vector<int> &arr, int l, int m, int r) {
    int n1 = (m - l) + 1;
    int n2 = (r - m); 

    vector<int> left;
    vector<int> right;

    for (int i = 0; i < n1; i++)
        left.push_back(arr[ l + i ]);
    for (int j = 0; j < n2; j++)
        right.push_back(arr[ m + 1 + j ]);

    int i = 0, j = 0, k = l;
    while(i < n1 && j < n2) {
        if (left[i] < right[j]) {
            arr[k] = left[i];
            i++; 
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while( i < n1 ) {
        arr[k] = left[i];
        i++; k++;
    }

    while( j < n2 ) {
        arr[k] = right[j];
        j++; k++;
    }
}   

void MergeSort(vector<int> &arr, int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        MergeSort(arr, l, m);
        MergeSort(arr, m + 1, r);
        // Merge(arr, l, m, r);
        MergeWithQueue(arr, l, m, r);
    }
}

void MergeSortWrapper(vector<int> &arr) {
    if (!arr.empty()) {
        MergeSort(arr, 0, arr.size() - 1);
    }
}


int partition(vector<int> &arr, int low, int high){
    int pivot = high;
    int firstHigh = low; 
    for (int i = low; i < high; i++) {
        if (arr[i] < arr[pivot]) {
            swap(arr[i], arr[firstHigh]);
            firstHigh++;
        }
    }
    swap(arr[pivot], arr[firstHigh]);
    return firstHigh;
}

void QuickSort(vector<int> &arr, int low, int high) {
    if (low < high) {
        int p = partition(arr, low, high);
        QuickSort(arr, low, p-1);
        QuickSort(arr, p+1, high);
    }
}

void QuickSortWrapper(vector<int> &arr) {
    if (!arr.empty()) {
        QuickSort(arr, 0, arr.size()-1);
    }
}

void RunTests(void (*sortFunc)(vector<int>&), const string &sortName) {
    cout << "Sorted by " << sortName << endl;

    vector<vector<int>> testCases = {
        {}, // Test case 1: Empty array
        {5}, // Test case 2: Single element
        {1, 2, 3, 4, 5}, // Test case 3: Already sorted
        {5, 4, 3, 2, 1}, // Test case 4: Reverse sorted
        {4, 2, 5, 1, 3}, // Test case 5: Random order
        {4, 4, 2, 2, 5, 5, 1, 1, 3, -3} // Test case 6: Duplicates
    };

    vector<vector<int>> expectedResults = {
        {}, // Expected result for test case 1
        {5}, // Expected result for test case 2
        {1, 2, 3, 4, 5}, // Expected result for test case 3
        {1, 2, 3, 4, 5}, // Expected result for test case 4
        {1, 2, 3, 4, 5}, // Expected result for test case 5
        {-3, 1, 1, 2, 2, 3, 4, 4, 5, 5} // Expected result for test case 6
    };

    for (int i = 0; i < testCases.size(); ++i) {
        sortFunc(testCases[i]);
        cout << "Test case " << i + 1 << ": ";
        if (testCases[i] == expectedResults[i]) {
            cout << "PASSED" << endl;
        } else {
            cout << "FAILED" << endl;
            cout << "  Expected: ";
            for (int num : expectedResults[i]) cout << num << " ";
            cout << endl;
            cout << "  Got:      ";
            for (int num : testCases[i]) cout << num << " ";
            cout << endl;
        }    
    }
}

int main() {
    RunTests(InsertionSort, "Insertion Sort");
    RunTests(SelectionSort, "Selection Sort");
    RunTests(MergeSortWrapper, "Merge Sort");
    RunTests(QuickSortWrapper, "Quick Sort"); // TLE 

    cout << "All tests completed!" << endl;
    return 0;
}