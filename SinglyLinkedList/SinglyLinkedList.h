// #ifdef SINGLY_LINKED_LIST_H
// #define SINGLY_LINKED_LIST_H

namespace datastructs {

    template<typename T>
    class list_node {

        public:

            // constructors, destructors
            list_node ();
            list_node<T> (const T&, list_node<T>*);

            // accessors
            list_node<T>* next(void) const;
            T retrieve(void) const;

        private:

            T element;
            list_node<T>* next_node;

    };

    template<typename T>
    class singly_linked_list {

        public:

            // constructors, destructors
            singly_linked_list ();
            explicit singly_linked_list (const singly_linked_list<T>&);
            explicit singly_linked_list (singly_linked_list<T>&&);
            ~singly_linked_list ();

            // accessors
            bool empty(void) const;
            unsigned int get_size(void) const;
            list_node<T>* get_head(void) const;
            list_node<T>* get_tail(void) const;
            T get_front(void) const;
            T get_back(void) const;
            unsigned int count(const T&) const;

            // mutators
            void swap(singly_linked_list<T>);
            void push_front(const T&);
            void push_front(T&&);
            void push_back(const T&);
            void push_back(T&&);
            T& pop(void);
            unsigned int erase(const T&);
            unsigned int erase(T&&);

        private:

            void insert_front(T& t);
            void insert_back(T& t);
            list_node<T> *head, *tail;
            unsigned int size;

    };

}

// #endif
