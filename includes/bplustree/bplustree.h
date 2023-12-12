#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include <iostream>
#include <iomanip>
#include "btree_array_funcs.h"

template <class T>
class BPlusTree
{
    public:

    class Iterator{
        public:
            friend class BPlusTree;
            Iterator(BPlusTree<T>* _it=NULL, int _key_ptr = 0):it(_it), key_ptr(_key_ptr){}

            T operator *()
            {
                return it->data[key_ptr];
            }

            Iterator operator++(int un_used)
            {
                
                key_ptr++;  

                if(key_ptr >= it->data_count)
                {
                    key_ptr = 0;
                    it = it->next;
                }

                return *this;
            }

            Iterator operator++()
            {
                key_ptr++;

                if(key_ptr >= it->data_count)
                {
                    key_ptr = 0;
                    it = it->next;
                }

                return *this;
            }
            friend bool operator ==(const Iterator& lhs, const Iterator& rhs)
            {
                return lhs.it == rhs.it && lhs.key_ptr == rhs.key_ptr;
            }

            friend bool operator !=(const Iterator& lhs, const Iterator& rhs)
            {
                return !(lhs == rhs);
            }

            void print_Iterator(){
                if (it){
                    cout<<"iterator: ";
                    print_array(it->data, it->data_count, key_ptr);
                }
                else{
                    cout<<"iterator: NULL, key_ptr: "<<key_ptr<<endl;
                }
            }
            bool is_null(){return !it;}
            void info(){

                cout<<endl<<"Iterator info:"<<endl;
                cout<<"key_ptr: "<<key_ptr<<endl;
                cout<<"it: "<<*it<<endl;
            }

        private:

            BPlusTree<T>* it;
            int key_ptr;
        };

    BPlusTree(bool dups = false)
    {
        dups_ok = dups;
        data_count = 0;
        child_count = 0;
        next = NULL;

        for (int i = 0; i < MAXIMUM + 1; i++)
        {
            data[i] = T();
        }

        for (int i = 0; i < MAXIMUM + 2; i++)
        {
            subset[i] = nullptr;
        }
    }

    BPlusTree(T *a, int size, bool dups = false)
    {
        dups_ok = dups;
        data_count = 0;
        child_count = 0;
        next = nullptr;

        for (int i = 0; i < size; i++)
        {
            insert(a[i]);
        }
    }

    // big three:
    BPlusTree(const BPlusTree<T> &other)
    {
        copy_tree(other);
    }

    ~BPlusTree()
    {
        clear_tree();
    }

    BPlusTree<T> &operator=(const BPlusTree<T> &RHS)
    {
        if (this == &RHS)
        {
            return *this;
        }

        clear_tree();
        copy_tree(RHS);
        return *this;
    }

    void insert(const T &entry) // insert entry into the tree
    {
        if (data_count == 0)
        {
            ordered_insert(data, data_count, entry);
        }
        else
        {
            loose_insert(entry);
        }
        if (data_count > MAXIMUM)
        {

            BPlusTree
                *new_root = new BPlusTree<T>();

            copy_array(new_root->data, data, new_root->data_count, data_count);
            copy_array(new_root->subset, subset, new_root->child_count, child_count);

            subset[0] = new_root;
            subset[1] = nullptr;

            data_count = 0;

            child_count = 1;

            fix_excess(0);
        }
    }

    void remove(const T &entry) // remove entry from the tree
    {
        loose_remove(entry);

        if (data_count < MINIMUM && !is_leaf())
        {
            int index = subset[0] ? 0 : 1;

            BPlusTree
                *shrink_ptr = new BPlusTree<T>();

            copy_array(data, subset[index]->data, data_count, subset[index]->data_count);

            delete_item(subset, index, child_count, shrink_ptr);

            copy_array(subset, shrink_ptr->subset, child_count, shrink_ptr->child_count);

            shrink_ptr->child_count = 0;

            delete shrink_ptr;
        }
        else if (data_count == 0 && is_leaf())
        {
            for (int i = 0; i < MAXIMUM + 1; i++)
            {
                data[i] = T();
            }

            for (int i = 0; i < MAXIMUM + 2; i++)
            {
                subset[i] = nullptr;
            }
        }
    }

