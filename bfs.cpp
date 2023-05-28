#include <iostream>
#include <queue>
#include <omp.h>

using namespace std;

void bfs(int** graph, int numNodes, int start, bool* visited) {
    queue<int> q;
    q.push(start);
    visited[start] = true;
    cout << start << endl;

    #pragma omp parallel
    {
        #pragma omp single
        {
            while (!q.empty()) {
                int vertex = q.front();
                q.pop();
                #pragma omp task firstprivate(vertex)
                {
                    for (int neighbor = 0; neighbor < numNodes; neighbor++) {
                        if (graph[vertex][neighbor] && !visited[neighbor]) {
                            q.push(neighbor);
                            visited[neighbor] = true;
                            cout << neighbor << endl;
                            bfs(graph, numNodes, neighbor, visited);
                        }
                    }
                }
            }
        }
    }
}

void parallel_bfs(int** graph, int numNodes, int start) {
    bool* visited = new bool[numNodes];
    for (int i = 0; i < numNodes; i++) {
        visited[i] = false;
    }

    bfs(graph, numNodes, start, visited);

    delete[] visited;
}

int main() {
    // Create a sample graph
    int numNodes = 4;
    int** graph = new int*[numNodes];
    for (int i = 0; i < numNodes; i++) {
        graph[i] = new int[numNodes];
    }
	
	for (int i=0; i< numNodes; i++){
		for (int j=0; j < numNodes; j++){
			if(i == j || graph[j][i] == 1) 
				continue;
			cout<<"Vertex "<<i<<" and vertex "<<j<<" are conected ? (If yes enter 1 else 0)"<<endl;
			cin>>graph[i][j];
		}
	}
			

    int startNode = 0;  // Starting node for the depth-first search

    parallel_bfs(graph, numNodes,startNode);

    return 0;
}