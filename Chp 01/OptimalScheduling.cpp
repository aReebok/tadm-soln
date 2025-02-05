#include <iostream>
#include <vector>


/*
* The Greedy Approach is to accept the first job and then find the next available role
* but we might miss other roles if the first job is way too long to begin with.
*
* Instead solution that is optimized and works is starting with the film that ends the earliest:
* the second pair of start and end time is the smallest. Go off of that in finding the next movie that starts 
* after but ends the earliest. 
*
* SOLUTION: Using a sorted vector of pairs, sorted by the second pair (ending time). 
* https://leetcode.com/discuss/interview-question/124748/maximize-the-number-of-tv-shows-that-can-be-watched
* 
*/

bool sortBySecondPair(std::pair<int,int> a, std::pair<int,int> b) {
    return a.second < b.second;
}

std::vector<std::pair<int,int>> OptimalScheduling(std::vector<std::pair<int,int>> schedule) {
    // sort the scheduling based on which roles end first
    std::sort(schedule.begin(), schedule.end(), sortBySecondPair);
    std::vector<std::pair<int,int>> op_sch;

    // set the first event in the sorted schedule as the starting point
    op_sch.push_back(schedule[0]);
    int prev = 0;
    for (int i = 1; i < schedule.size(); i++) {
        if (schedule[prev].second < schedule[i].first) {
            op_sch.push_back(schedule[i]);
            prev = i;
        }
    } 
    return op_sch;
}

void printVectorofPairs(std::vector<std::pair<int,int>> v) {
    std::cout << "[  ";
    for(auto pr: v)
    {
        // Print the element
        std::cout << "{";
        std::cout << pr.first << " , " << 
                pr.second;
        std::cout << "}  ";
    } 
    std::cout << "]\n";
}

int main() {
    std::vector<std::pair<int,int>> schedule = {{8, 11}, {4, 7}, {1, 3}, {3, 5}, {5, 9}, {0, 6}, {3, 8}, {6, 10}};
    printVectorofPairs(schedule);
    printVectorofPairs(OptimalScheduling(schedule));
}