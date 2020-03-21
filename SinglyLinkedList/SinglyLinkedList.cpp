#include "SinglyLinkedList.h"
#include <stdexcept>
#include <utility>
#include <iostream>

using namespace datastructs;

template<typename T>
list_node<T>::list_node () {}

template<typename T>
list_node<T>::list_node (const T& t, list_node<T>* next)
    : element(t), next_node(next)
{}

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
T singly_linked_list<T>::get_front(void) const {
    if (empty())
        throw std::underflow_error ("List is empty, but get_front attempted.");

    return head->retrieve();
}

template<typename T>
T singly_linked_list<T>::get_back(void) const {
    if (empty())
        throw std::underflow_error ("List is empty, but get_back attempted.");

    return tail->retrieve();
}

template <typename T>
unsigned int singly_linked_list<T>::count(const T& t) const {
    unsigned int cnt = 0;
    list_node<T>* curr = head;

    for (int i = 0; i < size; i++) {
        if (curr->retrieve() == t) { // increment count
            cnt++;
        }
        curr = curr->next(); // next node
    }

    return cnt;
}

template<typename T>
void singly_linked_list<T>::swap(singly_linked_list<T> other) {
    // create temp members
    list_node<T>* temp_head = std::move(other.get_head());
    list_node<T>* temp_tail = std::move(other.get_tail());
    unsigned int temp_size = std::move(other.get_size());

    // assign this objects members to other
    other.get_head() = std::move(head);
    other.get_tail() = std::move(tail);
    other.get_size() = std::move(size);

    // assing temp members to this
    head = std::move(temp_head);
    tail = std::move(temp_tail);
    size = std::move(temp_size);
}

template<typename T>
void singly_linked_list<T>::push_front(const T& t) {
    insert_front(t);
}

template<typename T>
void singly_linked_list<T>::push_front(T&& t) {
    insert_front(t);
}

template<typename T>
void singly_linked_list<T>::push_back(const T& t) {
    insert_back(t);
}

template<typename T>
void singly_linked_list<T>::push_back(T&& t) {
    insert_back(t);
}

template<typename T>
T& singly_linked_list<T>::pop(void) {
    if (empty())
        throw std::underflow_error ("List is empty, but pop attempted.");

    // copy necessary data from head
    T element = head->retrieve();
    list_node<T>* next = head->next();
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
unsigned int singly_linked_list<T>::erase(const T& t) {
    if (empty()) { // if list empty, there are no nodes to delete
        return 0;
    }

    unsigned int cnt = 0;
    list_node<T>* prev = nullptr;
    list_node<T>* curr = head; // head is guranteed to not be nullptr

    for (int i = 0; i < size; i++) {
        if (curr->retrieve() == t) { // delete, increment cnt and update head/tail
            list_node<T>* temp = std::move(curr);
            curr = curr->next();

            if (!prev) { // we need to delete head
                head = curr;
            } else if (!curr) { // we need to delete tail
                tail = prev;
            } else {
                list_node<T>* ptr = prev->next();
                ptr = curr;
            }

            cnt++;
            delete temp;
            continue;
        }
        curr = curr->next(); // next node
    }

    size -= cnt; // update size
    return cnt;
}

template<typename T>
void singly_linked_list<T>::insert_back(T& t) {
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
    size++;
}

template<typename T>
void singly_linked_list<T>::insert_front(T& t) {
    // create new node storing the passed on argument, pointing to current head
    list_node<T>* new_node = new list_node<T> (std::move(t), head);

    // if list is empty, let tail point to the new/first node
    if (empty())
        tail = new_node;

    // update head
    head = new_node;
    // update size
    size++;
}

int main(int argc, char *argv[])
{
    singly_linked_list<int>* li = new singly_linked_list<int>();
    li->push_front(1);
    li->push_front(1);
    li->push_front(1);

    std::cout << li->get_size() << std::endl;
    int i = 1;
    li->erase(i);
    std::cout << li->get_size() << std::endl;

    delete li;

    return 0;
}
