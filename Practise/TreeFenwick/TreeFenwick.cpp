#include <iostream>
#include <vector>

using namespace std;

int rsq(vector<int>& fenwick_tree, int index) {
    int sum = 0;
    while (index > 0) {
        sum += fenwick_tree[index];
        index -= index & (-index);
    }
    return sum;
}

void update(vector<int>& fenwick_tree, int index, int value) {
    while (index < fenwick_tree.size()) {
        fenwick_tree[index] += value;
        index += index & (-index);
    }
}

int main() {
    int n;
    cin >> n;

    vector<int> arr(n);
    vector<int> fenwick_tree(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        update(fenwick_tree, i + 1, arr[i]);
    }

    string cmd;
    while (cmd != "exit") {
        cin >> cmd;

        if (cmd == "out") {
            for (int i = 0; i < n; i++) {
                cout << arr[i] << " ";
            }
            cout << endl;
        }
        else if (cmd == "rsq") {
            int i, j;
            cin >> i >> j;
            cout << rsq(fenwick_tree, j + 1) - rsq(fenwick_tree, i) << endl;
        }
        else if (cmd == "add") {
            int i, v;
            cin >> i >> v;
            arr[i] += v;
            update(fenwick_tree, i + 1, v);
        }
        else if (cmd == "update") {
            int i, v;
            cin >> i >> v;
            int diff = v - arr[i];
            arr[i] = v;
            update(fenwick_tree, i + 1, diff);
        }
    }

    return 0;
}