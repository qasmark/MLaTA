#include "convertExpressionToPostFix.h"

convertExpressionToPostFix::convertExpressionToPostFix(const std::vector<std::string>& startExpression)
{
    inFixExpression = startExpression;
}

const std::vector<std::string>& convertExpressionToPostFix::getPostFixExpression()
{
    for (unsigned int i = 0; i < inFixExpression.size(); i++)
    {
        std::string token = inFixExpression[i];
        if (!isOp(token))
            postFixExpression.emplace_back(token);
        else
        {
            if (token == "(")
                opStack.push_back(token);
            else if (token == ")")
            {
                // Пока мы не достигнем (
                while (!opStack.empty() && opStack[opStack.size() - 1] != "(") 
                {
                    // попаем из стека операторов в постфиксное выражание
                    postFixExpression.emplace_back(opStack[opStack.size() - 1]);
                    opStack.pop_back();
                }
                if (opStack.empty()) throw std::out_of_range("");
                // не забываем убрать ( из стека операторов
                opStack.pop_back();
            }
            else
            {
                // если на стеке несколько операторов
                int tokenOpPriority = getOpPriority(token);
                // и приоритет слева направо
                while (!opStack.empty() && getOpPriority(opStack[opStack.size() - 1]) >= tokenOpPriority)
                {
                // пока стек операторов не пуст и вершина стека операторов имеет оператор большего приоритета 
                    // и при это не оператор не правоассоциативный
                    
                    //^ могут быть сложены друг на друга
                    if (token == "^" && (opStack[opStack.size() - 1] == "^"))
                        break;

                    // пушим из стека операторов в постфиксное выражение
                    postFixExpression.emplace_back(opStack[opStack.size() - 1]);
                    opStack.pop_back();
                }
                opStack.push_back(token);
            }
        }
    }
    while (opStack.size() > 0) 
    {
        // пушим все, что осталось
        postFixExpression.push_back(opStack[opStack.size() - 1]);
        opStack.pop_back();
    }
    return postFixExpression;
}
