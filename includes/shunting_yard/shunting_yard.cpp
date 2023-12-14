#include "shunting_yard.h"

Queue<Token *> ShuntingYard::postfix()
{
    Stack<Token *> operator_stack;
    Queue<Token *> result_queue;

    while (!infix_queue.empty())
    {
        Token *token = infix_queue.pop();

        
        if (token->TypeOf() == TKSTRING )
        {
            result_queue.push(token);
        }
        else if (token->TypeOf() == RELATIONAL)
        {
            operator_stack.push(token);
            
        }
        else if(token->TypeOf() == LOGICAL)
        {
            if(operator_stack.empty())
            {
                operator_stack.push(token);
            }
            else{
                while(!operator_stack.empty() && operator_stack.top()->TypeOf() != LEFTPAREN)
                {
                    result_queue.push(operator_stack.pop());
                }

                operator_stack.push(token);
            }
                
            
        }
        else if(token->TypeOf() == LEFTPAREN)
        {
            operator_stack.push(token);
        }
        else if(token->TypeOf() == RIGHTPAREN)
        {
            while(operator_stack.top()->TypeOf() != LEFTPAREN)
            {
                result_queue.push(operator_stack.pop());
            }

            operator_stack.pop();
        }
        
    }
    while (!operator_stack.empty())
    {
        if(operator_stack.top()->TypeOf() != LEFTPAREN && operator_stack.top()->TypeOf() != RIGHTPAREN)
            result_queue.push(operator_stack.pop());
        else
        operator_stack.pop();
    }

    return result_queue;
}

Queue<Token *> ShuntingYard::postfix(Queue<Token *> infix)
{
    Stack<Token *> operator_stack;
    Queue<Token *> result_queue;

    while (!infix.empty())
    {
        Token *token = infix_queue.pop();

        if (token->TypeOf() == TKSTRING )
        {
            result_queue.push(token);
        }
        else if (token->TypeOf() == RELATIONAL)
        {
            operator_stack.push(token);
            
        }
        else if(token->TypeOf() == LOGICAL)
        {
            if(operator_stack.empty())
            {
                operator_stack.push(token);
            }
            else{
                while(!operator_stack.empty() && operator_stack.top()->TypeOf() != LEFTPAREN)
                {
                    result_queue.push(operator_stack.pop());
                }

                operator_stack.push(token);
            }
                
            
        }
        else if(token->TypeOf() == LEFTPAREN)
        {
            operator_stack.push(token);
        }
        else if(token->TypeOf() == RIGHTPAREN)
        {
            while(operator_stack.top()->TypeOf() != LEFTPAREN)
            {
                result_queue.push(operator_stack.pop());
            }
        }
        
    }
    while (!operator_stack.empty())
    {
        result_queue.push(operator_stack.pop());
    }

    return result_queue;
}