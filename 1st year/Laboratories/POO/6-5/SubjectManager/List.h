#pragma once
#include <cstddef>
#include <vector>
#include <iterator>

using namespace std;

template <typename T> class Node {
public:
    T* data;
    Node<T>* prev;
    Node<T>* next;

    Node() : data{nullptr}, prev{this}, next{this} {}
    Node(const T* data, Node<T>* prev, Node<T>* next) : data{new T(*data)}, prev{prev}, next{next} {}
};

template <typename T> class ListIterator {
    Node<T>* node;
public:
    /**
     * @brief ListIterator represents the iterator for the list
     * @param node
     */
    ListIterator(Node<T>* node) : node{node} {}

    const T& operator*() {
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
    vector<T> iterator;
public:
    /**
     * @brief List represents a general item container implemented using a doubly linked list
     */
    List() : dim{0}, root{new Node<T>{}}, iterator{} {}

    /**
     * @brief operator []
     * @param index
     * @return
     */
    const T& operator[](const size_t index) const {
        size_t i = 0;
        Node<T>* curr = root->next;
        while (i < index) {
            curr = curr->next;
            ++i;
        }
        return *curr->data;
    }

    void swap(const size_t i1, const size_t i2) {
        size_t i = 0;
        Node<T>* n1 = nullptr;
        Node<T>* n2 = nullptr;
        Node<T>* curr = root->next;
        while (i < dim) {
            if (i1 == i) n1 = curr;
            if (i2 == i) n2 = curr;
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
    void push_back(const T& e)  {
        dim += 1;
        Node<T>* head = root;
        Node<T>* tail = head->prev;
        Node<T>* node = new Node<T>{&e, tail, head};
        tail->next = head->prev = node;
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
