#include "logical.h"

    ResultSet* Logical::eval(ResultSet* left, ResultSet* right)
    {
        ResultSet* result;
        if(_logical == "AND" ||_logical == "and")
        {
            result = left->and_with(right);
        }
        else if(_logical == "OR" || _logical == "or")
        {
            result = left->or_with(right);
        }

        return result;
    }
