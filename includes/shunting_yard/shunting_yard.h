#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H
#include "../token/token.h"
#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"
#include "../token/operator.h"
#include "../token/logical.h"
#include "../token/relational.h"
#include "../token/tokenstr.h"

#include "../token/constants.h"

class ShuntingYard
{
public:
    ShuntingYard(){};
    ShuntingYard(Queue<Token *> &_infix) : infix_queue(_infix){};

    void infix(Queue<Token *> _infix)
    {
        this->infix_queue = _infix;
    };

    Queue<Token*> postfix();
    Queue<Token *> postfix( Queue<Token*> infix);

private:
    Queue<Token *> infix_queue = {};
};
#endif // SHUNTING_YARD_H