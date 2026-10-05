#include <iostream>

/* --------------------------------------------- */



/* --------------------------------------------- */

struct Node {
    int data;
    Node* next;

    Node(int data_): data(data_), next(nullptr) {}
};

class SinglyList {
    private:
        Node* head;

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
};


int main() {



    return 0;
}
