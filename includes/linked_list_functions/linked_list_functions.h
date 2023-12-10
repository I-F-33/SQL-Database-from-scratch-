#ifndef LINKED_LIST_FUNCTIONS_H
#define LINKED_LIST_FUNCTIONS_H
#include "../../includes/node/node.h"
#include <iostream>
using namespace std;

// Linked List General Functions:
template <typename ITEM_TYPE>
void _print_list(node<ITEM_TYPE> *head)
{
    if (head == nullptr)
    {
        cout << "List is empty" << endl;
    }
    // walker for head node
    node<ITEM_TYPE> *current = head;

    // while the current node does equal to a nullptr
    while (current != nullptr)
    {
        // cout the item hte node is pointing to
        cout << current->_item << " ";
        // current is now equal tot he next node
        current = current->_next;
    }
    cout << endl;
}

// recursive fun! :)
template <typename ITEM_TYPE>
void _print_list_backwards(node<ITEM_TYPE> *head)
{
    // if the list is empty then return
    if (head == nullptr)
    {
        return;
    }
    // call the function again with the next node until it reaches hte final node
    _print_list_backwards(head->_next);
    // cout the item of the node
    cout << head->_item << " ";
}

// return ptr to key or NULL
template <typename ITEM_TYPE>
node<ITEM_TYPE> *_search_list(node<ITEM_TYPE> *head, ITEM_TYPE key)
{
    // if the head is a nullptr then return a nullptr
    if (head == nullptr)
    {
        return nullptr;
    }

    // while the head is not equal to the key
    while (head->_item != key && head->_next != nullptr)
    {
        // head is now equal to the next node
        head = head->_next;
    }

    if (head->_item != key)
    {
        return nullptr;
    }
    else
    {
        // return the head which should be the ptr to the key in the list
        return head;
    }
}

template <typename ITEM_TYPE>
node<ITEM_TYPE> *_insert_head(node<ITEM_TYPE> *&head, ITEM_TYPE insert_this)
{

    // New node to be insterted into linked list
    node<ITEM_TYPE> *new_node = new node<ITEM_TYPE>;

    // item for new node is the inssert_this
    new_node->_item = insert_this;

    // new node next piinter is the head
    new_node->_next = head;

    // head is now pointing to the head
    head = new_node;

    // return the head of the linked list
    return head;
}

// insert after ptr
template <typename ITEM_TYPE>
node<ITEM_TYPE> *_insert_after(node<ITEM_TYPE> *&head, node<ITEM_TYPE> *after_this, ITEM_TYPE insert_this)
{
    if (head == nullptr)
    {
        return _insert_head(head, insert_this);
    }

    // new node to be inserted
    node<ITEM_TYPE> *new_node = new node<ITEM_TYPE>;

    // item for new node is insert this
    new_node->_item = insert_this;

    // new node is pointing to the pointer following after_this
    new_node->_next = after_this->_next;

    // After this is now pointing to the new node
    after_this->_next = new_node;

    return new_node;
}

// ptr to previous node
template <typename ITEM_TYPE>
node<ITEM_TYPE> *_previous_node(node<ITEM_TYPE> *head, node<ITEM_TYPE> *prev_to_this)
{

    // check if head is a nullptr
    if (head == nullptr)
    {
        return head;
    }

    // pointer to head
    node<ITEM_TYPE> *current = head;

    // while the next node is not equal to prev_to_this then current is equal tot he next node
    while (current->_next != prev_to_this && current->_next != nullptr)
    {

        current = current->_next;
    }

    // return node previous to this
    return current;
}
// insert before ptr
template <typename ITEM_TYPE>
node<ITEM_TYPE> *_insert_before(node<ITEM_TYPE> *&head, node<ITEM_TYPE> *before_this, ITEM_TYPE insert_this)
{
    if (head == nullptr)
    {
        return nullptr;
    }

    if (before_this == head)
    {
        return _insert_head(head, insert_this);
    }

    // get the node before the before_this
    node<ITEM_TYPE> *before_node = _previous_node(head, before_this);

    // new node to be inserted pointing to before_This as next
    node<ITEM_TYPE> *new_node = new node<ITEM_TYPE>(insert_this, before_this);

    // node before the new node is now pointing at the new node
    before_node->_next = new_node;

    return head;
}

// delete, return item
template <typename ITEM_TYPE>
ITEM_TYPE _delete_node(node<ITEM_TYPE> *&head, node<ITEM_TYPE> *delete_this)
{

    if (delete_this == head)
    {

        head = delete_this->_next;

        ITEM_TYPE return_item = delete_this->_item;

        delete delete_this;

        // return item
        return return_item;
    }

    // get node before delete_This
    node<ITEM_TYPE> *before_delete_this = _previous_node(head, delete_this);

    before_delete_this->_next = delete_this->_next;

    // item to be returned
    ITEM_TYPE return_item = delete_this->_item;

    // delete node
    delete delete_this;

    // return item
    return return_item;
}

