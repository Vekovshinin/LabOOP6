#include <iostream>
#include <vector>
using namespace std;

class Node {
public:
    int data;
    Node* next;
public:
    Node(int data) {
        this->data = data;
        this->next = nullptr;
    }
};

class List {
public:
    Node* head, * tail;
    int size;

    List() {
        this->head = nullptr;
        this->tail = nullptr;
    }

    ~List() {
        while (head != nullptr) {
            pop_front();
        }
    }

    void pop_front() {
        if (head == nullptr) {
            return;
        }
        if (head == tail) {
            delete tail;
            head = nullptr;
            tail = nullptr;
            return;
        }
        Node* node = head;
        head = node->next;
        delete node;
        size--;
    }

    void push_back(int data) {
        Node* node = new Node(data);
        if (head == nullptr) {
            head = node;
        }
        if (tail != nullptr) {
            tail->next = node;
        }
        tail = node;
        size++;
    }

    void push_front(int data) {
        Node* node = new Node(data);
        node->next = head;
        head = node;
        if (tail == nullptr) {
            tail = node;
        }
        size++;
    }

    void pop_back() {
        if (tail == nullptr) {
            return;
        }
        if (head == tail) {
            delete tail;
            head = tail;
            head = tail = nullptr;
            return;
        }
        Node* node = head;
        for (; node->next != tail; node = node->next);
        node->next = nullptr;
        delete tail;
        tail = node;
        size--;
    }

    Node* getAt(int k) {
        if (k < 0) {
            return nullptr;
        }
        Node* node = head;
        int n = 0;
        while (node && n != k && node->next) {
            node = node->next;
            n++;
        }
        if (n == k) {
            return node;
        }
        else {
            return nullptr;
        }
    }

    void insert(int k, int data) {
        Node* left = getAt(k);
        if (left == nullptr) {
            return;
        }
        Node* right = left->next;
        Node* node = new Node(data);
        left->next = node;
        node->next = right;
        if (right == nullptr) {
            tail = node;
        }
        size++;
    }

    void erase(int k) {
        if (k < 0) return;
        if (k == 0) {
            pop_front();
            return;
        }
        Node* left = getAt(k - 1);
        Node* node = left->next;
        if (node == nullptr) return;
        Node* right = node->next;
        left->next = right;
        if (node == tail) tail = left;
        delete node;
        size--;
    }

    List& operator=(const List& other) {
        if (this == &other) {
            return *this;
        }

        while (head != nullptr) {
            pop_front();
        }

        Node* current = other.head;
        while (current != nullptr) {
            push_back(current->data);
            current = current->next;
        }
        return *this;
    }

    friend ostream& operator<<(ostream& out, const List& l) {
        Node* current = l.head;
        while (current != nullptr) {
            out << current->data << " ";
            current = current->next;
        }
        return out;
    }

    int& operator[](int index) {
        Node* node = getAt(index);
        if (node != nullptr) {
            return node->data;
        }
    }

    int operator()() const {
        return size;
    }

    friend List& operator*(List& l, vector<int> v) {
        if (l.size == v.size()) {
            for (int i = 0; i < l.size; i++) {
                l[i] = l[i] * v[i];
            }
        }
        else {
            cout << "\tСписок и вектор имеют разный размер!" << endl;
        }
        return l;
    }
};

int main() {
    system("chcp 1251 > null");

    List l;
    for (int i = 0; i < 10; i++) {
        l.push_back(rand() % 10);
    }

    for (int i = 0; i < l(); i++) {
        cout << l[i] << " ";
    }

    cout << endl;

    vector<int> v;
    for (int i = 0; i < 10; i++) {
        v.push_back(rand() % 10);
        cout << v[i] << " ";
    }
    cout << endl;

    l = l * v;
    cout << l << endl;

    return 0;
}
