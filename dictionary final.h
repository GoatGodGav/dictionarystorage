#ifndef map_H
#define map_H

#include <algorithm>
#include <iostream>
#include <stack>
#include <stdexcept>

namespace nwacc {

    template <typename K ,typename V>
    class map {

    private:

        struct node {

            K key;
            V value;
            node* parent;
            node* left;
            node* right;
            
            int height;


            node(const K& the_key, const V& the_value, node* the_parent, node* left_node, node* right_node, int node_height = 0)
                : key{ the_key }, value{ the_value }, parent{ the_parent }, left{ left_node }, right{ right_node }, height{ node_height } {}

            node(const K&& the_key, V&& the_value, node* the_parent, node* left_node, node* right_node, int node_height = 0)
                : key{ std::move(the_key) }, value{ std::move(the_value) }, parent{ the_parent }, left{ left_node }, right{ right_node }, height{ node_height } {}
        };



        node* root;




    public:

        class const_iterator {
        public:

            const_iterator() : current{ nullptr } { }




            const K& operator*() //derefrence key
            {
                return this->retrieve_key();
            }

            const V& operator-() // unused operator needed to derefrence value 
            {
                return this->retrieve_value();
            }


            const_iterator& operator++()
            {

                if (this->current->right != nullptr) // step right run left
                {
                    
                    this->current = this->current->right;

                    while (this->current->left != nullptr)
                    {
                        this->current = this->current->left;
                    }
                    return *this;  //next number reached
                }




                if (this->current->right == nullptr) // move up tree till move past left child node of subtree
                {

                    

                    node* holder = this->current->parent;

                    

                    if (this->current != holder->left)
                    {
                        

                        while (this->current != holder->left)//move up tree
                        {


                            if (this->current->parent == nullptr)//root reached
                            {

                                
                                return *this;
                                
                            }
                            
                            this->current = this->current->parent;
                        }


                    }

                   
                    this->current = this->current->parent;


                    if (this->current->right != nullptr)// reached final number
                    {

                        return *this;
                    }



                }
                return *this;

            }




            bool operator==(const const_iterator& rhs) const
            {
                return this->current == rhs.current;
            }

            bool operator!=(const const_iterator& rhs) const
            {
                return !(*this == rhs);
            }

        protected:
            node* current;

            K& retrieve() const
            {
                return this->current->key;
            }

            V& retrieve_value() const
            {
                return this->current->value;
            }

            const_iterator(node* position) : current{ position } {}

            friend class map<K,V>;
        };


        const_iterator begin() const
        {

            node* current = this->root;

            while (current != nullptr)
            {
                if (current->left == nullptr)
                {
                    return current;
                }
                current = current->left;
            }
            return this->root;
        }


        const_iterator end() const
        {
            node* current = this->root;

            while (current != nullptr)
            {
                current = current->right;
            }
            return current;
        }

        const_iterator last()const
        {
            node* current = this->root;

            while (current->right != nullptr)
            {
                current = current->right;
                
            }
            return current;
        }





        map() : root{ nullptr } {}

        map(const map& rhs) : root{ nullptr }
        {
            this->root = this->copy(rhs.root);
        }

        map(map&& rhs) : root{ rhs.root }
        {
            rhs.root = nullptr;
        }

        ~map()
        {
            this->empty();
        }

        map& operator=(const map& rhs)
        {
            auto copy = rhs;
            std::swap(*this, copy);
            return *this;
        }

        map& operator=(map&& rhs)
        {
            std::swap(this->root, rhs.root);
            return *this;
        }


        V operator[](K s_key) //[] operator
        {
            node* position = this->root;
            while (position != nullptr)
            {
                if (s_key < position->key)
                {
                    position = position->left;
                }
                else if (position->key < s_key)
                {
                    position = position->right;
                }
                else if(position->key == s_key)
                {
                    return position->value;
                }
            }

            return "value not found";
        }



        std::string get_key(int key)
        {
            return this->get_the_key(key, this->root);
        }





        



        void remove_key(const K& key)
        {
            this->remove_the_key(key, this->root);

        }

        void remove_value(const V& value)
        {
            this->remove_the_value(value);
        }





        void print(std::ostream& out = std::cout) const
        {
            if (this->is_empty()) {
                out << "Empty tree" << std::endl;
            }
            else {
                this->print(this->root, out);
            }
        }





        //
        //
        //
        //
        //
        //
        //
        //
        //
        //
        //
        //
        //
        //
        //
        //
        //
        //
        //

        void put(const K& key, const V& value)
        {

            this->insert(key, value, this->root, nullptr);

        }

