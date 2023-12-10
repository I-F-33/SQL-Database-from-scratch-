#ifndef TOKEN_T_H
#define TOKEN_T_H

#include <iostream>
#include <string>
using namespace std;

class Token_T
{
public:
    // constructors
    Token_T(): _token(""), _type(-1) {};

    Token_T(string str, int type): _token(str), _type(type) {};

    //overloads the output operator
    friend ostream& operator <<(ostream& outs, const Token_T& t)
    {
        outs << t._token;
        return outs;
    }

    //SETTERS
    void set_string(string s)
    {
        _token = s;
    }

    void set_type(int t)
    {
        _type = t;
    }

    //ACCESORS
    int type() const
    {
        return _type;
    }

    string type_string() const
    {
        switch (_type)
        {
        case 1:
            return "NUMBER";
            break;
        case 2:
            return "ALPHA";
            break;
        case 3:
            return "SPACE";
            break;
        case 4:
            return "OPERATOR";
            break;
        case 5:
            return "PUNCTUATION";
            break;
        default:
            return "UNKNOWN";
            break;
        }
    }

    string token_str() const
    {
        return _token;
    }

private:
    string _token;
    int _type;
};

#endif //TOKEN_H