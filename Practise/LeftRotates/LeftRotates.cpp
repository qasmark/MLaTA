#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> points(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i].first >> points[i].second;
    }
    int left_turns = 0, perpendicular_turns = 0;
    for (int i = 0; i < n - 2; i++) {
        int x1 = points[i].first, y1 = points[i].second;
        int x2 = points[i + 1].first, y2 = points[i + 1].second;
        int x3 = points[i + 2].first, y3 = points[i + 2].second;
        int cross_product = (x2 - x1) * (y3 - y2) - (x3 - x2) * (y2 - y1);

        if (cross_product > 0) {
            left_turns++;
        }
        int dot_product = (x2 - x1) * (x3 - x2) + (y2 - y1) * (y3 - y2);
        if (dot_product == 0) {
            perpendicular_turns++;
        }
    }
    cout << left_turns << " " << perpendicular_turns << endl;
    return 0;
}