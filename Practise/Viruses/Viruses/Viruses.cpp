#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;
	
int BFS(vector<vector<int>>& field, int infectedCellsCount)
{
	int stepsCount = 0;

	while (infectedCellsCount < field.size() * field.size())
	{
		++stepsCount;
		for (int x = 0; x < field.size(); ++x)
		{
			for (int y = 0; y < field.size(); ++y)
			{
				if (field[x][y] == stepsCount)
				{
					if (x > 0 && field[x - 1][y] == 0)
					{
						field[x - 1][y] = stepsCount + 1;
						++infectedCellsCount;
					}

					if (x < field.size() - 1 && field[x + 1][y] == 0)
					{
						field[x + 1][y] = stepsCount + 1;
						++infectedCellsCount;
					}

					if (y > 0 && field[x][y - 1] == 0)
					{
						field[x][y - 1] = stepsCount + 1;
						++infectedCellsCount;
					}

					if (y < field.size() - 1 && field[x][y + 1] == 0)
					{
						field[x][y + 1] = stepsCount + 1;
						++infectedCellsCount;
					}
				}
			}
		}
	}

	return stepsCount;
}

int main()
{
	time_t start = clock();

	fstream fin;
	int N;
	int M;
	fin.open("input10.txt");
	fin >> N >> M;

	vector<vector<int>> field(N, vector<int>(N, 0));
	for (int i = 0; i < M; ++i)
	{
		int x;
		int y;

		fin >> x >> y;
		field[x - 1][y - 1] = 1;
	}

	cout << BFS(field, M) << '\n';
	cout << "The time execution is " << double(clock() - start) / CLOCKS_PER_SEC << " s.	\n";
}