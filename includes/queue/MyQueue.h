#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include "../linked_list_functions/linked_list_functions.h"
#include "../node/node.h"
#include <cassert>
using namespace std;

template <typename T>
class Queue
{
public:
    class Iterator
    {
    public:
        friend class Queue; // give access to list to access _ptr
        Iterator()
        {
            _ptr = nullptr;
        } // default ctor
        Iterator(node<T> *p)
        {
            _ptr = p;
        } // Point Iterator to where
        //...                        //  p is pointing to
        T &operator*()
        { // dereference operator
            return _ptr->_item;
        }
        T *operator->()
        { // member access operator
            return &_ptr->_item;
        }
        bool is_null()
        { // true if _ptr is NULL
            return _ptr == nullptr;
        }
        friend bool operator!=(const Iterator &left, const Iterator &right)
        { // true if left != right
            return left._ptr != right._ptr;
        }

        friend bool operator==(const Iterator &left, const Iterator &right)
        { // true if left == right
            return left._ptr == right._ptr;
        }

        Iterator &operator++()
        { // member operator:
            _ptr = _ptr->_next;
            return *this;
        } //  ++it; or
          //  ++it = new_value

        friend Iterator operator++(Iterator &it, int unused)
        { // friend operator: it++
            ++it;
            return it;
        }

    private:
        node<T> *_ptr; // pointer being encapsulated
    };

    Queue()
    {
        _front = nullptr;
        _rear = nullptr;
        _size = 0;
    }

    Queue(const Queue<T> &copyMe)
    {
        _rear = _copy_list(_front, copyMe._front);
        _size = copyMe._size;
    }

    ~Queue()
    {
        _clear_list(_front);
    }
    Queue &operator=(const Queue<T> &RHS)
    {
        if (this == &RHS)
        {
            return *this;
        }
        _clear_list(_front);
        _rear = _copy_list(_front, RHS._front);
        _size = RHS._size;
        return *this;
    }

    bool empty()
    {
        return _front == nullptr;
    }
    T front()
    {
        return _front->_item;
    }
    T back()
    {
        return _rear->_item;
    }

    void push(T item)
    {
        node<T> *holder = _insert_after(_front, _rear, item);
        _rear = holder;
        _size++;
    }
    T pop()
    {
        // find prev to rear
        //  have prev point to null
        // delete rear
        //  update rear
        node<T> *holder = _front->_next;
        T item = _delete_node(_front, _front);
        _front = holder;
        _size--;
        return item;
    }

    Iterator begin() const
    {
        return _front;
    } // Iterator to the head node
    Iterator end() const
    {
        return nullptr;
    } // Iterator to NULL
    void print_pointers()
    {
        _print_list(_front);
    }
    int size() const
    {
        return _size;
    }
    template <typename TT>
    friend ostream &operator<<(ostream &outs, const Queue<TT> &printMe);

private:
    node<T> *_front;
    node<T> *_rear;
    int _size;
};
template <typename U>
ostream &operator<<(ostream &outs, const Queue<U> &printMe)
{
    outs << "Queue:Head-> ";
    for (node<U> *begin = printMe._front; begin != nullptr; begin = begin->_next)
    {
        outs << "[" << begin->_item << "]  ->";
    }
    outs << endl;
    return outs;
}

#endif