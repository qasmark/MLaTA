/*
12.3. Максимальный путь 1 (6)
Имеется взвешенный ориентированный ациклический граф. Найти максимальный путь, используя алгоритм Беллмана-Форда.
Ввод из файла INPUT.TXT. Первая строка входного файла INPUT.TXT содержит 3 числа: N - количество вершин графа (3 ≤ N ≤ 1000), 
M – дуг (3 ≤ M ≤ 500000), A – номер начальной вершины. В следующих M строках по 3 числа, задающих дуги: 
начало дуги, конец дуги, длина (вес).
Вывод в файл OUTPUT.TXT. В i-й строке выводится длина максимального пути из вершины S до i-й вершины, 
затем количество вершин максимального пути, а далее номера вершин максимального пути. 
Все числа разделены пробелами. Если пути в некоторую вершину не существует, то в соответствующей строке выводится слово No. 
Если в графе имеется достижимый из начальной вершины цикл положительной длины, то вывод состоит из двух строк. 
В первой строке выводится слово No, а во второй – количество и номера вершин обнаруженного цикла через пробел, начиная с его 
любой вершины и заканчивая ей же. При наличии нескольких циклов вывести информацию о любом из них.
Пример
Ввод 1    
4 6 1    
1 2 1     
1 4 2     
2 3 3      
2 4 3     
3 4 1       
4 3 1    
Вывод 1  
No        
3 4 3 4 
Ввод 2
5 6 1
1 2 1
1 4 2
2 3 3
2 4 3
3 4 1
5 2 5
Вывод 2

0 1 1
1 2 1 1
4 3 1 2 3
5 4 1 2 3 4
No

*/
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>

const int INF = std::numeric_limits<int>::max();

class Edge {
public:
    int from, to, weight;

    Edge(int _from, int _to, int _weight) : from(_from), to(_to), weight(_weight) {}
};

class Graph {
public:
    int size;

    Graph(int _size) : size(_size) {}

    virtual ~Graph() {}

    virtual void add_edge(int from, int to, int weight) = 0;

    virtual std::vector<int> shortest_path(int source) = 0;

    virtual std::vector<int> longest_path(int source) = 0;
};

class AdjacencyListGraph : public Graph {
public:
    std::vector<std::vector<Edge>> adj;

    AdjacencyListGraph(int _size) : Graph(_size), adj(_size) {}

    void add_edge(int from, int to, int weight) override {
        adj[from].emplace_back(from, to, weight);
    }

    std::vector<int> shortest_path(int source) override {
        std::vector<int> dist(size, INF);
        std::queue<int> q;
        std::vector<bool> in_queue(size, false);

        dist[source] = 0;
        q.push(source);
        in_queue[source] = true;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            in_queue[u] = false;

            for (const auto& edge : adj[u]) {
                int v = edge.to;
                int weight = edge.weight;

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;

                    if (!in_queue[v]) {
                        q.push(v);
                        in_queue[v] = true;
                    }
                }
            }
        }

        return dist;
    }

    std::vector<int> longest_path(int source) override {
        std::vector<int> dist(size, -INF);
        std::vector<int> pred(size, -1);
        std::vector<int> topo_order;
        std::vector<bool> visited(size, false);
        bool has_cycle = false;

        dfs(source, visited, pred, has_cycle, topo_order);

        if (has_cycle) {
            for (int i = 0; i < size; i++) {
                if (visited[i]) {
                    std::vector<int> cycle;
                    for (int j = i; j != i || cycle.empty(); j = pred[j]) {
                        cycle.push_back(j);
                    }

                    std::reverse(cycle.begin(), cycle.end());

                    std::ofstream output_file("OUTPUT.TXT");

                    output_file << "No\n";
                    output_file << cycle.size() << ' ';
                    for (int u : cycle) {
                        output_file << u + 1 << ' ';
                    }
                    output_file << cycle.front() + 1 << '\n';

                    return {};
                }
            }
        }

        dist[source] = 0;

        for (int u : topo_order) {
            if (dist[u] == -INF) {
                continue;
            }

            for (const auto& edge : adj[u]) {
                int v = edge.to;
                int weight = edge.weight;

                if (dist[u] + weight > dist[v]) {
                    dist[v] = dist[u] + weight;
                    pred[v] = u;
                }
            }
        }

        std::vector<std::pair<int, int>> path_sizes(size);
        for (int i = 0; i < size; i++) {
            if (dist[i] > -INF) {
                path_sizes[i] = std::make_pair(dist[i], get_path_size(pred, i));
            }
        }

        return get_max_path(path_sizes);
    }

private:
    void dfs(int u, std::vector<bool>& visited, std::vector<int>& pred, bool& has_cycle,
        std::vector<int>& topo_order) {
        visited[u] = true;

        for (const auto& edge : adj[u]) {
            int v = edge.to;

            if (!visited[v]) {
                pred[v] = u;
                dfs(v, visited, pred, has_cycle, topo_order);
            }
            else if (visited[v] && pred[u] != v) {
                has_cycle = true;
            }
        }

        topo_order.push_back(u);
    }

    int get_path_size(const std::vector<int>& pred, int u) {
        if (pred[u] == -1) {
            return 1;
        }

        return 1 + get_path_size(pred, pred[u]);
    }

    std::vector<int> get_max_path(const std::vector<std::pair<int, int>>& path_sizes) {
        std::vector<int> max_path;

        for (int i = 0; i < size; i++) {
            if (path_sizes[i].first == -INF) {
                std::ofstream output_file("OUTPUT.TXT");
                output_file << "No\n";
                return {};
            }
        }

        int max_path_size = 0;
        for (const auto& path : path_sizes) {
            if (path.second > max_path_size) {
                max_path_size = path.second;
            }
        }

        for (const auto& path : path_sizes) {
            if (path.second == max_path_size) {
                max_path.push_back(path.first);
            }
        }

        std::ofstream output_file("OUTPUT.TXT");

        for (int u : max_path) {
            output_file << path_sizes[u].first << ' ';
            output_file << path_sizes[u].second << ' ';
            int v = u;
            while (v != -1) {
                output_file << v + 1 << ' ';
                v = pred[v];
            }
            output_file << '\n';
        }

        return max_path;
    }
};

int main() {
    std::ifstream input_file("INPUT.TXT");

    int n, m, s;
    input_file >> n >> m >> s;
    s--;

    AdjacencyListGraph graph(n);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        input_file >> u >> v >> w;
        u--;
        v--;

        graph.add_edge(u, v, w);
    }

    graph.longest_path(s);

    return 0;
}