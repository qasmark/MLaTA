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
                // ���� �� �� ��������� (
                while (!opStack.empty() && opStack[opStack.size() - 1] != "(") 
                {
                    // ������ �� ����� ���������� � ����������� ���������
                    postFixExpression.emplace_back(opStack[opStack.size() - 1]);
                    opStack.pop_back();
                }
                if (opStack.empty()) throw std::out_of_range("");
                // �� �������� ������ ( �� ����� ����������
                opStack.pop_back();
            }
            else
            {
                // ���� �� ����� ��������� ����������
                int tokenOpPriority = getOpPriority(token);
                // � ��������� ����� �������
                while (!opStack.empty() && getOpPriority(opStack[opStack.size() - 1]) >= tokenOpPriority)
                {
                // ���� ���� ���������� �� ���� � ������� ����� ���������� ����� �������� �������� ���������� 
                    // � ��� ��� �� �������� �� ������������������
                    
                    //^ ����� ���� ������� ���� �� �����
                    if (token == "^" && (opStack[opStack.size() - 1] == "^"))
                        break;

                    // ����� �� ����� ���������� � ����������� ���������
                    postFixExpression.emplace_back(opStack[opStack.size() - 1]);
                    opStack.pop_back();
                }
                opStack.push_back(token);
            }
        }
    }
    while (opStack.size() > 0) 
    {
        // ����� ���, ��� ��������
        postFixExpression.push_back(opStack[opStack.size() - 1]);
        opStack.pop_back();
    }
    return postFixExpression;
}
