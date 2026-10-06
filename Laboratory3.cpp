#include <iostream>
#include <chrono>
#include <random>
#include <vector>

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

double benchInsertBefore(int n, int k, std::mt19937& gen){
    SinglyList benchList;
    fillRandom(benchList, n, gen);
    auto target = benchList.findNode(n-1);

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
    auto target = benchList.findNode(n-1);

    auto start = Clock::now();

    for (int i = 0; i < k; i++) {
        benchList.insertAfter(target, 100);
    }

    auto end = Clock::now();
    double ns = std::chrono::duration<double, std::nano>(end - start).count();
    return ns/k;
}

int main() {



    return 0;
}