    void clear_tree() // clear this object (delete all nodes etc.)
    {
        for (int i = 0; i < data_count; i++)
        {
            data[i] = T();
        }

        for (int i = 0; i < child_count; i++)
        {
            subset[i]->clear_tree();
            
            if(subset[i]->is_leaf())
            {
                subset[i]->next = nullptr;
            }
            
            subset[i] = nullptr;

        }

        data_count = 0;
        child_count = 0;
    }

    void copy_tree(const BPlusTree<T> &other) // copy other into this object
    {

        BPlusTree<T> *last_node = nullptr;

        copy_tree(other, last_node);

    }

    void copy_tree(const BPlusTree<T>& other, BPlusTree<T>*& last_node)
    {
        data_count = 0;
        child_count = other.child_count;
        dups_ok = other.dups_ok;

        copy_array(data, other.data, data_count, other.data_count);

        if(!is_leaf())
        {
            for (int i = 0; i < other.child_count; i++)
            {
                subset[i] = new BPlusTree<T>();
                subset[i]->copy_tree(*other.subset[i], last_node);
            }    

            return;
        }
        else if(last_node)
        {
            this->next = last_node->next;
            last_node->next = this;
        }

        last_node = this;
       
    }

    bool contains (const T &entry) // true if entry can be found in the array
    {
        int index = first_ge(data, data_count, entry);// > data_count ? data_count - 1 : first_ge(data, data_count, entry);


        bool found = data[index] == entry;

        if(found && !is_leaf())
        {
            return subset[index + 1]->contains(entry);
        }
        else if(!found && !is_leaf())
        {
            return subset[index]->contains(entry);
        }
        else if(!found && is_leaf())
        {
            return false;
        }
        
        return true;
        
    }


    T &get(const T &entry) // return a reference to entry in the tree
    {
        int index = first_ge(data, data_count, entry);

        if (data[index] == entry && !is_leaf())
        {
            return subset[index + 1]->get(entry);
        }
        else if(data[index] == entry && is_leaf())
        {
            return data[index];
        }
         else if(is_leaf() && data[index] != entry)
        {   
            return data[index];
        } 
        else
        {
            return subset[index]->get(entry);
        }
    }

    const T& get(const T& entry)const   //return a reference to entry
    {
        return get(entry);
    }

    T& get_existing(const T& entry) {
        /*
    * ---------------------------------------------------------------
    * This routing explains plainly how the BPlusTree is organized.
    * i = first_ge
    *       |      found         |    !found         |
    * ------|--------------------|-------------------|
    * leaf  |  you're done       | it's not there    |
    *       |                    |                   |
    * ------|--------------------|-------------------|
    * !leaf | subset[i+1]->get() |  subset[i]->get() |
    *       | (inner node)       |                   |
    * ------|--------------------|-------------------|
    *       |                    |                   |
    *
    * ---------------------------------------------------------------
    *
    */
        //assert that entry is not in the tree.
        //assert(contains(entry));

        const bool debug = false;
        int index = first_ge(data, data_count, entry);
        bool found = (index < data_count && data[index] == entry);

        if (is_leaf()){

            if (found){
                return data[index];
            }
            else{
                cout<<"get_existing was called with nonexistent entry"<<endl;
                return T();
            }
        }
        if (found) //inner node
            return subset[index+1]->get(entry);
            //or just return true?
        else //not found yet...
            return subset[index]->get(entry);


    }
    Iterator find(const T& key)         //return an iterator to this key. NULL if not there.
    {
        if(contains(key) == false)
        {
            return Iterator(nullptr,0);
        }

        Iterator it = begin();


        while(it != end())
        {
            if(*it == key)
            {
                return it;
            }

            it++;
        }

        return Iterator(nullptr,0);
    }

    Iterator lower_bound(const T& key)  //return first that goes NOT BEFORE key entry or next if does not exist: >= entry
    {
        Iterator it = begin();
     

        while(it != end())
        {
         if(*it >= key)
            {
                return it;
            }

            it++;
        }

        return Iterator(nullptr,0);
    }

