/*
Лабиринт представляет собой квадрат, состоящий из NxN сегментов. Каждый из сегментов может быть либо пустым, либо заполненным монолитной каменной стеной. Гарантируется, что левый верхний и правый нижний сегменты пусты. Лабиринт обнесён сверху, снизу, слева и справа стенами, оставляющими свободными только левый верхний и правый нижний углы. Директор лабиринта решил покрасить стены лабиринта, видимые изнутри (см. рисунок). Помогите ему рассчитать количество краски, необходимой для этого.

Ввод из файла INPUT.TXT. В первой строке находится число N, затем идут N строк по N символов: точка обозначает пустой сегмент, решётка - сегмент со стеной.
Вывод в файл OUTPUT.TXT. Вывести одно число - площадь видимой части внутренних стен лабиринта в квадратных метрах.
Ограничения: 3 ≤ N ≤ 33, размер сегмента 3 x 3 м, высота стен 3 м, время 1 с.
Пример
Ввод
5
.....
...##
..#..
..###
.....
Вывод
198


*/
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Point {
    int x;
    int y;
};

void exploreNeighbours(Point p, vector<vector<char>>& mainVector, int n, int& counter) {
    int dirX[4] = { 0, 0, -1, 1 };
    int dirY[4] = { -1, 1, 0, 0 };

    for (int i = 0; i < 4; i++) {
        Point nextPoint = p;
        nextPoint.x += dirX[i];
        nextPoint.y += dirY[i];

        if ((nextPoint.x == 0 && nextPoint.y == -1) || (nextPoint.x == -1 && nextPoint.y == 0))
            continue;
        if ((nextPoint.x == n && nextPoint.y == n - 1) || (nextPoint.x == n - 1 && nextPoint.y == n))
            continue;

        if (nextPoint.x < 0 || nextPoint.x > n - 1 || nextPoint.y < 0 || nextPoint.y > n - 1 ||
            mainVector[nextPoint.y][nextPoint.x] == '#') {
            counter++;
            continue;
        }

        if (mainVector[nextPoint.y][nextPoint.x] == 'O') {
            continue;
        }

        if (mainVector[nextPoint.y][nextPoint.x] == '.') {
            mainVector[nextPoint.y][nextPoint.x] = 'O';
            exploreNeighbours(nextPoint, mainVector, n, counter);
        }
    }
}

int main() {
    // Чтение входных данных
    ifstream inputFile("INPUT.TXT");
    int N;
    inputFile >> N;

    vector<vector<char>> labyrinth(N, vector<char>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            inputFile >> labyrinth[i][j];
        }
    }
    inputFile.close();

    // Инициализация переменных
    int visibleArea = 0;
    int segmentArea = 3 * 3;  // Площадь одного сегмента (3 x 3)

    // Поиск видимых стен
    Point start = { 0, 0 };
    int counter = 0;
    exploreNeighbours(start, labyrinth, N, counter);
    visibleArea = counter * segmentArea;

    // Запись результата
    ofstream outputFile("OUTPUT.TXT");
    outputFile << visibleArea;
    outputFile.close();

    return 0;
}

