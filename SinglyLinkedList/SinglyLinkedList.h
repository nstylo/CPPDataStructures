#pragma once
#include <bits/c++config.h>
#include <type_traits>

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

            void swap(list_node<T>&) noexcept;

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
            bool empty(void) const noexcept;
            T get_front(void) const;
            T get_back(void) const;
            unsigned int count(const T&) const noexcept;

            // mutators
            void swap(list<T>&) noexcept;
            void push_front(const T&) noexcept;
            void push_front(T&&) noexcept;
            void push_back(const T&) noexcept;
            void push_back(T&&) noexcept;
            unsigned int erase(const T&) noexcept;
            unsigned int erase(T&&) noexcept;
            T pop(void);

        private:

            template<typename V>
            using strippedType = std::remove_const_t<std::remove_reference_t<V>>;

            template<typename U>
            unsigned int delete_node(U&&) noexcept;
            template<typename U>
            void insert_front(U&& u) noexcept;
            template<typename U>
            void insert_back(U&& u) noexcept;

    };

}
