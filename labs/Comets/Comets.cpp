#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

int main() {
    int n, t;
    cin >> n >> t;
    vector<pair<double, double>> comets(n);
    for (int i = 0; i < n; i++) {
        cin >> comets[i].first >> comets[i].second;
    }
    double max_brightness = 0;
    for (int i = 0; i <= t; i++) {
        double brightness = 0;
        for (int j = 0; j < n; j++) {
            brightness = max(brightness, comets[j].first * i + comets[j].second);
        }
        max_brightness = max(max_brightness, brightness);
    }
    cout << fixed << setprecision(10) << max_brightness << endl;
    return 0;
}