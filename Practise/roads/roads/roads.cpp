#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

int main() {
    int n, m;
    fstream fin;
    fin.open("input10.txt");
    fin >> n >> m;

    vector<pair<int, int>> segments(n);
    for (int i = 0; i < n; i++) {
        fin >> segments[i].first >> segments[i].second;
    }

    sort(segments.begin(), segments.end());

    int i = 0, count = 0;
    while (i < n) {
        int j = i + 1;
        while (j < n && segments[j].first <= segments[i].second) {
            j++;
        }
        if (j - i >= m) {
            count++;
            i = j - 1;
        }
        i++;
    }

    cout << count << endl;

    return 0;
}