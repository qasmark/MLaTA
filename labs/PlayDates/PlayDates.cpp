/*
15.3. Даты (6)
	Играют двое. Задается какая-то дата високосного года, отличная от 31 декабря. 
	Каждый игрок при своем ходе называет более позднюю дату, увеличивая на 1 или 2 либо день в месяце, 
	либо номер месяца, но не оба сразу. При этом сочетание дня и месяца должно оставаться корректной датой. 
	Игрок, назвавший 31 декабря, проигрывает. Оба играют наилучшим образом. По заданной дате вывести, кто выиграет.
	Ввод из файла INPUT.TXT. В первой строке задано количество вариантов N (1 ≤ N ≤ 10). 
	В каждой из следующих N строк находятся через пробел два числа, задающих очередной вариант даты и 
	обозначающие день и месяц.
	Вывод в файл OUTPUT.TXT. Вывести через пробел N значений b1, b2, …bN. 
	Величина bi равна 1, если при i-м варианте выигрывает первый (начинающий) игрок. 
	В противном случае bi = 2.
	Пример
	Ввод
	2
	29 12
	29 11
	Вывод
	1 2
	Пояснение. В первом варианте начинающий игрок называет дату 30 декабря, после чего второй игрок проигрывает.
	Во втором варианте первый игрок может по правилам назвать либо 30 ноября, либо 29 декабря. 
	В каждом из этих случаев второй игрок называет дату 30 декабря и выигрывает.
	
	Игнатьев Влад, ПС-22
	Visual Studio Community 2022
		
Суть решения:
Инициализируем матрицу дней в месяцах в году, начинаем с выигрышной позиции - 30 ноября,
находим все варианты, как мы могли попасть в выигрышную позицию.
Повторяем это действие для всех комбинаций дня и месяца. В итоге получаем матрицу,
в которой размечены выигрышные позиции
Далее мы получаем входные данные и анализируем, в выигрышной или в проигрышной позиции находится игрок,
делающий первый ход.
Так как дней в високосном году 366, а в худшем случае в каждую дату мы можем 4 раза, то количество вариантов
при полном переборе не слишком большое, чтобы использовать перебор. (Хотя в задаче про робота простой перебор не работал)

*/


#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using SolveMtx = vector<vector<bool>>;

struct SolveContext
{
	static const int MONTHS_START = 11;
	static const int DAYS_START = 30;

	SolveContext()
	{
		monthDaysCnt = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

		solveMtx.assign(12, vector<bool>(31));
		solveMtx[MONTHS_START][DAYS_START] = true;
	}
	vector<int> monthDaysCnt;
	SolveMtx solveMtx;
};


void StepSolve(int m, int d, SolveContext& ctx)		
{
	if ((d + 1 < ctx.monthDaysCnt[m] && !ctx.solveMtx[m][d + 1]) ||
		(d + 2 < ctx.monthDaysCnt[m] && !ctx.solveMtx[m][d + 2]) ||
		(m + 1 < 12 && d < ctx.monthDaysCnt[m + 1] && !ctx.solveMtx[m + 1][d]) ||
		(m + 2 < 12 && d < ctx.monthDaysCnt[m + 2] && !ctx.solveMtx[m + 2][d]))
	{
		ctx.solveMtx[m][d] = true;
	}
}

void Solve(SolveContext& ctx)
{
	for (int m = SolveContext::MONTHS_START; m >= 0; m--) {
		for (int d = SolveContext::DAYS_START; d >= 0; d--) {
			if (m == SolveContext::MONTHS_START && d == SolveContext::DAYS_START)
				continue;

			if (d >= ctx.monthDaysCnt[m])
				continue;

			StepSolve(m, d, ctx);
		}
	}
}

int main() {
	ifstream in("input.txt");
	ofstream out("output.txt");

	int n, m, d;
	string ans = "";

	SolveContext ctx;
	Solve(ctx);

	in >> n;
	for (int i = 0; i < n; i++)
	{
		in >> d >> m;
		ans += to_string((ctx.solveMtx[m - 1][d - 1] ? 1 : 2)) + ((i == n - 1)? '\n' : ' ');
	}
	out << ans;

	return 0;
}