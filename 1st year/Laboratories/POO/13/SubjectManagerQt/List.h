#pragma once
#include <cstddef>

using namespace std;

template <typename T> class Node {
public:
    T* data;
    Node<T>* prev;
    Node<T>* next;

    Node() : data{nullptr}, prev{this}, next{this} {}

    Node(const T* data, Node<T>* prev, Node<T>* next) : data{new T(*data)}, prev{prev}, next{next} {}

    ~Node() { delete data; }
};

template <typename T> class ListIterator {
    Node<T>* node;
public:
    /**
     * @brief ListIterator represents the iterator for the custom list
     * @param node
     */
    ListIterator(Node<T>* node) : node{node} {}

    T& operator*() {
        return *node->data;
    }

    ListIterator<T>& operator++() {
        node = node->next;
        return *this;
    }

    bool operator==(const ListIterator<T>& other) {
        return node->data == other.node->data;
    }

    bool operator!=(const ListIterator<T>& other) {
        return !operator==(other);
    }
};

template <typename T> class List {
    size_t dim;
    Node<T>* root;
public:
    /**
     * @brief List represents a general item container implemented using a doubly linked list
     */
    List() : dim{0}, root{new Node<T>{}} {}

    /**
     * @brief List copy constructor
     * @param old
     */
    List(const List& old) : dim{0}, root{new Node<T>{}} {
        for (const T& item : old) {
            push_back(item);
        }
    }

    ~List() {
        Node<T>* temp;
        Node<T>* curr = root->next;
        while (curr != root) {
            temp = curr;
            curr = curr->next;
            delete temp;
        }
        delete root;
    }

    /**
     * @brief operator []
     * @param index
     * @return
     */
    T& operator[](const size_t index) const {
        size_t i = 0;
        Node<T>* curr = root->next;
        while (i < index % dim) {
            curr = curr->next;
            ++i;
        }
        return *curr->data;
    }

    /**
     * @brief swap
     * @param i1
     * @param i2
     */
    void swap(const size_t i1, const size_t i2) {
        size_t i = 0;
        Node<T>* n1 = nullptr;
        Node<T>* n2 = nullptr;
        Node<T>* curr = root->next;
        while (i < dim) {
            if (i1 % dim == i) n1 = curr;
            if (i2 % dim == i) n2 = curr;
            curr = curr->next;
            ++i;
        }
        T* aux = n1->data;
        n1->data = n2->data;
        n2->data = aux;
    }

    /**
     * @brief push_back adds an element to the end of the list
     * @param e the element to be added
     */
    void push_back(const T& e) {
        dim += 1;
        Node<T>* head = root;
        Node<T>* tail = root->prev;
        Node<T>* node = new Node<T>{&e, tail, head};
        tail->next = head->prev = node;
    }

    /**
     * @brief pop_back
     */
    void pop_back() {
        if (dim == 0) return;
        dim -= 1;
        Node<T>* head = root;
        Node<T>* tail = root->prev;
        Node<T>* new_tail = root->prev->prev;
        delete tail;
        head->prev = new_tail;
        new_tail->next = head;
    }

    /**
     * @brief size returns the length of the list
     * @return element count
     */
    size_t size() { return dim; }
    size_t size() const { return dim; }

    /**
     * @brief begin
     * @return
     */
    ListIterator<T> begin() const { return ListIterator<T>{root->next}; }

    /**
     * @brief end
     * @return
     */
    ListIterator<T> end() const { return ListIterator<T>{root}; }
};
