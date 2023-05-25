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
#include <limits>

const int INF = std::numeric_limits<int>::min(); // Используем негативную бесконечность

struct Edge {
    int source;
    int destination;
    int weight;
};

void bellmanFord(int N, int M, int A, const std::vector<Edge>& edges) {
    std::vector<int> distance(N, INF);
    std::vector<int> parent(N, -1);
    distance[A - 1] = 0;

    // Relax edges N-1 times
    for (int i = 1; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            int u = edges[j].source - 1;
            int v = edges[j].destination - 1;
            int weight = edges[j].weight;
            if (distance[u] != INF && distance[u] + weight > distance[v]) {
                distance[v] = distance[u] + weight;
                parent[v] = u;
            }
        }
    }

    // Check for negative cycles
    for (int j = 0; j < M; ++j) {
        int u = edges[j].source - 1;
        int v = edges[j].destination - 1;
        int weight = edges[j].weight;
        if (distance[u] != INF && distance[u] + weight > distance[v]) {
            std::vector<int> cycle;
            int current = v;
            while (current != u) {
                cycle.push_back(current + 1);
                current = parent[current];
            }
            cycle.push_back(u + 1);

            std::ofstream output("OUTPUT.TXT");
            output << "No" << std::endl;
            output << cycle.size() << " ";
            for (int i = cycle.size() - 1; i >= 0; --i) {
                output << cycle[i] << " ";
            }
            output.close();
            return;
        }
    }

    // Output longest paths
    std::ofstream output("OUTPUT.TXT");
    for (int i = 0; i < N; ++i) {
        if (distance[i] == INF) {
            output << "No" << std::endl;
        }
        else {
            std::vector<int> path;
            int current = i;
            while (current != -1) {
                path.push_back(current + 1);
                current = parent[current];
            }

            output << distance[i] << " ";
            output << path.size() << " ";
            for (int j = path.size() - 1; j >= 0; --j) {
                output << path[j] << " ";
            }
            output << std::endl;
        }
    }
    output.close();
}

int main() {
    std::ifstream input("INPUT.TXT");
    int N, M, A;
    input >> N >> M >> A;

    std::vector<Edge> edges(M);
    for (int i = 0; i < M; ++i) {
        input >> edges[i].source >> edges[i].destination >> edges[i].weight;
    }
    input.close();

    bellmanFord(N, M, A, edges);

    return 0;
}
