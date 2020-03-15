#include "SinglyLinkedList.h"
#include <stdexcept>
#include <utility>

using namespace datastructs;

template<typename T>
list_node<T>::list_node (const T& t, list_node<T>* next)
    : element(t), next_node(next)
{}

template<typename T>
list_node<T>::~list_node () {}

template<typename T>
list_node<T>* list_node<T>::next(void) const {
    return next_node;
}

template<typename T>
T list_node<T>::retrieve(void) const {
    return element;
}



template<typename T>
singly_linked_list<T>::singly_linked_list () :
    head(nullptr),
    tail(nullptr),
    size(0)
{}

// temporary, we will use an iterator in the future
template<typename T>
singly_linked_list<T>::~singly_linked_list () {
    list_node<T>* next = head;
    while (next) {
        list_node<T>* curr = next;
        next = curr->next();
        delete curr;
    }
}

template<typename T>
bool singly_linked_list<T>::empty(void) const {
    return size == 0;
}

template<typename T>
unsigned int singly_linked_list<T>::get_size(void) const {
    return size;
}

template<typename T>
list_node<T>* singly_linked_list<T>::get_head(void) const {
    return head;
}

template<typename T>
list_node<T>* singly_linked_list<T>::get_tail(void) const {
    return tail;
}

template<typename T>
void singly_linked_list<T>::push_front(const T& t) {
    // create new node storing the passed on argument, pointing to current head
    list_node<T>* new_node = new list_node<T> (t, head);

    // if list is empty, let tail point to the new/first node
    if (empty())
        tail = new_node;

    // update head
    head = new_node;
    // update size
    size += 1;
}

//TODO: remove duplicate code, create new function

template<typename T>
void singly_linked_list<T>::push_front(T&& t) {
    // create new node storing the passed on argument, pointing to current head
    list_node<T>* new_node = new list_node<T> (std::move(t), head);

    // if list is empty, let tail point to the new/first node
    if (empty())
        tail = new_node;

    // update head
    head = new_node;
    // update size
    size += 1;
}

template<typename T>
void singly_linked_list<T>::push_back(const T& t) {
    // create new node storing the passed on argument, pointing to current head
    list_node<T>* new_node = new list_node<T> (t, nullptr);

    // if list is empty, let head point to the new/first node
    if (empty())
        head = new_node;

    // update next of previous tail
    list_node<T>* next = tail->next();
    next = new_node;

    // update tail
    tail = new_node;
    // update size
    size += 1;
}

//TODO: remove duplicate code, create new function

template<typename T>
void singly_linked_list<T>::push_back(T&& t) {
    // create new node storing the passed on argument, pointing to current head
    list_node<T>* new_node = new list_node<T> (std::move(t), nullptr);

    // if list is empty, let head point to the new/first node
    if (empty())
        head = new_node;

    // update next of previous tail
    list_node<T>* next = tail->next();
    next = new_node;

    // update tail
    tail = new_node;
    // update size
    size += 1;
}

template<typename T>
T singly_linked_list<T>::pop(void) {
    if (empty())
        throw std::underflow_error ("List is empty, but pop attempted.");

    // copy necessary data from head and delete
    T element = head->retrieve();
    list_node<T>* next = head->next();
    delete head;

    // move head pointer one position back
    head = next;

    // if list is now empty, move tail pointer as well
    if (head)
        tail = head;

    // reduce size of list
    size -= 1;

    return element;
}

int main(int argc, char *argv[])
{
    return 0;
}
