#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>

struct ppl
{
	int time;
	int steps;
	int order;
	int timeMultSteps;
};

int main()
{
	std::ifstream fin("in2.txt");
	std::ofstream fout("output.txt");
	int N;

	fin >> N;
	std::vector<ppl> ppls;
	ppls.resize(N);

	for (int i = 0; i < N; i++)
	{
		fin >> ppls[i].time >> ppls[i].steps;
		ppls[i].order = i;
	}

	std::sort(ppls.begin(), ppls.end(), [](const ppl& left, const ppl& right)
		{
			return left.steps < right.steps;
		});
	
	ppls[0].timeMultSteps = ppls[0].time * ppls[0].steps;

	for (int i = 1; i < N; i++)
	{
		ppls[i].timeMultSteps = std::max(ppls[i].time * ppls[i].steps, ppls[i - 1].timeMultSteps);
	}

	std::sort(ppls.begin(), ppls.end(), [](const ppl& left, const ppl& right)
		{
			return left.order < right.order;
		});

	for (int i = 0; i < N; i++)
	{
		fout << ppls[i].timeMultSteps << std::endl;
	}

	return 0;
}