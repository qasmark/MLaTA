#include <iostream>
#include <string>
#include <stack>
#include <cmath>
#include <iomanip>
using namespace std;

struct Node {
    char op;
    double num;
    Node* left;
    Node* right;
    Node(char c) :op(c), num(0), left(NULL), right(NULL) {}
    Node(double n) :op('\0'), num(n), left(NULL), right(NULL) {}
};

int priority(char op) {
    if (op == '(') return 0;
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return -1;
}

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

double calculate(double a, double b, char op) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return a / b;
    case '^': return pow(a, b);
    default: return 0;
    }
}

Node* buildTree(string s) {
    stack<Node*> nodes;
    stack<char> ops;

    for (int i = 0; i < s.size(); i++) {
        if (isDigit(s[i])) {
            double num = s[i] - '0';
            int j = i + 1;
            while (j < s.size() && isDigit(s[j])) {
                num = num * 10 + (s[j] - '0');
                j++;
            }
            i = j - 1;
            nodes.push(new Node(num));
        }
        else if (s[i] == '(') {
            ops.push(s[i]);
        }
        else if (s[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                char op = ops.top();
                ops.pop();
                Node* right = nodes.top();
                nodes.pop();
                Node* left = nodes.top();
                nodes.pop();
                Node* node = new Node(op);
                node->left = left;
                node->right = right;
                nodes.push(node);
            }
            ops.pop();
        }
        else {
            if (s[i] == '-' && (i == 0 || !isDigit(s[i - 1]) && s[i - 1] != ')')) { //unary minus
                double num = s[i + 1] - '0';
                int j = i + 2;
                while (j < s.size() && isDigit(s[j])) {
                    num = num * 10 + (s[j] - '0');
                    j++;
                }
                i = j - 1;
                nodes.push(new Node(-num));
            }
            else {
                while (!ops.empty() && priority(ops.top()) > priority(s[i])) { //право ассоциативность возведения в степень
                    char op = ops.top();
                    ops.pop();
                    Node* right = nodes.top();
                    nodes.pop();
                    Node* left = nodes.top();
                    nodes.pop();
                    Node* node = new Node(op);
                    node->left = left;
                    node->right = right;
                    nodes.push(node);
                }
                ops.push(s[i]);
            }
        }
    }

    while (!ops.empty()) {
        char op = ops.top();
        ops.pop();
        Node* right = nodes.top();
        nodes.pop();
        Node* left = nodes.top();
        nodes.pop();
        Node* node = new Node(op);
        node->left = left;
        node->right = right;
        nodes.push(node);
    }

    return nodes.top();
}

double evaluate(Node* root) {
    if (root->left == NULL && root->right == NULL) {
        return root->num;
    }
    double leftVal = evaluate(root->left);
    double rightVal = evaluate(root->right);
    return calculate(leftVal, rightVal, root->op);
}

int main() {
    string s;
    cin >> s;
    Node* root = buildTree(s);
    double result = evaluate(root);
    cout << fixed << setprecision(4) << result << endl;
    return 0;
}