    Iterator upper_bound(const T& key)  //return first that goes AFTER key exist or not, the next entry  >entry
    {
        Iterator it = begin();

        while(it != end())
        {
            if(*it > key)
            {
                return it;
            }

            it++;
        }

        return end();
    }

    Iterator begin(){

        return Iterator(get_smallest_node());

    }

    Iterator end(){
        return Iterator(nullptr,0);
    }
    
    /* T *find(const T &entry) // return a pointer to this key. NULL if not there.
    {

        int index = first_ge(data, data_count, entry);

        if (data[index] == entry && index < data_count)
        {
            return &data[index];
        }

        if (is_leaf() && data[index] != entry)
        {
            return NULL;
        }

        return subset[index]->find(entry);
    }
 */
    int size()  // count the number of elements in the tree
    {
        int size = 0;

        if (!is_leaf())
        {
            size += subset[child_count - 1]->size();
        }

        for (int i = data_count - 1; i >= 0; i--)
        {
            size++;

            if (!is_leaf())
            {
                size += subset[i]->size();
            }
        }

        return size;
    }
    bool empty() const // true if the tree is empty
    {
        return child_count == 0 && data_count == 0;
    }

    bool is_valid() {
         
        if (data_count > MAXIMUM)
        {
            return false;
        }

        if (data_count < MINIMUM && !is_leaf())
        {
            return false;
        }

        if (child_count > MAXIMUM + 1)
        {
            return false;
        }

        if (child_count < 0)
        {
            return false;
        }

        if (child_count > 0 && is_leaf())
        {
            return false;
        }

        if (child_count > 0 && subset[0] == nullptr)
        {
            return false;
        }

        if (child_count > 0 && subset[child_count - 1] == nullptr)
        {
            return false;
        }

        if (child_count > 1 && subset[0]->data_count < MINIMUM)
        {
            return false;
        }

        if (child_count > 1 && subset[child_count - 1]->data_count < MINIMUM)
        {
            return false;
        }

        for (int i = 0; i < data_count; i++)
        {
            if (data[i] == T())
            {
                return false;
            }
        }

        for (int i = 0; i < child_count; i++)
        {
            if (subset[i] == nullptr)
            {
                return false;
            }
        }

        for (int i = 0; i < child_count; i++)
        {
            if (!subset[i]->is_valid())
            {
                return false;
            }
        }

        return true;
    }
    // print a readable version of
    //                   the tree
    void print_tree(int level = 0, ostream &outs = cout) const
    {
        if (!is_leaf())
        {
            subset[child_count - 1]->print_tree(level + 1, outs);
        }

        for (int i = data_count - 1; i >= 0; i--)
        {
            outs << setw(6 * level) << "[" << data[i] << "]" << endl;

            if (!is_leaf())
            {
                subset[i]->print_tree(level + 1, outs);
            }
        }
    }
    friend ostream &operator<<(ostream &outs, const BPlusTree<T> &print_me)
    {
        print_me.print_tree(0, outs);
        return outs;
    }

    string in_order(){

        string result = "";
        
        if(is_leaf())
        {
            for(int i = 0; i < data_count; i++)
            {
                result += to_string(data[i]);
                 result += "|";
            }
            return result;
        }

        for(int i = 0; i < data_count; i++)
        {
            result += subset[i]->in_order();
            result += to_string(data[i]);
            result += "|";
        }

        result += subset[child_count-1]->in_order();

        return result;
    }
 

    string pre_order()
    {

        string output = "";

        //print root/data
        //then traverse  left
        for (int i = 0; i < data_count; i++)
        {
            //print data
            output += to_string(data[i]) + "|";

            //traverse the left
            if (!is_leaf())
            {
                output += subset[i]->pre_order();
            }
        }

        //traverse the right
        if (!is_leaf())
        {
            output += subset[data_count]->pre_order();
        }



        return output;
    }

    string post_order()
    {

        //NOTE: Only right needs to iterate

        string output = "";

        //traverse the left
        if (!is_leaf())
        {
            output += subset[0]->post_order();
        }

        //traverse the right
        //and data

        for (int i = 0; i < data_count; i++)
        {
            //traverse right
            if (!is_leaf())
            {
                output += subset[i + 1]->post_order();
            }

            //print data
            output += to_string(data[i]) + "|";
        }

        return output;

    }

    

