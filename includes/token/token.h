#ifndef TOKEN_H
#define TOKEN_H
#include <iostream>
#include <string>
using namespace std;
#include "constants.h"

class Token
{
public:
    Token();
    Token(TOKEN_TYPES type, string value = "i");

    friend ostream &operator<<(ostream &outs, const Token &token)
    {
        outs << token.get_value() << " ";
        return outs;
    }
    virtual void Print(ostream &outs = cout) const
    {
    }
    virtual TOKEN_TYPES TypeOf()
    {
        return _type;
    }
    string get_value() const { return _value; }

    void set_string(string str) { _value = str; }

    void set_type(int type) { int_type = type; }

private:
    TOKEN_TYPES _type;
    string _value;
    int int_type;
};

#endif // TOKEN_H
