#include "rpn.h"

RPN::RPN()
{
}

RPN::RPN(Queue<Token *> tokens,Map<std::string, int> _field_names, vector<MMap<std::string, long> >_table) : _tokens(tokens),table(_table),field_names(_field_names){};

void RPN::set_input(Queue<Token *> tokens, Map<std::string, int> _field_names, vector<MMap<std::string, long> >_table)
{
    _tokens = tokens;
    field_names = _field_names;
    table = _table;
}

vectorlong RPN::operator()()
{
    Stack<Token *> stack;
    Stack<ResultSet*> result_stack;


    ResultSet* result;    

    while (!_tokens.empty())
    {
        Token *token = _tokens.pop(); 


        if (token->TypeOf() == TKSTRING)
        {
            stack.push(token);
        }
        else if (token->TypeOf() == RELATIONAL)
        {
            
            Token *rightvar = stack.pop();
            Token *leftvar = stack.pop();

            result = static_cast<Relational *>(token)->eval(field_names,table,leftvar, rightvar);

            result_stack.push(result);
        }
        else if(token->TypeOf() == LOGICAL)
        {

            result = static_cast<Logical*>(token)->eval(result_stack.pop(), result_stack.pop());

            result_stack.push(result);
        }
        

    }

    ResultSet* res = result_stack.pop();

    vectorlong result_records = res->get_recnos();

    return result_records;
}