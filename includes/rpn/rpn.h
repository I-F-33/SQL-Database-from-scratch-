#ifndef RPN_H
#define RPN_H

#include "../../includes/queue/MyQueue.h"
#include "../../includes/stack/MyStack.h"
#include "../../includes/token/relational.h"
#include "../../includes/token/logical.h"   
#include "../../includes/token/leftparen.h"
#include "../../includes/token/rightparen.h"


using namespace std;

class RPN
{
    public:

        RPN();

        RPN(Queue<Token*> &tokens, Map<std::string, int> _field_names, vector<MMap<std::string, long> >_table);

        void set_input(Queue<Token*> &tokens, Map<std::string, int> _field_names, vector<MMap<std::string, long> >_table);

        vector<long> operator()();

    private:
    
            Queue<Token*> _tokens = {};
            Map<std::string, int> field_names = {};
            vector<MMap<std::string, long> >table = {};

};
#endif // RPN_H