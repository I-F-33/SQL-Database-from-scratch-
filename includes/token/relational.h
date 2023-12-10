#ifndef RELATIONAL_H
#define RELATIONAL_H
#include <iostream>
#include <string>
#include "tokenstr.h"
#include "resultset.h"
using namespace std;


class Relational : public Token
{
public:
    Relational(string relation) : Token(RELATIONAL,relation),  _relation(relation){};

    string get_function() const { return _relation; }

    ResultSet* eval(Map<string,int> field_names, vector<MMap<string,long> > _table, Token* left, Token* right);

    void Print(ostream &outs = cout) const
    {
        Print(outs);
    }

     virtual TOKEN_TYPES TypeOf()
    {
        return RELATIONAL;
    }

private:

    string _relation;

};

#endif // FUNCTION_H