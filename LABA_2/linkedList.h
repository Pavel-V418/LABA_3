#ifndef LABA2_LINKEDLIST_H
#define LABA2_LINKEDLIST_H

#include <stdexcept>
#include "i_enumerator.h"

template <class T>
class LinkedList {

private:
    struct Node {
        T data; // T здесь используем для хранения объекта, поэтому не ссылка
        Node *next;//

        Node(T value) {
            data = value;
            next = nullptr;
        }
    };

    Node *head;
    Node *tail;
    int length;

public:
    // constructors
    LinkedList(const T *element, int count);
    LinkedList();
    LinkedList(const LinkedList& list);

    // destructor
    ~LinkedList();

    // Decomposition
    const T& get_first() const;
    const T& get_last() const;
    const T& get(int index) const;
    Node* get_head() const;

    LinkedList<T>* get_sub_list(int startIndex, int endIndex); // сл этап

    int get_length() const;

    // Operations
    void append(const T& element); // добавить в конец
    void prepend(const T& element); // добавить в начало
    void insert_at(const T& element, int index); // добавить в заданную позицию // сл этап
    void remove_at(int index);

    LinkedList<T>* concat(LinkedList<T> *list);

    // итератор
    class ListEnumerator : public IEnumerator<T> {

    public:
        ListEnumerator(const Node *head)
            : current(head) {}

        bool has_more_elements() override {
            return current != nullptr;
        }

        const T& next() override {
            const T& value = current->data;

            current = current->next;

            return value;
        }

    private:
        const Node *current;
    };

};

/*============ КОНСТРУКТОРЫ ============*/

template<class T>
LinkedList<T>::LinkedList(const T *element, int count) {
    if (count < 0)
        throw std::out_of_range("Index out of range");
    head = nullptr;
    tail = nullptr;
    length = 0;

    for (int i = 0; i < count; i++) {
        append(element[i]);
    }
}

template<class T>
LinkedList<T>::LinkedList() {
    head = nullptr;
    tail = nullptr;
    length = 0;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList& list) {
    head = nullptr;
    tail = nullptr;
    length = 0;

    Node *current = list.head;
    while (current != nullptr) {
        append(current->data);
        current = current->next;
    }
}

/*============ ДЕСТРУКТОР ============*/

template<class T>
LinkedList<T>::~LinkedList() {

    Node *current = head;

    while (current != nullptr) {
        Node *next = current->next;
        delete current;
        current = next;
    }
}

/*============ ГЕТТЕРЫ ============*/

template<class T>
const T& LinkedList<T>::get_first() const{
    if (length == 0)
        throw std::out_of_range("Empty list");
    return head->data;
}

template<class T>
const T& LinkedList<T>::get_last() const {
    if (length == 0)
        throw std::out_of_range("Empty list");
    return tail->data;
}

template<class T>
const T& LinkedList<T>::get(int index) const {
    if (index < 0 || index >= length)
        throw std::out_of_range("Empty list");

    Node *current = head;

    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

template<class T>
typename LinkedList<T>::Node* LinkedList<T>::get_head() const {
    return head;
}

template<class T>
int LinkedList<T>::get_length() const{
    return length;
}

template<class T>
LinkedList<T> *LinkedList<T>::get_sub_list(int startIndex, int endIndex) {
    if (startIndex < 0 || startIndex >= length || startIndex > endIndex || endIndex >= length)
        throw std::out_of_range("Index out of range");

    LinkedList<T> *newList = new LinkedList<T>(); // нужно ли выделять память или передать как параметр?

    Node *current = head;
    for (int i = 0; i < startIndex; i++) {
        current = current->next;
    }

    for (int i = startIndex; i <= endIndex; i++) {
        newList->append(current->data);
        current = current->next;
    }

    return newList;
}

/*============ ОПЕРАЦИИ ============*/

template<class T>
void LinkedList<T>::append(const T& element) {

    Node *newNode = new Node(element);

    if (length == 0) {
        head = newNode;
        tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }

    length++;
}

template<class T>
void LinkedList<T>::prepend(const T& element) {

    Node *newNode = new Node(element);

    newNode->next = head;
    head = newNode;

    if (length == 0) {
        tail = newNode;
    }
    length++;
}

template<class T>
void LinkedList<T>::insert_at(const T& element, int index) {
    if (index < 0 || index > length)
        throw std::out_of_range("Index out of range");

    if (index == 0) {
        prepend(element);
        return;
    }
    if (index == length) {
        append(element);
        return;
    }

    Node *prev = head;

    for (int i = 0; i < index - 1; i++) {
        prev = prev->next;
    }

    Node *newNode = new Node(element);

    newNode->next = prev->next;
    prev->next = newNode;

    length++;
}

template<class T>
void LinkedList<T>::remove_at(int index) {

    if (index < 0 || index >= length)
        throw std::out_of_range("Index out of range");

    if (index == 0) {
        Node *to_delete = head;
        head = head->next;

        delete to_delete;
        length--;

        if (length == 0)
            tail = nullptr;

        return;
    }

    Node *prev = head;
    for (int i = 0; i < index - 1; i++) {
        prev = prev->next;
    }

    Node *to_delete = prev->next;

    prev->next = to_delete->next;

    if (to_delete == tail) {
        tail = prev;
    }

    delete to_delete;
    length--;
}

template<class T>
LinkedList<T>* LinkedList<T>::concat(LinkedList<T> *list) {

    LinkedList<T> *concatList = new LinkedList<T>(*this);

    Node *current = list->head;
    while (current != nullptr) {
        concatList->append(current->data);
        current = current -> next;
    }

    return concatList;
}


#endif //LABA2_LINKEDLIST_H