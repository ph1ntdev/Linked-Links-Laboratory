#include <fstream>
#include <iostream>
#include <chrono>
#include <random>

using Clock = std::chrono::steady_clock;

/* --------------------------------------------- */

/*
 */

/* --------------------------------------------- */

struct Node {
    int data;
    Node* next;

    Node(int data_): data(data_), next(nullptr) {}
};

class SinglyList {
    private:
        Node* head;

        Node* findPrevNode(Node* node) const {
            Node* prevNode = head;
            while (prevNode != nullptr && prevNode->next != node) {
                prevNode = prevNode->next;
            }
            return prevNode;
        }

    public:
        SinglyList(): head(nullptr) {}

        ~SinglyList() {
            Node* cur = head;
            while (cur != nullptr) {
                Node* nextNode = cur->next;
                delete cur;
                cur = nextNode;
            }
        }

        void pushFront(int value) {
            Node* newNode = new Node(value);
            newNode->next = head;
            head = newNode;
        }

        void print() const {
            Node* cur = head;
            while (cur != nullptr) {
                std::cout << cur->data << '\n';
                cur = cur->next;
            }
        }

        void insertAfter(Node* node, int value) {
            if (node == nullptr) return;
            Node* newNode = new Node(value);
            newNode->next = node->next;
            node->next = newNode;
        }

        Node* findNode(int index) const {
            if (index < 0) return nullptr;

            int count = 0;
            Node* cur = head;

            while (cur != nullptr && count < index) {
                cur = cur->next;
                count++;
            }
            return cur;
        }

        void insertBefore(Node* node, int value) {
            if (node == nullptr) return;
            if (node == head) {
                pushFront(value);
                return;
            }
            Node* prev = findPrevNode(node);
            if (prev == nullptr) return;

            Node* newNode = new Node(value);
            newNode->next = node;
            prev->next = newNode;
        }
};

void fillRandom(SinglyList& list, int n, std::mt19937& gen) {
    for (int i = 0; i < n; i++) {
        list.pushFront(static_cast<int>(gen()));
    }
}

/*
 * Для тестирования в худшем случае изменить на findNode(n-1)
 * Для тестирования в лучшем случае изменить на findNode(0)
*/

double benchInsertBefore(int n, int k, std::mt19937& gen){
    SinglyList benchList;
    fillRandom(benchList, n, gen);
    auto target = benchList.findNode(0);

    auto start = Clock::now();

    for (int i = 0; i < k; i++) {
        benchList.insertBefore(target, 100);
    }

    auto end = Clock::now();
    double ns = std::chrono::duration<double, std::nano>(end - start).count();
    return ns/k;
}

double benchInsertAfter(int n, int k, std::mt19937& gen) {
    SinglyList benchList;
    fillRandom(benchList, n, gen);
    auto target = benchList.findNode(0);

    auto start = Clock::now();

    for (int i = 0; i < k; i++) {
        benchList.insertAfter(target, 100);
    }

    auto end = Clock::now();
    double ns = std::chrono::duration<double, std::nano>(end - start).count();
    return ns/k;
}

int main() {
//     Тестирование алгоритмов вставки
    std::mt19937 gen(42);
    std::ofstream file("result.csv");
    if (file.is_open()) {
        int size[5] = {100, 1000, 10000, 100000, 1000000};
        file << "n,after_ns,before_ns\n";
        for (int i = 0; i < 5; i++) {
            double iBefore = 0;
            double iAfter = 0;

            for (int j = 0; j < 5; j++) {
                iAfter += benchInsertAfter(size[i], 1000, gen);
                iBefore += benchInsertBefore(size[i], 1000, gen);
            }

            file << size[i] << ',' << iAfter / 5 << ',' << iBefore / 5 << '\n';
        }
    }
    else {
        std::cout << "File was not opened.\n";
    }
    file.close();

    return 0;
}
