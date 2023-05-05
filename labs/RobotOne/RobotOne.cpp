/* 
3.2. Робот 1 (5). 
Робот находится на расстоянии X шагов от цели. За один ход он продвигается либо к цели, либо 
в противоположном направлении. 
Если он достигает цели, то немедленно останавливается. Найти количество способов достижения цели ровно за Y шагов.
Ввод из файла INPUT.TXT. В единственной строке находятся X и Y (1 ≤ X, Y ≤ 50).
Вывод в файл OUTPUT.TXT. В единственной строке вывести количество способов достижения цели.
Пример
Ввод 1
3 3
Вывод 1
1
Ввод 2
3 5
Вывод 2
3

Игнатьев Влад, ПС-22
VSC 2022

*/

#include <iostream>
#include <map>
#include <cmath>    
#include <fstream>
#include <ctime>

using namespace std;

map<pair< long long,  long long>,  long long> memo;

 long long f( long long x,  long long y)
{
    if (x <= 0) {
        return 0;
    }   
    if (y < x) {
        return 0;
    }
    if (x == y) {
        return 1;
    }

    auto key = make_pair(x, y);
    if (memo.count(key)) {
        return memo[key];
    }

     long long result = f(x - 1, y - 1) + f(x + 1, y - 1);
    memo[key] = result;
    return result;
}

int main() 
{
    time_t start = clock();
    int x = 2, y = 40;
    //cin >> x >> y;
    cout << "Result by program: " << f(x, y) << "\n";
    cout << "Time: " << double(clock() - start) / CLOCKS_PER_SEC << " s.\n";
    return 0;
}
