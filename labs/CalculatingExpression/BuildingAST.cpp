#include "BuildingAST.h"

#include<iostream>
#include<stdexcept>

BuildingAST::BuildingAST(const std::vector<std::string>& input)
{
    tokens = input;
};

std::shared_ptr<node> BuildingAST::convertToTree()
{
    try {
        for (unsigned int i = 0; i < tokens.size(); i++)
        {
            if (!(tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "/" || tokens[i] == "*" || tokens[i] == "^"))
                expressionTree.emplace_back(new node(tokens[i]));
            else
            {
                if (tokens[i] == "cos" ||//if the token is a function
                    tokens[i] == "tan" ||
                    tokens[i] == "sin") {


                    temp = std::make_shared<node>((tokens[i]));//create a new node
                    temp->right = expressionTree[expressionTree.size() - 1];//have the right tree contain the furthest token in the vector
                    expressionTree.pop_back();//take the furthest token in the vector away
                    expressionTree.push_back(temp);//put the new token in the vector
                }

                else//if the token is an operator
                {
                    temp = std::make_shared<node>(tokens[i]);//create a new node
                    temp->right = (expressionTree[expressionTree.size() - 1]);//have the right tree set to the furthest token in the vector
                    expressionTree.pop_back();//take the furthest token in the vector away

                    if (expressionTree.size() > 0)
                    {
                        temp->left = (expressionTree[expressionTree.size() - 1]);//have the left tree set to the furthest token in the vector
                        expressionTree.pop_back();//take the furthest token in the vector away
                    }

                    expressionTree.push_back(temp);//put the new token in the vector
                }
            }

        }
        temp = expressionTree.size() > 0 ? expressionTree[expressionTree.size() - 1] : nullptr;//get the root node of the expression tree
        expressionTree.resize(0);//reset the expression tree
        return temp;//return the root node of the expression tree
    }


    catch (std::out_of_range)
    {
        std::cout << "ERROR : OUT OF BOUNDS" << std::endl;
        return nullptr;
    }
}

long double BuildingAST::evaluateExpressionTree(const std::shared_ptr<node>& root)
{
    if (root == nullptr) return 0;
    //Evaluate each token as they should be evaluated using a recursive approach. This will result in a final answer
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

        //if left token is negative evaulate the operator by inverting the while expression after taking the abs of the left token
        //This takes priority over -powers
        if (root->left->data.size() > 1 && root->left->data[0] == '-')
        {
            left = abs(left);
            ans = -(pow(left, right));

        }
        //If the power is negative then take the reciprocal of the power by taking the left ^ abs (right) /1
        else if (root->right->data.size() > 1 && root->right->data[0] == '-')
        {
            return (1 / (pow(left, abs(right))));
        }
        //If neither tokens are negative then evaluate it the normal way i.e n*n*n...
        else {
            ans = pow(left, right);
        }
        return ans;
    }
    if (root->data == "cos")
        return cos(evaluateExpressionTree(root->right));
    if (root->data == "sin")
        return sin(evaluateExpressionTree(root->right));
    if (root->data == "tan")
        return tan(evaluateExpressionTree(root->right));

    try
    {
        std::string nodeData = root->data;
        double data = stold(nodeData);
        if (data == -0)
            return 0;
        else
            return data;
    }
    catch (std::invalid_argument)
    {
        std::cout << "ERROR : INVALID ARGUMENT" << std::endl;
        return 0;
    }
    //if not a function or operator then return the data in the node
};