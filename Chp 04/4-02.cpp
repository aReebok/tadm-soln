#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;


pair<int,int> maximumDifference(vector<int> nums) {
    /**
     * Problem A. 
     * O(n) time complexity: given unsorted array,
     * find the pair x,y with maximum difference
     */
    if (nums.size() < 2) return make_pair(-1,-1);

    int curr_min = nums[0], curr_max = nums[0];
    int max_diff = 0;
    for (int y = 1; y < nums.size(); y++) {
        curr_min = min(curr_min, nums[y]);
        curr_max = max(curr_max, nums[y]);
        max_diff = max(max_diff, curr_max - curr_min);
    }

    return make_pair(curr_min, curr_max);
}

pair<int,int> maximumDifferenceSort(vector<int> nums) {
    /**
     * Problem B. 
     * O(1) time complexity: given sorted array,
     * find the pair x,y with maximum difference
     */
    return make_pair(nums[0], nums[nums.size()-1]);
}


pair<int,int> minimumDifferenceSort(vector<int> nums) {
    /**
     * Problem D.
     * given a Sorted array, find the pair of x and y
     * that minimizes |y-x| where x!=y. The algorithm must
     * run in O(n) // 3 3 6 8 13 19
     */

    if (nums.size() < 2) return make_pair(-1,-1);
    int _left = nums[0];
    int min_diff = INT_MAX;
    int min_r_i = 0;
    int i = 0;
    while ( i < nums.size()) {
        while (nums[i] == _left ) i++;
        if (min_diff > nums[i] - _left) {
            min_diff = nums[i] - _left;
            min_r_i = i;
        }
        _left = nums[i];
        i++;
    }

    return min_diff == INT_MAX ? make_pair(-1,-1) : \
                                 make_pair(nums[min_r_i-1], nums[min_r_i]);
}

pair<int,int> minimumDifference(vector<int> nums) {
    /**
     * Problem C.
     * given an Unsorted array, find the pair of x and y
     * that minimizes |y-x| where x!=y. The algorithm must
     * run in O(nlogn)
     */
    sort(nums.begin(), nums.end());
    return minimumDifferenceSort(nums);
}


int main() {
    vector<int> unsorted_input {6,13,19,3,8}; 
    vector<int> sorted_input = {6,13,19,3,8};
    sort(sorted_input.begin(), sorted_input.end());
    pair<int, int> solution = minimumDifference(unsorted_input);
    // pair<int, int> solution = minimumDifferenceSort(sorted_input);
    cout << "Solution: [" << solution.first << ", " << solution.second << "]" << endl;
    return 0;
}