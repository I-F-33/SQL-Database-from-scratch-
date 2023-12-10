#include "operator.h"
#include <iostream>
#include <cmath>

using namespace std;

Operator::Operator(const string &str) : Token(OPERATOR, str), _operator(str), _type(OPERATOR)
{
    precedence = get_prec();
}


int Operator::get_prec()
{
    if(_operator == "<" || _operator == ">" || _operator == "<=" || _operator == ">=" || _operator == "=" )
    {
        return 1;
    }
    else if(_operator == "and" || _operator == "or")
    {
        return 2;
    }
    return 0;
}
        
        





