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