#include "SinglyLinkedList.h"
#include <bits/c++config.h>
#include <stdexcept>
#include <utility>

using namespace ds;

template<typename T>
list_node<T>::list_node () {}

template<typename T>
list_node<T>::list_node (const T& t, list_node<T>* next)
    : element(t), next(next)
{}

template<typename T>
list_node<T>::list_node (T&& t, list_node<T>* next)
    : element(std::move(t)), next(next)
{}

template<typename T>
list_node<T>& list_node<T>::operator= (list_node<T> rhs) {
    swap(rhs);
    return *this;
}

template<typename T>
void list_node<T>::swap (list_node<T>& other) {
    // create temp members
    T temp_element = std::move(other.element);
    list_node<T>* temp_next = std::move(other.next);

    // assing this objects members to other
    other.element = std::move(element);
    other.next = std::move(next);

    // assign temp to members to this
    element = std::move(temp_element);
    next = std::move(temp_next);
}

template<typename T>
list<T>::list () :
    head(nullptr),
    tail(nullptr),
    size(0)
{}

template<typename T>
list<T>::list (const list<T>& t) :
    head(t.head),
    tail(t.tail),
    size(t.size)
{}

template<typename T>
list<T>::list (list<T>&& t) :
    head(std::move(t.head)),
    tail(std::move(t.tail)),
    size(std::move(t.size))
{}

template<typename T>
list<T>::~list () {
    list_node<T>* next = head;
    while (next) {
        list_node<T>* curr = next;
        next = curr->next;
        delete curr;
    }
}

template<typename T>
list<T>& list<T>::operator= (list<T> rhs) {
    swap(rhs);
    return *this;
}

template<typename T>
bool list<T>::empty(void) const {
    return size == 0;
}

template<typename T>
T list<T>::get_front(void) const {
    if (empty())
        throw std::underflow_error ("List is empty, but get_front attempted.");

    return head->element;
}

template<typename T>
T list<T>::get_back(void) const {
    if (empty())
        throw std::underflow_error ("List is empty, but get_back attempted.");

    return tail->element;
}

template <typename T>
unsigned int list<T>::count(const T& t) const {
    unsigned int cnt = 0;
    list_node<T>* curr = head;

    for (int i = 0; i < size; i++) {
        if (curr->element == t) { // increment count
            cnt++;
        }
        curr = curr->next; // next node
    }

    return cnt;
}

template<typename T>
void list<T>::swap(list<T>& other) {
    // create temp members
    list_node<T>* temp_head = std::move(other.head);
    list_node<T>* temp_tail = std::move(other.tail);
    std::size_t temp_size = std::move(other.size);

    // assign this objects members to other
    other.head = std::move(head);
    other.tail = std::move(tail);
    other.size = std::move(size);

    // assign temp members to this
    head = std::move(temp_head);
    tail = std::move(temp_tail);
    size = std::move(temp_size);
}

template<typename T>
void list<T>::push_front(const T& t) {
    insert_front(t);
}

template<typename T>
void list<T>::push_front(T&& t) {
    insert_front(std::move(t));
}

template<typename T>
void list<T>::push_back(const T& t) {
    insert_back(t);
}

template<typename T>
void list<T>::push_back(T&& t) {
    insert_back(std::move(t));
}

template<typename T>
unsigned int list<T>::erase(const T& t) {
    return delete_node(t);
}

template<typename T>
unsigned int list<T>::erase(T&& t) {
    return delete_node(std::move(t));
}

template<typename T>
T list<T>::pop(void) {
    if (empty())
        throw std::underflow_error ("List is empty, but pop attempted.");

    // copy necessary data from head
    T element = head->element;
    list_node<T>* next = head->next;
    delete head;

    // move head pointer one position back
    head = next;

    // if list is now empty, move tail pointer as well
    if (head)
        tail = head;

    // reduce size of list
    size--;

    return element;
}

template<typename T>
template<typename U>
unsigned int list<T>::delete_node(U&& u) {
    unsigned int cnt = 0;
    list_node<T>* prev = nullptr;
    list_node<T>* curr = head;

    for (int i = 0; i < size; i++) {
        if (curr->element == u) { // delete, increment cnt and update head/tail
            list_node<T>* temp = curr;
            curr = curr->next;

            if (prev != nullptr) { // we need to reset head
                head = curr;
            }
            if (curr != nullptr) { // we need to reset tail
                tail = prev;
            } else { // pointer deleted, reset next
                prev->next = curr;
            }

            cnt++;
            delete temp;
            continue;
        }
        prev = curr;
        curr = curr->next; // next node
    }

    size -= cnt; // update size
    return cnt;
}

template<typename T>
template<typename U>
void list<T>::insert_back(U&& u) {
    // create new node storing the passed on argument, pointing to current head
    list_node<T>* new_node = new list_node<T> (std::forward<U>(u), nullptr);

    // if list is empty, let head point to the new/first node
    if (empty()) {
        head = new_node;
    } else {
        // update next of previous tail
        tail->next = new_node;
    }

    // update tail
    tail = new_node;
    // update size
    size++;
}

template<typename T>
template<typename U>
void list<T>::insert_front(U&& u) {
    // create new node storing the passed on argument, pointing to current head
    list_node<T>* new_node = new list_node<T> (std::forward<U>(u), head);

    // if list is empty, let tail point to the new/first node
    if (empty())
        tail = new_node;

    // update head
    head = new_node;
    // update size
    size++;
}
