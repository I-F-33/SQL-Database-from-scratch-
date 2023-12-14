#include "shunting_yard.h"

Queue<Token *> ShuntingYard::postfix()
{
    Stack<Token *> operator_stack;
    Queue<Token *> result_queue;

    while (!infix_queue.empty())
    {
        Token *token = infix_queue.pop();

        //if token is a string, push it to the queue
        if (token->TypeOf() == TKSTRING )
        {
            result_queue.push(token);
        }
        //if token is a relational operator, push it to the stack
        else if (token->TypeOf() == RELATIONAL)
        {
            operator_stack.push(token);
            
        }
        //if token is a logical operator, pop all the operators from the stack that have higher precedence and push them to the queue
        else if(token->TypeOf() == LOGICAL)
        {
            if(operator_stack.empty())
            {
                operator_stack.push(token);
            }
            else{
                //while the stack is not empty and the top of the stack is not a left parenthesis
                while(!operator_stack.empty() && operator_stack.top()->TypeOf() != LEFTPAREN)
                {   
                    //if the top of the stack is a logical operator and has higher precedence than the token, push it to the queue
                    if(operator_stack.top()->TypeOf() == LOGICAL)
                    {   
                        //if the top of the stack has higher precedence than the token, push it to the queue
                        if(static_cast<Logical*>(operator_stack.top())->get_prec() > static_cast<Logical*>(token)->get_prec())
                        {
                            result_queue.push(operator_stack.pop());
                        }
                        //if the top of the stack has lower precedence than the token, break out of the loop
                        else
                        {
                            break;
                        }

                    }
                    else
                    {   
                        //if the top of the stack is not a logical operator, push it to the queue
                        result_queue.push(operator_stack.pop());
                    }
                }

                //push the token to the stack
                //top is a left parenthesis
                operator_stack.push(token);
            }
                
            
        }
        //if token is a left parenthesis, push it to the stack
        else if(token->TypeOf() == LEFTPAREN)
        {
            operator_stack.push(token);
        }
        //if token is a right parenthesis, pop all the operators from the stack until a left parenthesis is found and push them to the queue
        else if(token->TypeOf() == RIGHTPAREN)
        {
            while(operator_stack.top()->TypeOf() != LEFTPAREN)
            {
                result_queue.push(operator_stack.pop());
            }

            operator_stack.pop();
        }
        
    }
    //pop all the operators from the stack and push them to the queue
    //if a left parenthesis is found, pop it from the stack and discard it
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
                    if(operator_stack.top()->TypeOf() == LOGICAL)
                    {
                        if(static_cast<Logical*>(operator_stack.top())->get_prec() > static_cast<Logical*>(token)->get_prec())
                        {
                            result_queue.push(operator_stack.pop());
                        }
                        else
                        {
                            break;
                        }

                    }
                    else
                    {
                        result_queue.push(operator_stack.pop());
                    }
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