        void put(K&& key, V&& value)
        {

            this->insert(std::move(key), std::move(value), this->root, nullptr);

        }

        bool contains_key(const K& key) const
        {
            return this->find_key(key, this->root);
        }

        bool contains_value(const V& value)
        {
            return this->find_value(value, this->root);
        }

        bool is_empty() const
        {
            return this->root == nullptr;
        }


        void empty()
        {
            this->clear(this->root);
        }

        const K& find_min() const
        {
            if (this->is_empty()) {
                throw new std::range_error("Tree is empty");
            }
            else {
                return this->find_min(this->root);
            }
        }

        const K& find_max() const
        {
            if (this->is_empty()) {
                throw new std::range_error("Tree is empty");
            }
            else {
                return this->find_max(this->root);
            }
        }

        int get_root()
        {
            int holder;
            node* test;
            test = this->root;
            holder = test->key;
            return holder;
        }





        //
        //
        //
        //
        //
        //
        //
        //
        //
        //
        //
        //



        void display(std::ostream& out = std::cout)
        {
            std::stack<node*> global_stack;
            global_stack.push(this->root);
            auto number_of_blanks = 40;
            auto is_row_empty = false;
            out << "......................................................" << std::endl;
            while (!is_row_empty) {
                std::stack<node*> local_stack;
                is_row_empty = true;
                for (auto counter = 0; counter < number_of_blanks; counter++) {
                    out << " ";
                }

                while (!global_stack.empty()) {
                    auto temp = global_stack.top();
                    global_stack.pop();
                    if (temp != nullptr && temp->parent != nullptr) {

                        
                        out << temp->key << ":" << temp->parent->key;

                        local_stack.push(temp->left);
                        local_stack.push(temp->right);

                        if (temp->left != nullptr ||
                            temp->right != nullptr) {
                            is_row_empty = false;
                        }
                    }
                    else {
                        out << "--";
                        local_stack.push(nullptr);
                        local_stack.push(nullptr);
                    }

                    for (auto counter = 0;
                        counter < number_of_blanks * 2 - 2;
                        counter++) {
                        out << " ";
                    }
                }
                out << std::endl;
                number_of_blanks /= 2;
                while (!local_stack.empty()) {
                    global_stack.push(local_stack.top());
                    local_stack.pop();
                }
            }
            out << "......................................................"
                << std::endl;
        }







    private:


        int height(node* position) const
        {
            return position == nullptr ? -1 : position->height;
        }


        void assign_parents(node* holder)
        {
            
            if (holder != nullptr)
            {

                node* current = holder->left;

                if (current != nullptr)
                {

                    while (current->left != nullptr)
                    {

                        current->parent = holder;

                        holder = current;

                        current = current->left;

                    }
                }

            }
            this->root->parent = nullptr;

        }


        // left rotate
        void rotate_with_right_child(node*& current)
        {
            auto* temp = current->right;

            current->right = temp->left;

            temp->left = current;

            current->height = std::max( this->height(current->left), this->height(current->right)) + 1;

            temp->height = std::max( this->height(temp->left), current->height) + 1;



            current->parent = temp;



            current = temp;

            if (current == this->root) 
            {
           //     current->parent = nullptr;
            }

            
        }

       //right rotate
        void rotate_with_left_child(node*& current)
        {
            auto* temp = current->left;
            current->left = temp->right;
            temp->right = current;

            current->height = std::max(
                this->height(current->left),
                this->height(current->right)) + 1;

            temp->height = std::max(
                this->height(temp->left),
                current->height) + 1;

            
            current->parent = temp;

            current = temp;

            if (current == this->root)
            {
            //    current->parent = nullptr;
            }
        }

        void double_rotate_with_left_child(node*& current)
        {
            this->rotate_with_right_child(current->left);
            this->rotate_with_left_child(current);
        }

        void double_rotate_with_right_child(node*& current)
        {
            this->rotate_with_left_child(current->right);
            this->rotate_with_right_child(current);
        }

        void rebalance(node*& current)
        {
            if (current == nullptr) {
                return;
            }

            if (this->height(current->left) - this->height(current->right) > 1)
            {


                if (this->height(current->left->left) >=
                    this->height(current->left->right)) {
                    this->rotate_with_left_child(current);
                }
                else {

                    this->double_rotate_with_left_child(current);
                }
            }

            else if (this->height(current->right) -
                this->height(current->left) > 1) {

                if (this->height(current->right->right) >=
                    this->height(current->right->left)) {
                    this->rotate_with_right_child(current);
                }
                else {

                    this->double_rotate_with_right_child(current);
                }

            }


            current->height = std::max(
                this->height(current->left),
                this->height(current->right)) + 1;
        }

