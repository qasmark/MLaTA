#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class SegmentTree {
public:
    explicit SegmentTree(vector<T>& elements)
        : tree_(4 * elements.size()), elements_(elements) {
        BuildTree(1, 0, elements_.size() - 1);
    }

    T Rmq(int l, int r) const {
        return RmqImpl(1, 0, elements_.size() - 1, l, r);
    }

    void Add1(int i, T d) {
        int pos = i + elements_.size() - 1;
        tree_[pos] += d;

        while (pos != 1) {
            pos /= 2;
            tree_[pos] = max(tree_[2 * pos], tree_[2 * pos + 1]);
        }
    }


    void Add2(int i, int j, T d) {
        Add2Impl(1, 0, elements_.size() - 1, i, j, d);
    }

    void out()
    {
        for (int i = 0; i < tree_.size(); i++)
        {
            cout << tree_[i] << " ";
        }
        cout << endl;
    }

private:
    vector<T> tree_;
    vector<T>& elements_;

    void BuildTree(int node, int lo, int hi) {
        if (lo == hi) {
            tree_[node] = elements_[lo];
            return;
        }

        int mid = (lo + hi) / 2;
        BuildTree(node * 2, lo, mid);
        BuildTree(node * 2 + 1, mid + 1, hi);
        tree_[node] = max(tree_[node * 2], tree_[node * 2 + 1]);
    }

    T RmqImpl(int node, int lo, int hi, int i, int j) const {
        if (lo > j || hi < i) {
            return -1e9; 
        }

        if (lo >= i && hi <= j) {
            return tree_[node];
        }

        int mid = (lo + hi) / 2;
        T left = RmqImpl(node * 2, lo, mid, i, j);
        T right = RmqImpl(node * 2 + 1, mid + 1, hi, i, j);
        return max(left, right);
    }

    void UpdateTree(int node, int lo, int hi, int i) 
    {
        if (lo > i || hi < i) {
            return;
        }

        if (lo == hi) {
            tree_[node] = elements_[i];
            return;
        }

        int mid = (lo + hi) / 2;
        UpdateTree(node * 2, lo, mid, i);
        UpdateTree(node * 2 + 1, mid + 1, hi, i);
        tree_[node] = max(tree_[node * 2], tree_[node * 2 + 1]);
    }

    void Add2Impl(int node, int lo, int hi, int i, int j, T d) {
        if (lo > j || hi < i) {
            return;
        }

        if (lo >= i && hi <= j) {
            tree_[node] += d;
            return;
        }

        int mid = (lo + hi) / 2;
        Add2Impl(node * 2, lo, mid, i, j, d);
        Add2Impl(node * 2 + 1, mid + 1, hi, i, j, d);
        tree_[node] = max(tree_[node * 2], tree_[node * 2 + 1]);
    }
};

int main() {
    vector<int> elements;
    int n, q;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        elements.push_back(x);
    }
    SegmentTree<int> tree(elements);

    string query = "";
    while (query != "exit") 
    {
        cin >> query;
        if (query == "rmq") 
        {
            int l, r;
            cin >> l >> r;
            cout << tree.Rmq(l, r) << "\n";
        }
        else if (query == "add1") 
        {
            int i, d;
            cin >> i >> d;
           // tree.Add1(i - 1, d);
           tree.Add2(i - 1, i, d);
        }
        else if (query == "add2") 
        {
            int i, j, d;
            cin >> i >> j >> d;
            tree.Add2(i, j, d);
        }
        else if (query == "out")
        {
            tree.out();
        }
    }

    return 0;
}