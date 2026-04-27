#include <iostream>
#include <list>
#include <vector>
#include <deque>
#include <set>
#include <map>
#include <algorithm>
#include <string>
#include <ctime>

using namespace std;

bool isOdd(int n) {
    return n % 2 != 0;
}

bool compareLength(const string& a, const string& b) {
    return a.length() < b.length();
}

class AddPrice {
    double rate;
public:
    AddPrice(double r) : rate(r) {}

    void operator()(double& price) {
        price += price * rate;
    }
};

class WithinRange {
    int minVal, maxVal;
public:
    WithinRange(int minV, int maxV) : minVal(minV), maxVal(maxV) {}

    bool operator()(int x) {
        return x >= minVal && x <= maxVal;
    }
};

int main() {

    srand(time(0));

    cout << "Task 1:\n";
    list<int> lst;

    for (int i = 0; i < 20; i++)
        lst.push_back(rand() % 100);

    lst.remove_if(isOdd);

    for (int x : lst) cout << x << " ";
    cout << "\n\n";

    cout << "Task 2:\n";
    vector<string> names = {"Anna", "Oleh", "Maksym", "Ira", "Kateryna"};

    sort(names.begin(), names.end(), compareLength);

    for (auto n : names) cout << n << " ";
    cout << "\n\n";

    cout << "Task 3:\n";
    deque<double> prices = {10.5, 20.0, 30.5};

    for_each(prices.begin(), prices.end(), AddPrice(0.2));

    for (auto p : prices) cout << p << " ";
    cout << "\n\n";

    cout << "Task 4:\n";
    set<int> s = {1, 5, 10, 15, 20, 25};

    int count = count_if(s.begin(), s.end(), WithinRange(5, 20));

    cout << "Count: " << count << "\n\n";

    cout << "Task 5:\n";
    map<string, int> warehouse = {
        {"apple", 50},
        {"banana", 120},
        {"orange", 200}
    };

    for_each(warehouse.begin(), warehouse.end(), [](pair<string,int> item){
        if (item.second > 100)
            cout << item.first << " ";
    });
    cout << "\n\n";

    cout << "Task 6:\n";
    vector<int> nums = {1, -2, 3, -4, 5};

    replace_if(nums.begin(), nums.end(), [](int x){
        return x < 0;
    }, 0);

    for (int x : nums) cout << x << " ";
    cout << "\n\n";

    cout << "Task 7:\n";
    vector<int> v = {1,2,3,4,5};

    int sum = 0;
    for_each(v.begin(), v.end(), [&sum](int x){
        sum += x;
    });

    double avg = (double)sum / v.size();

    cout << "Sum: " << sum << " Avg: " << avg << "\n\n";

    cout << "Task 8:\n";
    string text = "Programming";

    int vowels = count_if(text.begin(), text.end(), [](char c){
        string v = "aeiouAEIOU";
        return v.find(c) != string::npos;
    });

    cout << "Vowels: " << vowels << "\n";

    return 0;
}