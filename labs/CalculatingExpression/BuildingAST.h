#pragma once
#include <string>
#include <vector>
#include <iomanip>

struct node
{
    node(const std::string& number)
    {
        data = number;
    }
    ~node() = default;

    std::string data;
    std::shared_ptr<node> left = nullptr;
    std::shared_ptr<node> right = nullptr;
};

class BuildingAST
{
public:
    BuildingAST(const std::vector<std::string>& input);
    ~BuildingAST() = default;

    std::shared_ptr<node> convertToTree();

    long double evaluateExpressionTree(const std::shared_ptr<node>& root);

    std::shared_ptr<node> temp;
    std::vector<std::shared_ptr<node>> expressionTree; // для корня дерева
    std::vector<std::string> tokens; // лист токенов
};


