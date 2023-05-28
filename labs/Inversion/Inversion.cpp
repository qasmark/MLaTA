/*
    17.1.Инверсии(5)
Задана некоторая перестановка X = (X1, X2, …, XN) чисел от 1 до N.
Требуется найти вектор инверсий и общее количество инверсий в этой перестановке, то есть 
количество пар чисел(i, j) таких, что i < j, а  Xi  > Xj.
Ввод из файла cin.TXT.В первой строке задано число N(1 ≤  N ≤ 500000).
Во второй строке заданы через пробел элементы перестановки X1, X2, …, XN.
Вывод в файл cout.TXT.В первой строке выводится количество инверсий.
Во второй строке – элементы вектора инверсий.
Пример
Ввод
5
2 5 4 1 3
Вывод
6
0 0 1 3 2
	Игнатьев Влад, ПС-22
	Visual Studio Community 2022

Суть решения:
    Используется класс дерева Фенвика, чтобы ффективно обновлять значения и выполнять запросы 
    суммы на префиксном префиксном отрезке массива. До этого я пытался сделать другими методами (MergeSort, RadixSort),
    Однако это не дало такой эффективности, как использование дерева Фенивка в этой задачи. Кстати, нашел в интернете, 
    что дерево Фенвика по-другому называется бинарное индексированное дерево :)
    В классе используется методы Update и Query, затем идет подсчет пар через std::vector<std::pair<int, int>> elements(N)
    Самое трудное было разобраться с перебором, а так все работает.
    Также прилагаю несколько своих тестов и генератор тестов. Можете посмотреть его

    На тесте cin5.txt время выполнения программы 2.944 секунды в Debug, а в сборке Release 0.33, доказательства будут в word
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>

class FenwickTree
{
public:
    FenwickTree(int size) : tree(size + 1, 0) {}

    void Update(int index, int value)
    {
        while (index < tree.size())
        {
            tree[index] += value;
            index += index & -index;
        }
    }

    int Query(int index)
    {
        int sum = 0;
        while (index > 0)
        {
            sum += tree[index];
            index -= index & -index;
        }
        return sum;
    }

private:
    std::vector<int> tree;
};

std::vector<int> CountInversions(const std::vector<int>& permutation, long long& inversionCount)
{
    int N = permutation.size();
    std::vector<int> inversions(N);
    FenwickTree tree(N);

    std::vector<std::pair<int, int>> elements(N);
    for (int i = 0; i < N; ++i)
        elements[i] = std::make_pair(permutation[i], i);

    std::sort(elements.begin(), elements.end());

    for (int i = N - 1; i >= 0; --i)
    {
        inversions[elements[i].second] = tree.Query(elements[i].second);
        tree.Update(elements[i].second + 1, 1);
    }

    inversionCount = 0;
    for (int i = 0; i < inversions.size(); ++i)
        inversionCount += inversions[i];

    return inversions;
}

int main()
{
    time_t start = clock();
    std::ifstream inputFile("cin.txt");
    std::ofstream outputFile("cout.txt");

    int N;
    inputFile >> N;

    std::vector<int> permutation(N);
    for (int i = 0; i < N; ++i)
        inputFile >> permutation[i];

    long long inversionCount;
    std::vector<int> inversions = CountInversions(permutation, inversionCount);

    outputFile << inversionCount << std::endl;
    for (int i = 0; i < inversions.size(); ++i)
    {
        outputFile << inversions[i];
        if (i != inversions.size() - 1)
            outputFile << " ";
    }
    outputFile << std::endl;

    inputFile.close();
    outputFile.close();

    std::cout << "The time execution is " << (double)(clock() - start) / CLOCKS_PER_SEC << " s." << std::endl;
    return 0;
}
