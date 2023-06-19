#include "BuildingAST.h"

#include<iostream>
#include<stdexcept>

BuildingAST::BuildingAST(const std::vector<std::string>& input)
{
    tokens = input;
};

std::shared_ptr<node> BuildingAST::convertToTree()
{
    for (unsigned int i = 0; i < tokens.size(); i++)
    {
        if (!(tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "/" || tokens[i] == "*" || tokens[i] == "^"))
            expressionTree.emplace_back(new node(tokens[i]));
        else
        {
            // ���� � ��� ��������
            temp = std::make_shared<node>(tokens[i]);
            // � ������ ����� � ������
            temp->right = (expressionTree[expressionTree.size() - 1]);
            expressionTree.pop_back();

            if (expressionTree.size() > 0)
            {
                // � ����� ����� � ������
                temp->left = (expressionTree[expressionTree.size() - 1]);
                expressionTree.pop_back();
            }

            // � ����� ����� � ������
            expressionTree.push_back(temp);
        }

    }
    // �������� ������ � ���������� ���, �� ������� �������� ������
    temp = expressionTree.size() > 0 ? expressionTree[expressionTree.size() - 1] : nullptr;
    expressionTree.resize(0);
    return temp;
}

long double BuildingAST::evaluateExpressionTree(const std::shared_ptr<node>& root)
{
    if (root == nullptr) return 0;
    // ���������� �� ������, ����� ���������� ��������� ���������� ���������
    if (root->data == "+")
        return evaluateExpressionTree(root->left) + evaluateExpressionTree(root->right);
    if (root->data == "-")
    {
        if (root->left == nullptr)
            return -evaluateExpressionTree(root->right);
        else
            return evaluateExpressionTree(root->left) - evaluateExpressionTree(root->right);
    }

    if (root->data == "*")
        return evaluateExpressionTree(root->left) * evaluateExpressionTree(root->right);
    if (root->data == "/")
        return evaluateExpressionTree(root->left) / evaluateExpressionTree(root->right);
    if (root->data == "^")
    {
        long double left = evaluateExpressionTree(root->left);
        long double right = evaluateExpressionTree(root->right);
        long double ans;

        // ������������� ��������� ��� ������� �������
        if (root->left->data.size() > 1 && root->left->data[0] == '-')
        {
            left = abs(left);
            ans = -(pow(left, right));

        }
        // ������������� �������
        else if (root->right->data.size() > 1 && root->right->data[0] == '-')
        {
            return (1 / (pow(left, abs(right))));
        }
        // ������� �������
        else {
            ans = pow(left, right);
        }
        return ans;
    }
    std::string nodeData = root->data;
    double data = stold(nodeData);
    if (data == -0)
        return 0;
    else
        return data;
};