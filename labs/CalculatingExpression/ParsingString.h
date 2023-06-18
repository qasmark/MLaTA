#pragma once

#include <string>
#include <vector>
#include <fstream>

const std::vector<std::string> getMathExpression(std::ifstream& fin);

const int getOperatorPrecedance(const std::string& givenOperator);

const bool isOperator(const std::string& givenOperator);