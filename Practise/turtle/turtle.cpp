#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int SearchMin(std::vector<std::vector<int>>& field1, std::vector<std::vector<int>>& field2, int M, int N, std::vector <std::pair<int, int>>& way)
{
    for (int m = 1; m < N; m++)
    {
        field1[0][m] = field1[0][m - 1] + field2[0][m];
    }
    for (int i = 1; i < M; i++)
    {
        field1[i][0] = field1[i - 1][0] + field2[i][0];
    }
    for (int m = 1; m < M; m++)
    {
        for (int i = 1; i < N; i++)
        {
            field1[m][i] = field2[m][i] + std::min(field1[m - 1][i], field1[m][i - 1]);
        }
    }
    return field1[M - 1][N - 1];
}

int main()
{
    std::ifstream fileInput("input5.txt");
    std::ofstream fileOutput("output.txt");
    if (!fileInput)
    {
        std::cout << "Ð¤Ð°Ð¹Ð» Ð½Ðµ Ð¾Ñ‚ÐºÑ€Ñ‹Ñ‚" << std::endl;
        return 1;
    }
    int M, N;
    fileInput >> M >> N;
    std::vector<std::vector<int>> field1(M, std::vector<int>(N));
    std::vector<std::vector<int>> field2(M, std::vector<int>(N));
    for (int m = 0; m < M; m++)
    {
        for (int i = 0; i < N; i++)
        {
            fileInput >> field1[m][i];
            field2[m][i] = field1[m][i];
        }
    }
    int minDistance;
    std::vector <std::pair<int, int>> way;
    minDistance = SearchMin(field1, field2, M, N, way);
    int j = M - 1, k = N - 1;
    way.push_back({ j + 1, k + 1 });
    while (j > 0 || k > 0) {
        if (j == 0) k--;
        else if (k == 0) j--;
        else if (field1[j - 1][k] < field1[j][k - 1]) j--;
        else k--;
        way.push_back({ j + 1, k + 1 });
    }
    std::reverse(way.begin(), way.end());
    fileOutput << minDistance << std::endl;
    for (int m = 0; m < way.size(); m++)
    {
        fileOutput << way[m].first << " " << way[m].second << std::endl;
    }
}
