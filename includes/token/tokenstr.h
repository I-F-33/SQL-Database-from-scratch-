#ifndef TOKENSTR_H
#define TOKENSTR_H
#include "token.h"
#include <iostream>
#include <iomanip>
using namespace std;

class TokenStr : public Token
{
public:
    
    TokenStr(string token) : _value(token), Token(TKSTRING, token){};

    virtual void Print(ostream &outs = cout) const
    {

        outs << setprecision(1)  << get_value() << " ";
    }

    virtual TOKEN_TYPES TypeOf()
    {
        return TKSTRING;
    }
    string get_value() const { return _value; }

private:
    string _value;
};

#endif