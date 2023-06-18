#pragma once
#include <string>
#include <vector>
#include <iomanip>

struct node
{
    node(const std::string& g_data)
    {
        data = g_data;
    }
    ~node() = default;

    std::string data;//the token data i.e. ..., -1, 0, 1, ...
    std::shared_ptr<node> left = nullptr;//The left expression of the token
    std::shared_ptr<node> right = nullptr;//the right expression of the token
};

class Expression_Parser
{
public:
    Expression_Parser(const std::vector<std::string>& input);
    ~Expression_Parser() = default;

    std::shared_ptr<node> toTree();

    long double evaluateExpressionTree(const std::shared_ptr<node>& root);

    std::shared_ptr<node> temp;;//General pointer used for manipulation
    std::vector<std::shared_ptr<node>> expression_tree;//will result in one element pointing to the root of the tree
    std::vector<std::string> tokens;//A list of each postfix expression token
};


