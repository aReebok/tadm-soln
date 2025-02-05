#include <iostream>
#include <vector>
using namespace std;

/**
 * file:///Users/areebakhan/Desktop/p10137.pdf
 * This program 
 */

vector<int> convertToIntSpendings(vector<double> spendings) {
    vector<int> largePrices;
    int convertFactor = pow(10, 4);
    for (auto s : spendings) 
        largePrices.push_back(s*convertFactor);

    return largePrices;
} 

double calculateExchange(vector<int> spendings) {
    // add up all spending, average the cost
    int spendingSum = 0;
    for (auto s: spendings) spendingSum += s;

    // Round and calculate average spending.
    spendingSum = round(spendingSum / pow(10, 2)) * pow(10, 2);
    double averageSpending = round((spendingSum / spendings.size()) / pow(10,2)) * pow(10, 2);

    // now if each trip, there is someone that spent over, the averageSpending,
    //      they need to BE PAID back. 
    // Otherwise, we can also calculate if there's people that spent less,
    //      they then need to PAY back
    double exchangeTotal = 0;

    for (auto s: spendings)
        if (s > averageSpending) 
            exchangeTotal += s - averageSpending;

    return exchangeTotal / pow(10, 4); 
}

vector<int> getTripSpendings() {
    int trips;
    cin >> trips;

    vector<double> spendings;
    double t;

    while (trips) {
        cin >> t;
        spendings.push_back(t);
        trips--;
    }

    return convertToIntSpendings(spendings);
}

int main() {
    vector<int> groupSpendings = getTripSpendings();
    double requiredExchange = calculateExchange(groupSpendings);
    cout << "$" << requiredExchange << endl;
}