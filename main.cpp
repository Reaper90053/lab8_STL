#include <iostream>
#include <array>
#include <vector>
#include <deque>
#include <string>

using namespace std;

// =======================
// Власний клас
// =======================
class Number {
public:
    int value;

    Number(int v = 0) : value(v) {}

    bool operator<(const Number& other) const {
        return value < other.value;
    }

    bool operator==(const Number& other) const {
        return value == other.value;
    }
};

// Вивід для класу
ostream& operator<<(ostream& os, const Number& n) {
    os << n.value;
    return os;
}

// =======================
// 1. Об'єднання array
// =======================
template <typename T, size_t N1, size_t N2>
array<T, N1 + N2> mergeArrays(const array<T, N1>& a, const array<T, N2>& b) {
    array<T, N1 + N2> result;

    auto it1 = a.begin();
    auto it2 = b.begin();
    auto itRes = result.begin();

    while (it1 != a.end() && it2 != b.end()) {
        if (*it1 < *it2) {
            *itRes = *it1;
            ++it1;
        } else {
            *itRes = *it2;
            ++it2;
        }
        ++itRes;
    }

    while (it1 != a.end()) {
        *itRes = *it1;
        ++it1; ++itRes;
    }

    while (it2 != b.end()) {
        *itRes = *it2;
        ++it2; ++itRes;
    }

    return result;
}

// =======================
// 2. Розбиття vector
// =======================
template <typename T>
void splitVector(const vector<T>& v, vector<T>& even, vector<T>& odd) {
    for (auto it = v.begin(); it != v.end(); ++it) {
        if ((*it) % 2 == 0)
            even.push_back(*it);
        else
            odd.push_back(*it);
    }
}

// =======================
// 3. Паліндром deque
// =======================
template <typename T>
bool isPalindrome(const deque<T>& d) {
    auto left = d.begin();
    auto right = d.end();

    if (right != d.begin()) --right;

    while (left < right) {
        if (!(*left == *right))
            return false;
        ++left;
        --right;
    }
    return true;
}

// =======================
// Вивід контейнера
// =======================
template <typename Container>
void printContainer(const Container& c) {
    for (auto it = c.begin(); it != c.end(); ++it)
        cout << *it << " ";
    cout << endl;
}

// =======================
// MAIN
// =======================
int main() {

    cout << "=== ARRAY (int) ===\n";
    array<int, 3> arr1 = {1, 3, 5};
    array<int, 3> arr2 = {2, 4, 6};

    auto mergedInt = mergeArrays(arr1, arr2);
    printContainer(mergedInt);

    cout << "\n=== ARRAY (double) ===\n";
    array<double, 3> d1 = {1.1, 3.3, 5.5};
    array<double, 3> d2 = {2.2, 4.4, 6.6};

    auto mergedDouble = mergeArrays(d1, d2);
    printContainer(mergedDouble);

    cout << "\n=== ARRAY (custom class) ===\n";
    array<Number, 3> n1 = {Number(1), Number(3), Number(5)};
    array<Number, 3> n2 = {Number(2), Number(4), Number(6)};

    auto mergedClass = mergeArrays(n1, n2);
    printContainer(mergedClass);

    // =======================

    cout << "\n=== VECTOR ===\n";
    vector<int> v = {1,2,3,4,5,6,7,8};

    vector<int> even, odd;
    splitVector(v, even, odd);

    cout << "Even: ";
    printContainer(even);

    cout << "Odd: ";
    printContainer(odd);

    // =======================

    cout << "\n=== DEQUE ===\n";
    deque<int> d = {1, 2, 3, 2, 1};

    if (isPalindrome(d))
        cout << "Palindrome\n";
    else
        cout << "Not palindrome\n";

    // =======================

    cout << "\n=== DEQUE (custom class) ===\n";
    deque<Number> d2_class = {Number(1), Number(2), Number(1)};

    if (isPalindrome(d2_class))
        cout << "Palindrome\n";
    else
        cout << "Not palindrome\n";

    return 0;
}