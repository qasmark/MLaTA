/*
14.18. Вычисление выражения (7)
	Во входной строке записано арифметическое выражение, состоящее из целых чисел и знаков операций «+», «-», «*», «/», «(», «)», «^». 
	Пробелы в выражении отсутствуют. Требуется написать программу, которая вычислит значение данного выражения.
	Ввод. 
	Входной файл INPUT.TXT содержит одну строку, состоящую не более чем из 255 символов. Числа в выражении не превышают по модулю 2×10^9. 
	Гарантируется, что в процессе вычислений получаемые значения не превышают по модулю 2×10^9.
	Вывод. В единственной строке файла OUTPUT.TXT требуется вывести значение выражения с точностью 4 знака после запятой.

Примеры

Ввод 1
1+2*3^(1-2/3^4)
Вывод 1
6.8394

Ввод 2
(1/2+2/3)*(3/4-4/5)*1000
Вывод 2
-58.3333

	Игнатьев Владислав, ПС-22
	Visual Studio Community 2022
*/

#include "ParsingString.h"
#include "BuildingAST.h"
#include "ConvertExpressionToPostFix.h"

int main()
{
	std::ifstream fin("example2.txt");
	std::ofstream fout("output.txt");

	
	toPostFix expr(getMathExpression(fin));

	Expression_Parser AST(expr.getPostFixExpression());

	std::shared_ptr<node> expressionTree = AST.toTree();

	fout << std::fixed << std::setprecision(4) << AST.evaluateExpressionTree(expressionTree) << std::endl;
}