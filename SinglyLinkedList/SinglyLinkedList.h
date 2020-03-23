#pragma once

namespace datastructs {

    template<typename T>
    struct list_node {

            // public members
            T element;
            list_node<T>* next;

            // constructors, destructors
            list_node ();
            list_node<T> (T&, list_node<T>*);

    };

    template<typename T>
    class singly_linked_list {

        public:
            // public members
            list_node<T> *head, *tail;
            unsigned int size;

            // constructors, destructors
            singly_linked_list ();
            explicit singly_linked_list (const singly_linked_list<T>&);
            explicit singly_linked_list (singly_linked_list<T>&&);
            ~singly_linked_list ();

            // operators
            singly_linked_list<T>& operator= (singly_linked_list<T>&);

            // accessors
            bool empty(void) const;
            T get_front(void) const;
            T get_back(void) const;
            unsigned int count(const T&) const;

            // mutators
            void swap(singly_linked_list<T>&);
            void push_front(T&);
            void push_front(T&&);
            void push_back(T&);
            void push_back(T&&);
            T& pop(void);

            template<typename U>
            unsigned int erase(U&&);

        private:

            void insert_front(T& t);
            void insert_back(T& t);

    };

}