// duplicate the list...
template <typename ITEM_TYPE>
node<ITEM_TYPE> *_copy_list(node<ITEM_TYPE> *head)
{

    bool debug = false;

    if (head == nullptr)
    {
        return nullptr;
    }

    // new head node for new list
    node<ITEM_TYPE> *new_head = new node<ITEM_TYPE>;

    // new head item is the item of hte head of original list
    new_head->_item = head->_item;

    // original list walker is pointing to original head
    node<ITEM_TYPE> *original_list = head;

    // duplicate list walker is pointing to new head
    node<ITEM_TYPE> *new_list = new_head;

    // while the next item in the original list is not a nullptr
    while (original_list->_next != nullptr)
    {
        // original walker is equal to the next node
        original_list = original_list->_next;
        // duplicate walkers next item is a new node
        new_list->_next = new node<ITEM_TYPE>;

        // duplicate walker is now equal to the new node
        new_list = new_list->_next;

        // item of the duplicate walker is now the item of the original walker
        new_list->_item = original_list->_item;
    }

    // end of list = nullptr
    new_list->_next = nullptr;

    // return the head of new list
    return new_head;
}

// duplicate list and return the last node of the copy
template <typename T>
node<T> *_copy_list(node<T> *&dest, node<T> *src)
{

    if (src == nullptr)
    {
        return nullptr;
    }

    // copy the list
    dest = _copy_list(src);

    // copy of the dest
    node<T>* dest_copy = dest;

    // while the next node is not a nullptr
    while (dest_copy->_next != nullptr)
    {
        dest_copy = dest_copy->_next;
    }

    // return the last node of the copy
    return dest_copy;
}

// delete all the nodes
template <typename ITEM_TYPE>
void _clear_list(node<ITEM_TYPE> *&head)
{

    // head / current node
    node<ITEM_TYPE> *walker_node = head;

    // next node
    node<ITEM_TYPE> *next_walker;

    // while the next node is not null ptr
    while (walker_node != nullptr)
    {
        // next node is pointing to the node after the walker_node
        next_walker = walker_node->_next;

        // delete the walker
        delete walker_node;

        // walker is now the next node
        walker_node = next_walker;
    }

    // set head to null
    head = nullptr;
}

//_item at this position
template <typename ITEM_TYPE>
ITEM_TYPE &_at(node<ITEM_TYPE> *head, int pos)
{

    // walker and move to the desired position
    node<ITEM_TYPE> *walker = head;
    for (int i = 0; i < pos; i++)
    {
        walker = walker->_next;
    }

    // return the address of the item at walker
    return walker->_item;
}

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//      Sorted List Routines. order: 0: ascending, order: other: descending .
//                              Assume a Sorted List                        .
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

template <typename ITEM_TYPE>
node<ITEM_TYPE> *_insert_sorted(node<ITEM_TYPE> *&head, ITEM_TYPE item, bool ascending = true) // insert
{
    node<ITEM_TYPE> *node_used = _where_this_goes(head, item, ascending);

    // if where this goes returned a nullptr then insert at the head
    if (node_used == nullptr)
    {
        return _insert_head(head, item);
    }

    if (ascending)
    {
        return _insert_before(head, node_used, item);
    }
    else
    {
        // insert before the node
        return _insert_after(head, node_used, item);
    }
}

// insert or add if a dup
template <typename ITEM_TYPE>
node<ITEM_TYPE> *_insert_sorted_and_add(node<ITEM_TYPE> *&head, ITEM_TYPE item, bool ascending = true)
{
    // if the item is not in the list then insert it
    if (_search_list(head, item) == nullptr)
        ;
    {
        return _insert_sorted(head, item, ascending);
    }

    node<ITEM_TYPE> *head_copy = head;

    // first time ive ever used a while loop
    // move to hte next node while item at the node is not equal to the item being inserted
    do
    {
        head_copy = head_copy->_next;
    } while (head_copy->_item != item);

    // add the item to the item at the node
    head_copy->_item = head_copy->_item + item;

    // return the head
    return head_copy;
}
// node after which this item goes order: 0 ascending
template <typename ITEM_TYPE>
node<ITEM_TYPE> *_where_this_goes(node<ITEM_TYPE> *head, ITEM_TYPE item, bool ascending = true)
{

    if (head == nullptr)
    {

        return nullptr;
    }
    if (ascending)
    {
        // if the item is smaller than the head item then return a nullptr
        if (item < head->_item)
        {
            return nullptr;
        }

        // while next node is no a nullptr
        while (head->_next != nullptr)
        {

            // if the head item is smaller than or equal to item AND the next head item is greater than item
            if (head->_item <= item && head->_next->_item > item)
            {
                // then return this node
                return head;
            }

            // move to next node
            head = head->_next;
        }

        return head;
    }
    else
    {

        // if the item is smaller than the head item then return a nullptr
        if (item > head->_item)
        {
            return nullptr;
        }

        // while next node is no a nullptr
        // if the head item is greater than or equal to item AND the next head item is smaller than item
        // then return this node
        while (head->_next != nullptr)
        {
            if (head->_item >= item && head->_next->_item < item)
            {
                return head;
            }
            head = head->_next;
        }

        return head;
    }
}
// Last Node in the list
template <typename ITEM_TYPE>
node<ITEM_TYPE> *_last_node(node<ITEM_TYPE> *head) // never use this function.
{
    // while the next node is not a nullptr then increment to he next node
    while (head->next != nullptr)
    {
        head = head->_next;
    }

    return head;
}
#endif