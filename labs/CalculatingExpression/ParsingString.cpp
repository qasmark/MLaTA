#include "ParsingString.h"

const std::vector<std::string> getMathExpression(std::ifstream& fin)
{
	std::string input;
    std::vector<std::string> mathExpression;
    std::string buildString = "";
    char ch;

	fin >> input;

    for (unsigned int i = 0; i < input.size(); i++)
    {
        ch = input[i];
        if ((i == 0 || (input.size() > 0 && input[i - 1] == '(')) && ch == '-')
            // добавление - для отрицательности числа
            buildString += '-';

        else if (isdigit(ch))
            buildString += ch;

        else if (ch == '^' || ch == '*' || ch == '/' || ch == '+' || ch == '-' || ch == '(' || ch == ')')
        {
            // проверка на унарный минус
            if ((i >= 1 && ch == '-') && (input[i - 1] == '^' || input[i - 1] == '*' || input[i - 1] == '/' ||
                    input[i - 1] == '+' || input[i - 1] == '-'))
                buildString += "-";
            // иначе бинарный оператор
            else
            {
                if (buildString.size() > 0)
                {
                    mathExpression.push_back(buildString);
                    buildString = "";
                }
                buildString += ch;
                mathExpression.push_back(buildString);
                buildString = "";
            }
        }
    }

    if (buildString.size() > 0)
        mathExpression.push_back(buildString);

    for (int i = 0; i < mathExpression.size(); i++)
    {
        if ((mathExpression.size() - i) < 3)
            break;

        const std::string&
            token_one = mathExpression[i],
            token_two = mathExpression[i + 1],
            token_three = mathExpression[i + 2];

        if (isOp(token_one) && token_two == "-" && token_three == "(")
        {
            // убираем обратную скобку у "-"
            mathExpression.erase(mathExpression.begin() + i + 1);

            // делаем костыль для унарного минуса
            mathExpression.insert(mathExpression.begin() + i + 2, "-1");

            mathExpression.insert(mathExpression.begin() + i + 3, "*");

            mathExpression.insert(mathExpression.begin() + i + 4, "(");

            int bracket_alt = 0;

            for (size_t j = i + 5; j < mathExpression.size(); j++)
            {
                if (mathExpression[j] == "(") bracket_alt += 1;
                else if (mathExpression[j] == ")") bracket_alt -= 1;

                if (bracket_alt == -1)
                {
                    mathExpression.insert(mathExpression.begin() + j, ")");
                    break;
                }

            }
        }

    }

    return mathExpression;
}


const int getOpPriority(const std::string&  op)
{
    if (op == "^")
        return 4;
    if (op == "*")
        return 3;
    if (op == "/")
        return 3;
    if (op == "+")
        return 2;
    if (op == "-")
        return 2;
    if (op == "(")
        return 1;
    if (op == ")")
        return 1;
    else
        return 0;

}

const bool isOp(const std::string& op)
{
    if (op == "^")
        return true;
    if (op == "*")
        return true;
    if (op == "/")
        return true;
    if (op == "+")
        return true;
    if (op == "-")
        return true;
    if (op == "(")
        return true;
    if (op == ")")
        return true;
    return false;
}