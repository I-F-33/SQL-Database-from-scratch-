#ifndef RESULTSET_H
#define RESULTSET_H
#include "token.h"
#include <iostream>
#include <string>
#include "../table/typedefs.h"
#include <algorithm>
#include <set>
using namespace std;

class ResultSet : public Token
{
public:
    ResultSet(vectorlong _recnos) : Token(RESULTSET,"vectorlong"), recnos(_recnos){};

    ResultSet* or_with(ResultSet* other);

    ResultSet* and_with(ResultSet* other);
    
    vector<long> get_recnos() const { return recnos; }

    void Print(ostream &outs = cout) const
    {
        Print(outs);
    }

     virtual TOKEN_TYPES TypeOf()
    {
        return RESULTSET;
    }

private:

    vector<long> recnos;

};

#endif // FUNCTION_H