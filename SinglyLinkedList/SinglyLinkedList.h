#pragma once
#include <bits/c++config.h>

namespace ds {

    template<typename T>
    struct list_node {

            // public members
            T element;
            list_node<T>* next;

            // constructors, destructors
            list_node ();
            list_node (const T&, list_node<T>*);
            list_node (T&&, list_node<T>*);

            void swap(list_node<T>&);

            // operator overloading
            list_node& operator= (list_node<T>);

    };

    template<typename T>
    class list {

        public:
            // public members
            list_node<T> *head, *tail;
            std::size_t size;

            // constructors, destructors
            list ();
            explicit list (const list<T>&);
            explicit list (list<T>&&);
            ~list ();

            // operator overloading
            list<T>& operator= (list<T>);

            // accessors
            bool empty(void) const;
            T get_front(void) const;
            T get_back(void) const;
            unsigned int count(const T&) const;

            // mutators
            void swap(list<T>&);
            void push_front(const T&);
            void push_front(T&&);
            void push_back(const T&);
            void push_back(T&&);
            unsigned int erase(const T&);
            unsigned int erase(T&&);
            T pop(void);

        private:

            template<typename U>
            unsigned int delete_node(U&&);
            template<typename U>
            void insert_front(U&& u);
            template<typename U>
            void insert_back(U&& u);

    };

}
