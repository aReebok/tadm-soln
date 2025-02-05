/**
 * Give an efficient algo if anagram for letters only
 * 
 */

#include<iostream>
#include<unordered_map>
#include<string>
using namespace std;

bool isAnagram2(string x, string y) {
    if (x.size() != y.size())
        return false;

    int arr[26] = {0}; // our make-shift memory eff map.
    for (int i = 0;  i < x.size(); i++) {
        arr[x[i] - 'a']++; 
        arr[y[i] - 'a']--;
    }

    // now check all values in arr are false
    for (char c: arr) {
        if (c != 0) return false;
    }

    return true;
}   

bool isAnagram(string X, string Y) { 
    /** Questions to ask are, is the anagram contain only letters? Do spaces exist in inputs and should they be ignored?
     * Try using a single arrray of 26, instantiated to {0} and a single for loop 
     */
    if (X.size() != Y.size()) return 0;
    unordered_map<char, int> xmap;
    for (char c: X) {
        xmap[c]++;
    }

    for (char c: Y) {
        if (xmap.find(c) == xmap.end()) 
            return 0;

        xmap[c]--;
        if (xmap[c] == 0) 
            xmap.erase(c);
    }
    return 1;
}

int main() {
    string x = "poopie";
    string y = "listen";
    string z = "silent";
    cout << "Are " << x << " and " << y << " anagrams?: " << isAnagram(x,y) << endl;
    cout << "Are " << z << " and " << y << " anagrams?: " << isAnagram(z,y) << endl;
    return -1;
}