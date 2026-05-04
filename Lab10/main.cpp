#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <queue>
#include <condition_variable>

using namespace std;

// -------------------- TASK 2 --------------------
int counter = 0;

// -------------------- TASK 3 --------------------
mutex mtx;

// -------------------- TASK 5 --------------------
class SafeQueue {
private:
    queue<int> q;
    mutex m;
    condition_variable cv;
    const int MAX_SIZE = 5;

public:
    void enqueue(int value) {
        unique_lock<mutex> lock(m);

        cv.wait(lock, [this]() { return q.size() < MAX_SIZE; });

        q.push(value);
        cout << "Produced: " << value << endl;

        cv.notify_all();
    }

    int dequeue() {
        unique_lock<mutex> lock(m);

        cv.wait(lock, [this]() { return !q.empty(); });

        int value = q.front();
        q.pop();

        cout << "Consumed: " << value << endl;

        cv.notify_all();
        return value;
    }
};

int main() {

    // -------------------- TASK 1 --------------------
    cout << "Task 1:\n";

    vector<thread> threads1;

    for (int i = 1; i <= 3; i++) {
        threads1.emplace_back([i]() {
            int result = i * i;
            cout << "Thread " << i << ": " << result << endl;
        });
    }

    for (auto& t : threads1) t.join();

    // -------------------- TASK 2 --------------------
    cout << "\nTask 2 (Data Race):\n";

    vector<thread> threads2;

    for (int i = 1; i <= 3; i++) {
        threads2.emplace_back([i]() {
            counter += i;
            cout << "Thread " << i << " counter: " << counter << endl;
        });
    }

    for (auto& t : threads2) t.join();

    // -------------------- TASK 3 --------------------
    cout << "\nTask 3 (With mutex):\n";

    counter = 0;
    vector<thread> threads3;

    for (int i = 1; i <= 3; i++) {
        threads3.emplace_back([i]() {
            lock_guard<mutex> lock(mtx);
            counter += i;
            cout << "Thread " << i << " counter: " << counter << endl;
        });
    }

    for (auto& t : threads3) t.join();

    // -------------------- TASK 4 --------------------
    cout << "\nTask 4 (Deadlock demo):\n";

    mutex m1, m2;

    thread t1([&]() {
        lock_guard<mutex> lock1(m1);
        this_thread::sleep_for(chrono::milliseconds(100));
        lock_guard<mutex> lock2(m2);
        cout << "Thread 1 done\n";
    });

    thread t2([&]() {
        lock_guard<mutex> lock2(m2);
        this_thread::sleep_for(chrono::milliseconds(100));
        lock_guard<mutex> lock1(m1);
        cout << "Thread 2 done\n";
    });

    t1.join();
    t2.join();

    // -------------------- TASK 5 --------------------
    cout << "\nTask 5 (Producer-Consumer):\n";

    SafeQueue sq;

    thread producer([&]() {
        for (int i = 1; i <= 10; i++) {
            sq.enqueue(i);
        }
    });

    thread consumer([&]() {
        for (int i = 1; i <= 10; i++) {
            sq.dequeue();
        }
    });

    producer.join();
    consumer.join();

    return 0;
}