    ostream& list_keys(Iterator from = NULL, Iterator to = NULL){
        if(from == NULL)
        {
            from = begin();
        } 
        if(to == NULL)
        {
            to = end();
        }
        for(Iterator it = from; it != to; it++)
        {
            cout << *it << " ";
        }

        return cout;

    }

private:
    static const int MINIMUM = 1;
    static const int MAXIMUM = 2 * MINIMUM;

    bool dups_ok = false;       // true if duplicate keys may be inserted
    int data_count =0;      // number of data elements
    T data[MAXIMUM + 1]; // holds the keys
    int child_count = 0;     // number of children
    BPlusTree*subset[MAXIMUM + 2]; // suBPlusTrees
    BPlusTree* next = nullptr;


    bool is_leaf() const { return child_count == 0; } // true if this is a leaf node

    T* find_ptr(const T& entry)         //return a pointer to this key. NULL if not there.
    {
        
        if(contains(entry) == false)
        {
            return NULL;
        }

        int index = first_ge(data,data_count,entry);

        if(data[index] == entry)
        {
            if(!is_leaf())
            {
                return subset[index + 1]->find_ptr(entry);
            }
            else{
                return &data[index];
            }
        }
        
    }

    BPlusTree<T>* get_smallest_node()
    {
        if(is_leaf())
        {
            return this;
        }

        return subset[0]->get_smallest_node();
    }

    BPlusTree<T>* get_largest_node()
    {
        if(is_leaf())
        {
            return this;
        }

        return subset[child_count-1]->get_largest_node();
    }

    void get_smallest(T& entry)      //entry := leftmost leaf
    {

        if(is_leaf())
        {
            entry = data[0];
            return;
        }

        subset[0]->get_smallest(entry);

    }

    void get_biggest(T& entry)       //entry := rightmost leaf
    {

        if(is_leaf())
        {
            entry = data[data_count-1];
        }

        subset[child_count-1]->get_biggest(entry);

    }

    // insert element functions
    void loose_insert(const T &entry) // allows MAXIMUM+1 data elements in the root
    {
        
        int index = first_ge(data, data_count, entry);

        bool found = data[index] == entry && index < data_count;

         // insert into the leaf
        if (is_leaf())
        {
            if(found)
            {
                data[index] = data[index] + entry;
            }
            else{

                ordered_insert(data, data_count, entry);
            }
            
            return;
        }


        // if this is a duplicate then return and terminate program
        if (found && !is_leaf())
        {
            subset[index + 1]->loose_insert(entry);
        }        
        else
        { // if its not a leaf then recurse
            subset[index]->loose_insert(entry);
        }

        // if the child is too big then fix excess
        if (subset[index] && subset[index]->data_count > MAXIMUM)
        {
            fix_excess(index);
        }

    }

    void fix_excess(int i) // fix excess of data elements in child i
    {

        BPlusTree* child = subset[i];

        T middle_node_of_child = T();

        //grab the middle item of child data array
        delete_item(child->data, child->data_count / 2, child->data_count, middle_node_of_child);

        //insert middle child into parent
        ordered_insert(data, data_count, middle_node_of_child);

        //new BPlusTree for the right of data
        BPlusTree* new_right = new BPlusTree<T>();

        //split the data array into 2 array, the right side being stored in new_right
        split(child->data, child->data_count, new_right->data, new_right->data_count);
        split(child->subset, child->child_count, new_right->subset, new_right->child_count);

        int index = first_ge(data, data_count, new_right->data[0]);

        if(child->is_leaf())
        {
            ordered_insert(new_right->data, new_right->data_count, middle_node_of_child);

            new_right->next = child->next;

            child->next = new_right;

            
        }
        else {
            child ->next = nullptr;

            new_right->next = nullptr;
        }
        
        
        insert_item(subset, index, child_count, new_right); 
    }


