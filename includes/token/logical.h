#ifndef LOGICAL_H
#define LOGICAL_H
#include <iostream>
#include <string>
#include "relational.h"
using namespace std;

class Logical : public Token
{
public:
    Logical(string logical) : Token(LOGICAL, logical),  _logical(logical){};

    string get_logical() const { return _logical; }

    int get_prec() const
    {
        if(_logical == "and" || _logical == "AND")
        {
            return 1;
        }
        else if(_logical == "or" || _logical == "OR")
        {
            return 2;
        }
        else
        {
            cout << "What is this??" << endl;
        }
        return -1;
    }

    ResultSet* eval(ResultSet* left, ResultSet* right); // TODO: implement

    void Print(ostream &outs = cout) const
    {
        Print(outs);
    }

     virtual TOKEN_TYPES TypeOf()
    {
        return LOGICAL;
    }

private:

    string _logical;

};

#endif // FUNCTION_H