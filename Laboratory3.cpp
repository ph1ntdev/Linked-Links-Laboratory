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
};


int main() {

    SinglyList list;

    list.print();
    list.pushFront(1);
    list.pushFront(2);
    list.pushFront(3);
    list.print();

    return 0;
}
