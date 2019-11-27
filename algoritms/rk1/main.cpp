#include <iostream>

using namespace std;

#include <vector>
#include<stack>
#include<ctime>

struct IGraph {
    virtual ~IGraph() = 0;

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const  = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

IGraph::~IGraph() {}

class CMatrixGraph: public IGraph
{
public:
    CMatrixGraph(int n) :
        viseted(n, false),
        matrix(n)
    {
        for (size_t i = 0; i < matrix.size(); i++)
        {
            matrix[i].resize(n);
            for (int j = 0; j < matrix.size(); j++)
            {
                matrix[i][j] = false;
            }
        }
    }
    CMatrixGraph(const IGraph &graph)
    {
        matrix.resize(graph.VerticesCount());
        for (size_t i = 0; i < matrix.size(); i++)
        {
            matrix[i].resize(graph.VerticesCount());
            std::vector<int> next = graph.GetNextVertices(i);
            for (size_t j = 0; j < next.size(); j++)
            {
                matrix[i][next[j]] = true;
            }
        }
    }
    ~CMatrixGraph() {}

    // Добавление ребра от from к to.
    void AddEdge(int from, int to) override
    {
        matrix[from][to] = true;
    }

    int VerticesCount() const  override
    {
        return (int)matrix.size();
    }

    std::vector<int> GetNextVertices(int vertex) const override
    {
        std::vector<int> next;
        for (size_t i = 0; i < matrix.size(); i++)
        {
            if (matrix[vertex][i])
                next.push_back(i);
        }
        return next;

    }
    std::vector<int> GetPrevVertices(int vertex) const override
    {
        std::vector<int> prev;
        for (size_t i = 0; i < matrix.size(); i++)
        {
            if (matrix[i][vertex])
                prev.push_back(i);
        }
        return prev;
    }


    void DFS(int vertex,  void (*func)(int)) {
        for (int i = 0; i < viseted.size(); i++)
        {
            viseted[i] = false;
        }

        this->_dfs(vertex, func);

    }

    void DFS2(int vertex, void (*func)(int))
    {
        for (int i = 0; i < viseted.size(); i++)
        {
            viseted[i] = false;
        }
        std::stack<int> next_vertices;

        next_vertices.push(vertex);
        viseted[vertex] = true;

        while (next_vertices.size())
        {
            int current = next_vertices.top();
            next_vertices.pop();

            func(current);

            for (int next_vertex: this->GetNextVertices(current))
            {
                if (!viseted[next_vertex])
                {
                    viseted[next_vertex] = true;
                    next_vertices.push(next_vertex);
                }
            }
        }
    }


private:
    void _dfs(int vertex,  void (*func)(int)) {
        if (viseted[vertex]) return;
        viseted[vertex] = true;

        func(vertex);
        for (int next_vertex: this->GetNextVertices(vertex))
        {
            if (!viseted[next_vertex])
            {
                _dfs(next_vertex, func);
            }
        }
    }
    std::vector<bool> viseted;
    std::vector<std::vector<bool>> matrix;


};

void DFS(const IGraph &graph, int vertex, void (*func)(int))
{
    std::vector<bool> visited(graph.VerticesCount(), false);
    std::stack<int> next_vertices;

    next_vertices.push(vertex);
    visited[vertex] = true;

    while (next_vertices.size())
    {
        int current = next_vertices.top();
        next_vertices.pop();

        func(current);

        for (int next_vertex: graph.GetNextVertices(current))
        {
            if (!visited[next_vertex])
            {
                visited[next_vertex] = true;
                next_vertices.push(next_vertex);
            }
        }
    }
}

#include <random>

void time() {

    FILE *f = fopen("time.txt", "w");
    fprintf(f,"%5s,%15s,%15s,%15s\n", "N" , "unrec", "rec", "1");
    printf("%5s,%15s,%15s,%15s\n", "N" , "unrec", "rec", "1");
    std::clock_t time = 0;
    int count = 5;
    for (int i = 100; i <= 3000; i+= 100) {
        fprintf(f, "%5d,", i);
        printf("%5d,", i);
        CMatrixGraph graph(i);
        for (int j = 0; j < (i-1)*i; j++) {
            graph.AddEdge(std::rand()%i, std::rand()%i);
        }
        time = 0;
        for (int j = 0; j < count; j++) {
             std::clock_t start = std::clock();
             DFS(graph, 0, [](int vertex){ int i = vertex + 5; });
             //graph.DFS2(0, [](int vertex){ int i = vertex + 5; });
             std::clock_t end = std::clock();
             time += end-start;
        }
        printf("%15d,", time/count);
        fprintf(f,"%15d,", time/count);
        time = 0;
        for (int j = 0; j < count; j++) {
             std::clock_t start = std::clock();
             graph.DFS(0, [](int vertex){ int i = vertex + 5; });
             std::clock_t end = std::clock();
             time += end-start;
        }
        printf("%15d\n", time/count);
        fprintf(f,"%15d\n", time/count);
    }
}

int main()
{
    time();
    CMatrixGraph graph(7);
    graph.AddEdge(0, 1);
    graph.AddEdge(0, 4);
    graph.AddEdge(0, 5);
    //graph.AddEdge(1, 2);
    graph.AddEdge(1, 3);
    //graph.AddEdge(1, 5);
    //graph.AddEdge(1, 6);
    graph.AddEdge(3, 2);
    //graph.AddEdge(3, 4);
    //graph.AddEdge(3, 6);
   // graph.AddEdge(5, 4);
    graph.AddEdge(5, 6);
    graph.AddEdge(6, 4);

    DFS(graph, 0, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl;
    graph.DFS(0, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl;

    cout << "Hello World!" << endl;
    return 0;
}
