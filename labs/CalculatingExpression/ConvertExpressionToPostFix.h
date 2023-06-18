#pragma once
#include <iostream>

#include "ParsingString.h"

class convertExpressionToPostFix
{
public:
    convertExpressionToPostFix(const std::vector<std::string>& startExpression);

    ~convertExpressionToPostFix() = default;

    const std::vector<std::string>& getPostFixExpression();


private:
    std::vector<std::string> inFixExpression;

    std::vector<std::string> postFixExpression;

    std::vector<std::string> opStack;
};