        V get_the_key(K& s_key, node* position)
        {
            while (position != nullptr)
            {
                if (s_key < position->key)
                {
                    position = position->left;
                }
                else if (position->key < s_key)
                {
                    position = position->right;
                }
                else
                {
                    return position->value;
                }
            }
            return "value not found";
        }




        node* find_min(node* position) const
        {
            if (position == nullptr) {
                return nullptr;
            } 

            if (position->left == nullptr) {
                return position;
            } 

            return this->find_min(position->left);
        }

        node* find_max(node* position) const
        {
            if (position != nullptr) {
                while (position->right != nullptr) {
                    position = position->right;
                }
            }
            return position;
        }

        void remove_the_key(const K& s_key, node*& position) // s_key = key im Serching for 
        {
            if (position == nullptr) {
                return; 
            } 


            if (s_key < position->key) {
                this->remove_the_key(s_key, position->left);
            }
            else if (position->key < s_key) {
                this->remove_the_key(s_key, position->right);
            }

            else if (position->left != nullptr && position->right != nullptr)
            {
                position->key = this->find_min(position->right)->key;
                this->remove_the_key(position->key, position->right);
            }
            else {
                auto* old_node = position;
                position = (position->left != nullptr) ?
                    position->left :
                    position->right;
                delete old_node;
            }

            this->rebalance(position);
            assign_parents(position);
        }


        void remove_the_value(const V& s_value) // s_value = value im Serching for 
        {

            auto itra = begin();
            
            while (itra != last())
            {

                    if (-itra == s_value)
                    {

                        node* remove_this = itra.current;

                        ++itra;

                        node* lefts = remove_this->left;

                        node* rights = remove_this->right;

                        node* parents = remove_this->parent;

                        if (parents->right == remove_this)
                        {
                            parents->right = rights;
                            
                        }
                        else if(parents->left == remove_this){
                            parents->left = rights;
                        }


                        if (lefts != nullptr) 
                        {
                            lefts->parent = remove_this->right;
                        }

                        if (rights != nullptr)
                        {
                            rights->parent = remove_this->parent;
                        }

                        node* position = itra.current;

                        this->rebalance(position);
                        assign_parents(position);

                        delete remove_this;
                    }
                    else {
                        ++itra;
                    }
            }

        }

        void insert(const K& new_key,const V& new_value, node*& position, node* parent_link)
        {

            if (position == nullptr) {
                position = new node{ new_key, new_value, parent_link, nullptr, nullptr };
            }
            
            parent_link = position;

            if (new_key < position->key) 
            {
                this->insert(new_key, new_value, position->left, parent_link);
            }


            else if (position->key < new_key) {
                this->insert(new_key, new_value, position->right, parent_link);
            } 

            this->rebalance(position);
            assign_parents(position);
        }

        void insert(const K&& new_key,const V&& new_value, node*& position, node* parent_link)
        {
            if (position == nullptr)
            {
                position = new node{ std::move(new_key), std::move(new_value), parent_link, nullptr, nullptr };
            }

            parent_link = position;

            if (new_key < position->key)
            {
                this->insert(std::move(new_key),std::move(new_value), position->left, parent_link);
            }

            else if (position->key < new_key) 
            {
                this->insert(std::move(new_key), std::move(new_value), position->right, parent_link);
            } 

            this->rebalance(position);
            assign_parents(position);
        }


        bool find_key(const K& s_key, node* position) const
        {
            while (position != nullptr) 
            {
                if (s_key < position->key) 
                {
                    position = position->left;
                }
                else if (position->key < s_key) 
                {
                    position = position->right;
                }
                else
                {
                    return true;
                }
            }

            return false;
        }


        bool find_value(const V& s_value, node* position) const
        {
            auto itra = begin();

            for (auto index = 0; index < 6; index++)
            {

                if (-itra == s_value)
                {

                    return true;

                }

                ++itra;

            }
            return false;
        }


        void print(node* position, std::ostream& out) const
        {
            if (position != nullptr) {
                this->print(position->left, out);
                out << position->key << " " << position->value << std::endl;
                this->print(position->right, out);
            } 
        }



        void clear(node*& position)
        {
            if (position != nullptr) {
                this->clear(position->left);
                this->clear(position->right);
                delete position;
            } 

            position = nullptr;
        }

        node* copy(node* position) const
        {
            return position == nullptr ?
                nullptr :
                new node{ position->key,
                          this->copy(position->left),
                          this->copy(position->right),
                          position->height };
        }


    };
}

#endif
