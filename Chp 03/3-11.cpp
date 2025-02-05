/** Give a dictionary data structure design in which 
 * Search O(1)
 * insertion O(1)
 * deletion O(1)
 * 
 * initialization can take O(n) 
 */

#include <iostream>
#include <vector>
using namespace std;

struct FastDictionary {
    int n;
    vector<int> data;

    FastDictionary(int size) : n(size), data(size+1, 0) {}

    void insert(int n) {
        data[n]++;
    } 

    void remove(int n) {
        data[n]--;
    }

    int search(int n) {
        // return value-pair
        return(data[n]);
    }
};

int main() {
    int n = 10; // Maximum value in the finite set
    FastDictionary dict(n);

    // Insert elements
    dict.insert(5);
    dict.insert(7);

    // Search for elements
    std::cout << "Search 5: " << dict.search(5) << "\n"; // Output: 1 (true)
    std::cout << "Search 3: " << dict.search(3) << "\n"; // Output: 0 (false)

    // Delete an element
    dict.remove(5);
    std::cout << "Search 5 after deletion: " << dict.search(5) << "\n"; // Output: 0 (false)

    return 0;

    /**
     * Expected output
     * Search 5: 1
        Search 3: 0
        Search 5 after deletion: 0
     */
}