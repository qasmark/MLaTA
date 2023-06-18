#pragma once

#include <string>
#include <vector>
#include <fstream>

const std::vector<std::string> getMathExpression(std::ifstream& fin);

const int getOpPriority(const std::string& op);

const bool isOp(const std::string& op);