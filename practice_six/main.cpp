#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//две вершины и вес ребра
struct Edge {
    int v1, v2, weight;
};

// сравнение ребер по весу
bool compare_edges(const Edge &a, const Edge &b) {
    return a.weight < b.weight;
}

//нахождение корня множества, к которому принадлежит элемент i
// рекурсивно обходит дерево представления множества,
// пока не достигнет корня, и возвращает его
int find(vector<int> &parent, int i) {
    if (parent[i] == i)
        return i;
    return find(parent, parent[i]);
}

// объединяет два множества, содержащих элементы x и y

void union_sets(vector<int> &parent, int x, int y) {
    // сначала находит корни этих множеств с помощью функции find
    int xset = find(parent, x);
    int yset = find(parent, y);
    // делает один из корней родителем другого
    parent[yset] = xset;
}

void kruskalMST(vector<Edge> &edges, int V) {
    //сортируем по весу
    sort(edges.begin(), edges.end(), compare_edges);

    // родитель каждой вершины
    vector<int> parent(V);
    for (int i = 0; i < V; ++i)
        parent[i] = i;

    //ребра минимального остовного дерева
    vector<Edge> mst;
    int mstWeight = 0;

    // проходим по каждому ребру из отстортированного вектора
    for (const auto &edge : edges) {
        // Находим корни множеств, к которым принадлежат вершины edge.v1 и edge.v2
        int x = find(parent, edge.v1);
        int y = find(parent, edge.v2);

        // Если корни этих множеств различны, то добавляем ребро edge в mst,
        // увеличиваем mstWeight на вес ребра edge и объединяем множества вершин edge.v1 и edge.v2
        if (x != y) {
            mst.push_back(edge);
            mstWeight += edge.weight;
            union_sets(parent, x, y);
        }
    }

    // вес дерева
    cout << "Weight of MST: " << mstWeight << endl;
    cout << "Edges in MST:" << endl;
    // все ребра дерева
    for (const auto &edge : mst) {
        cout << "edge " << edge.v1 << "---" << edge.v2 << " with weight  " << edge.weight << endl;
    }
}

int main() {
    const int V = 5;
    vector<Edge> edges;
    edges.push_back({1, 2, 1});
    edges.push_back({1, 3, 2});
    edges.push_back({1, 5, 10});
    edges.push_back({2, 5, 6});
    edges.push_back({3, 5, 7});
    edges.push_back({2, 4, 3});
    edges.push_back({3, 4, 4});
    edges.push_back({4, 5, 11});

    kruskalMST(edges, V);

    return 0;
}