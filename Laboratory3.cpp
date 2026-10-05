#include <iostream>

/* --------------------------------------------- */

struct Node;

/* --------------------------------------------- */

class SimplyList {
    private:
        Node* head;

    public:
        SimplyList(): head(nullptr) {}
};

struct Node {
    int data;
    Node* next;

    Node(int data_): data(data_), next(nullptr) {}
};

int main() {



    return 0;
}
