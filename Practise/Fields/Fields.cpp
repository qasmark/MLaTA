#include <iostream>
#include <vector>
#include <fstream>

using Field = std::vector<std::vector<char>>;


void grille(Field& field, long long row, long long column)
{
	if (field[row][column] == '#')
	{
		field[row][column] = '.';
		grille(field, row + 1, column);
		grille(field, row - 1, column);
		grille(field, row, column + 1);
		grille(field, row, column - 1);
	}
}

void solve()
{
	int N, M;
	std::cin >> N >> M;

	Field field(N + 2, std::vector<char>(M + 2, '.'));
	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= M; ++j)
		{
			std::cin >> field[i][j];
		}
	};

	int result = 0;

	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= M; ++j)
		{
			if (field[i][j] == '#')
			{
				result++;
				grille(field, i, j);
			}
		}
	};

	std::cout << result << '\n';
}

//Field InitField(std::string path)
//{
//	std::fstream fin;
//	Field field;
//	int N, M;
//
//	fin.open(path);
//	fin >> N >> M;
//	for (int i = 0; i <= N; i++)
//	{
//		for (int j = 0; i <= M; j++)
//		{
//			fin >> field[i][j];
//		}
//	}
//
//	return field;
//}

int main()
{
	//Field field = InitField("input.txt");

	solve();

	return 0;
}