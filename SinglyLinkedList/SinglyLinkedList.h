// #ifdef SINGLY_LINKED_LIST_H
// #define SINGLY_LINKED_LIST_H

namespace datastructs {


    template<typename T>
    class singly_linked_list {

        private:

            template<typename U>
            class list_node {
                public:

                    // constructors destructors
                    list_node () = delete;
                    list_node (T&, list_node<T>*);
                    explicit list_node (const list_node<T>&);
                    explicit list_node (list_node<T>&&);
                    ~list_node ();

                    // accessors
                    list_node<T>* next(void) const;
                    T retrieve(void) const;

                private:

                    T element;
                    list_node<T>* next_node;
            };

        public:

            // constructors, destructors
            singly_linked_list ();
            explicit singly_linked_list (const singly_linked_list<T>&);
            explicit singly_linked_list (singly_linked_list<T>&&);
            ~singly_linked_list ();

            // accessors
            bool empty(void) const;
            int get_size(void) const;
            list_node<T>* get_head(void) const;
            list_node<T>* get_tail(void) const;

            // mutators
            void push_front(const T&);
            void push_front(const T&&); // uses std::move
            void push_back(const T&);
            void push_back(const T&&); // uses std::move
            T pop(void);
            void destroy(void);
            int erase(const T&);
            int erase(const T&&); // uses std::move

        private:

            list_node<T>* head;
            list_node<T>* tail;
            int size;

    };

}

// #endif
