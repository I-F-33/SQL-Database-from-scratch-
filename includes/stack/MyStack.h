#ifndef MYSTACK_H
#define MYSTACK_H
#include <iostream>
#include <cassert>
#include "../../includes/linked_list_functions/linked_list_functions.h"
#include "../../includes/node/node.h"
using namespace std;

template <typename T>
class Stack
{
public:
    class Iterator
    {
    public:
        friend class Stack;                // give access to list to access _ptr
        Iterator() { _ptr = nullptr; }     // default ctor
        Iterator(node<T> *p) { _ptr = p; } // Point Iterator to where
                                           //   p is pointing to
        T &operator*()                     // dereference operator
        {
            return _ptr->_item;
        }

        T *operator->() // member access operator
        {
            return &_ptr->_item;
        }
        bool is_null() // true if _ptr is NULL
        {
            return _ptr == nullptr;
        }
        friend bool operator!=(const Iterator &left, const Iterator &right) // true if left != right
        {
            return left._ptr != right._ptr;
        }
        friend bool operator==(const Iterator &left, const Iterator &right) // true if left == right
        {
            return left._ptr == right._ptr;
        }
        Iterator &operator++() // member operator:  ++it; or  ++it = new_value
        {

            _ptr = _ptr->_next;
            return *this;
        }

        friend Iterator operator++(Iterator &it, int unused) // friend operator: it++
        {
            ++it;
            return it;
        }

    private:
        node<T> *_ptr; // pointer being encapsulated
    };

    Stack()
    {
        _top = nullptr;
        _size = 0;
    }

    Stack(const Stack<T> &copyMe)
    {
        _top = _copy_list(copyMe._top);
        _size = copyMe.size();
    }

    ~Stack()
    {
        _clear_list(_top);
        _size = 0;
    }

    Stack<T> &operator=(const Stack<T> &RHS)
    {
        if (this == &RHS)
        {
            return *this;
        }

        _clear_list(_top);

        _top = _copy_list(RHS._top);
        _size = RHS.size();

        return *this;
    }

    T top()
    {

        return _top->_item;
    }

    bool empty()
    {
        return _top == nullptr;
    }

    void push(T item)
    {
        _insert_head(_top, item);
        _size++;
    }

    T pop()
    {
        if (_size == 0)
        {
            return T();
        }
        _size--;

        return _delete_node(_top, _top);
    }

    template <typename TT>
    friend ostream &operator<<(ostream &outs,
                               const Stack<TT> &printMe);

    Iterator begin() const // Iterator to the head node
    {
        return _top;
    }
    Iterator end() const // Iterator to NULL
    {
        return nullptr;
    }
    int size() const { return _size; }

private:
    node<T> *_top;
    int _size;
};

template <typename TT>
ostream &operator<<(ostream &outs, const Stack<TT> &printMe)
{
    _print_list(printMe._top);
    return outs;
}
#endif // MYSTACK_H