    // remove element functions:
    void loose_remove(const T &entry) // allows MINIMUM-1 data elements in the root
    {
        int index = first_ge(data, data_count, entry);

        if (data[index] != entry && is_leaf())
        {
            return;
        }

        if (data[index] == entry && index != data_count)
        {

            if (is_leaf())
            {
                T temp;

                delete_item(data, index, data_count, temp);

                return;
            }
            else
            {
                index++;

                subset[index]->loose_remove(entry);

                subset[index] ->get_smallest(data[index - 1]);
            }
        }
        else if (!is_leaf())
        {
            subset[index]->loose_remove(entry);
        }

        // fix shortage by gettting largest element
        if (!is_leaf() && subset[index]->data_count < MINIMUM)
        {

            fix_shortage(index);
        }
    }

    BPlusTree<T>* fix_shortage(int i) // fix shortage of data elements in child i
    {

        if(size() == 3)
        {
            if(i == child_count-1)
            {
                merge_with_next_subset(i - 1);
            }
            else{
                merge_with_next_subset(i);
            }
        }
        else {
            int index = i == data_count && !empty() ? i - 1 : i;

            if (i + 1 < child_count && subset[i + 1]->data_count > MINIMUM)
            {
                transfer_left(i + 1);
            }
            else if (i - 1 >= 0 && subset[i - 1]->data_count > MINIMUM)
            {
                transfer_right(i - 1);
            }
            else if (data_count == child_count - 1)
            {
                if(data_count == 2 && i == 1)
                {
                    merge_with_next_subset(i - 1);
                }
                else {
                    merge_with_next_subset(index);

                }
            }
        }
        

        return nullptr;
    }

    void remove_biggest(T &entry) // remove the biggest child of this tree->entry and adjust child counter
    {
        // cout << "removing biggest" << endl;
        int index = first_ge(data, data_count, entry);

        if (is_leaf())
        {
            detach_item(data, data_count, entry);
        }
        else
        {
            subset[index]->remove_biggest(entry);

            for (int i = 0; i < child_count; i++)
            {
                if (subset[i]->data_count < MINIMUM)
                {
                    fix_shortage(i);
                }
            }
            /*  if(subset[child_count - 1] && subset[child_count - 1]->data_count < MINIMUM)
             {
                 fix_shortage(child_count - 1);

             } */
        }
    }

    void transfer_left(int i) // transfer one element LEFT from child i
    {
        // cout << "rotating left" << endl;
        // grab elements from child and root
        T transfer_element = T();

        delete_item(subset[i]->data, 0, subset[i]->data_count, transfer_element);

        T element_moving_down;

        delete_item(data, i - 1, data_count, element_moving_down);

        ordered_insert(data, data_count, transfer_element);

        ordered_insert(subset[i - 1]->data, subset[i - 1]->data_count, element_moving_down);

        BPlusTree *pointer_being_trasnfered;

        delete_item(subset[i]->subset, 0, subset[i]->child_count, pointer_being_trasnfered);

        // insert element from child to root

        attach_item(subset[i - 1]->subset, subset[i - 1]->child_count, pointer_being_trasnfered);

        // insert element from root to child

    }
    void transfer_right(int i) // transfer one element RIGHT from child i
    {
        // cout << "rotating right" << endl;
        // grab elements from child and root
        T transfer_element = T();

        detach_item(subset[i]->data, subset[i]->data_count, transfer_element);

        data[i] = transfer_element;

        // inserting elements to new homes

        ordered_insert(subset[i + 1]->data, subset[i + 1]->data_count, transfer_element);

    }

    BPlusTree<T> *merge_with_next_subset(int i) // merge subset i with subset  i+1
    {
        // cout << "merging with next subset" << endl;
        T element_going_down = T();

        BPlusTree*temp;

        delete_item(data, i, data_count, element_going_down);

        if(!subset[i]->is_leaf())
        {
            ordered_insert(subset[i]->data, subset[i]->data_count, element_going_down);
        }

    
        merge(subset[i]->data, subset[i]->data_count, subset[i + 1]->data, subset[i + 1]->data_count);
        merge(subset[i]->subset, subset[i]->child_count, subset[i + 1]->subset, subset[i + 1]->child_count);

        subset[i]->next = subset[i + 1]->next;
        
        delete_item(subset, i + 1, child_count, temp);

        delete temp;

        return nullptr;
    }
};

#endif // BPlusTree_H