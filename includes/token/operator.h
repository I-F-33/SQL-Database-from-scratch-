#ifndef OPERATOR_H
#define OPERATOR_H
#include <cmath>
#include "token.h"
#include <iostream>
#include <string>


class Operator : public Token
{
public:
    Operator(const string &str);

    int get_prec();

    virtual void Print(ostream &outs = cout) const
    {
        outs <<  get_value() << " ";
    }

    virtual TOKEN_TYPES TypeOf()
    {
        return OPERATOR;
    }

    string get_operator() const { return _operator; }

private:
    int precedence;
    string _operator;
    TOKEN_TYPES _type;
};

#endif