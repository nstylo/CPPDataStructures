#include "SinglyLinkedList.h"
#include <stdexcept>
#include <utility>

using namespace datastructs;

template<typename T>
list_node<T>::list_node () {}

template<typename T>
list_node<T>::list_node (T& t, list_node<T>* next)
    : element(t), next(next)
{}

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
        next = curr->next;
        delete curr;
    }
}

// uncommon behaviour: swaps the lists
template<typename T>
singly_linked_list<T>& singly_linked_list<T>::operator= (singly_linked_list<T>& other) {
    swap(other);
    return *this;
}

template<typename T>
bool singly_linked_list<T>::empty(void) const {
    return size == 0;
}

template<typename T>
T singly_linked_list<T>::get_front(void) const {
    if (empty())
        throw std::underflow_error ("List is empty, but get_front attempted.");

    return head->element;
}

template<typename T>
T singly_linked_list<T>::get_back(void) const {
    if (empty())
        throw std::underflow_error ("List is empty, but get_back attempted.");

    return tail->element;
}

template <typename T>
unsigned int singly_linked_list<T>::count(const T& t) const {
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
void singly_linked_list<T>::swap(singly_linked_list<T>& other) {
    // create temp members
    list_node<T>* temp_head = std::move(other.head);
    list_node<T>* temp_tail = std::move(other.tail);
    unsigned int temp_size = std::move(other.size);

    // assign this objects members to other
    other.head = std::move(head);
    other.tail = std::move(tail);
    other.size = std::move(size);

    // assing temp members to this
    head = std::move(temp_head);
    tail = std::move(temp_tail);
    size = std::move(temp_size);
}

template<typename T>
void singly_linked_list<T>::push_front(T& t) {
    insert_front(t);
}

template<typename T>
void singly_linked_list<T>::push_front(T&& t) {
    insert_front(t);
}

template<typename T>
void singly_linked_list<T>::push_back(T& t) {
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
unsigned int singly_linked_list<T>::erase(U&& u) {
    unsigned int cnt = 0;
    list_node<T>* prev = nullptr;
    list_node<T>* curr = head;

    for (int i = 0; i < size; i++) {
        if (curr->element == std::forward<U>(u)) { // delete, increment cnt and update head/tail
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
void singly_linked_list<T>::insert_back(T& t) {
    // create new node storing the passed on argument, pointing to current head
    list_node<T>* new_node = new list_node<T> (t, nullptr);

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
void singly_linked_list<T>::insert_front(T& t) {
    // create new node storing the passed on argument, pointing to current head
    list_node<T>* new_node = new list_node<T> (t, head);

    // if list is empty, let tail point to the new/first node
    if (empty())
        tail = new_node;

    // update head
    head = new_node;
    // update size
    size++;
}
