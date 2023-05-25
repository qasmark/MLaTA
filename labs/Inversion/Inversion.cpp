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
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

void update(vector<int>& bit, int i, int val)
{
    while (i < bit.size())
    {
        bit[i] += val;
        i += i & -i;
    }
}

int sum(vector<int>& bit, int i)
{
    int sm = 0;
    while (i > 0)
    {
        sm += bit[i];
        i -= i & -i;
    }
    return sm;
}

int main()
{

    int n;
    cin >> n;

    vector<int> nums(n);
    vector<int> sortedNums(n);

    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
        sortedNums[i] = nums[i];
    }

    sort(sortedNums.begin(), sortedNums.end());
    vector<int> index(n);
    for (int i = 0; i < n; i++)
    {
        index[i] = lower_bound(sortedNums.begin(), sortedNums.end(), nums[i]) - sortedNums.begin();
    }

    vector<int> bit(n + 1, 0);
    long long inv_count = 0;
    vector<int> inversions(n, 0);
    for (int i = n - 1; i >= 0; i--)
    {
        inv_count += sum(bit, index[i] - 1);
        inversions[i] = inv_count;
        update(bit, index[i], 1);
    }

    cout << inv_count << endl;
    for (int k = 0; k < inversions.size(); k++)
    {
        cout << inversions[k] << " ";
    }

    return 0;
}