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

        //if token is a string, push it to the stack
        if (token->TypeOf() == TKSTRING)
        {
            stack.push(token);
        }
        //if token is a relational operator, pop two strings from the stack and evaluate the relational operator
        else if (token->TypeOf() == RELATIONAL)
        {
            
            Token *rightvar = stack.pop();
            Token *leftvar = stack.pop();

            result = static_cast<Relational *>(token)->eval(field_names,table,leftvar, rightvar);

            result_stack.push(result);
        }
        //if token is a logical operator, pop two resultsets from the stack and evaluate the logical operator
        else if(token->TypeOf() == LOGICAL)
        {

            result = static_cast<Logical*>(token)->eval(result_stack.pop(), result_stack.pop());

            result_stack.push(result);
        }
        

    }

    vectorlong result_records = result_stack.pop()->get_recnos();

    return result_records;
}