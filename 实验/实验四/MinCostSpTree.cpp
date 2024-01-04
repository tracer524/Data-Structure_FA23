// 此程序分别用DFS和BFS遍历图
# define TRUE       1
# define FALSE      0
# define OK         1
# define ERROR      0
# define INFEASIBLE -1
# define OVERFLOW   -2

typedef int Status;

#include <iostream>
#include <limits.h>

using namespace std;

class Graph
{
    public:
        int VertexNum;
        int EdgeNum;
        int **AdjMatrix;
        int *visited;
        int **ConnecMatrix;
        Status InitVisitedArray();
        Status InitAdjMatrix();
        Status InitGraph();
        int Prim();
        int FindMinimum();
        int Kruskal();
        void FindLowestCost(int &vertex1, int &vertex2);
        void Connect(int vertex1, int vertex2);
        bool AllConnected();
        bool AllVisited();
        int Search(int vertex);
};

int main(){
    Graph G;
    G.InitGraph();
    cout << "Kruskal:" << G.Kruskal() <<endl;
    cout << "Prim:" << G.Prim() << endl;
    return 0;
}

Status Graph::InitAdjMatrix(){
    int i, j;
    AdjMatrix = new int*[VertexNum+1];
    for(i=0; i<=VertexNum; i++){
        AdjMatrix[i] = new int[VertexNum+1];
    }
    for(i=0; i<=VertexNum; i++){
        for(j=0; j<=VertexNum; j++){
            AdjMatrix[i][j] = INT_MAX;
        }
    }
    return OK;
}

Status Graph::InitVisitedArray(){
    int i;
    for(i=0; i<=VertexNum; i++){
        visited[i] = 0;
    }
    return OK;
}

Status Graph::InitGraph(){
    int i, j;
    int vertex1, vertex2, weight;
    cout << "Enter number of vertices and edges:" << endl;
    cin >> VertexNum >> EdgeNum;
    InitAdjMatrix();
    visited = new int[VertexNum+1];
    InitVisitedArray();
    for(i=0; i<EdgeNum; i++){
        cin >> vertex1 >> vertex2 >> weight;
        AdjMatrix[vertex1][vertex2] = weight;
        AdjMatrix[vertex2][vertex1] = weight;
    }
    return OK;
}

int Graph::Prim(){
    int weight_sum_P =0;
    visited[1] = 1;
    while(!AllVisited()){
        weight_sum_P += FindMinimum();
    }
    return weight_sum_P;
}

int Graph::FindMinimum(){
    int min = INT_MAX;
    int min_num = 0;
    int i, j;
    for(i=1; i<=VertexNum; i++){
        if(!visited[i]) continue;
        for(j=1; j<=VertexNum; j++){
            if(visited[j]) continue;
            if(AdjMatrix[i][j] < min){
                min = AdjMatrix[i][j];
                min_num = j;
            }
        }
    }
    visited[min_num] = 1;
    return min;
}

int Graph::Kruskal(){
    int i, j, vertex1, vertex2;
    int weight_sum_K = 0;
    ConnecMatrix = new int*[VertexNum+1];
    for(i=0; i<=VertexNum; i++){
        ConnecMatrix[i] = new int[VertexNum+1];
    }
    for(i=0; i<=VertexNum; i++){
        for(j=0; j<=VertexNum; j++){
            ConnecMatrix[i][j] = 0;
        }
    }
    for(i=1; i<=VertexNum; i++){
        ConnecMatrix[i][i] = 1;
    }
    while(!AllConnected()){
        FindLowestCost(vertex1, vertex2);
        weight_sum_K += AdjMatrix[vertex1][vertex2];
        Connect(vertex1, vertex2);
    }
    return weight_sum_K;
}

void Graph::FindLowestCost(int &vertex1, int &vertex2){
    int i, j;
    int min = INT_MAX;
    for(i=1; i<=VertexNum; i++){
        for(j=1; j<i; j++){
            if(!ConnecMatrix[i][j] && (AdjMatrix[i][j]<min)){
                vertex1 = i;    vertex2 = j;    min = AdjMatrix[i][j];
            }
        }
    }
}

void Graph::Connect(int vertex1, int vertex2){
    int i, j;
    for(i=1; i<=VertexNum; i++){
        if(ConnecMatrix[i][vertex1]){
            for(j=1; j<=VertexNum; j++){
                if(ConnecMatrix[j][vertex2]){
                    ConnecMatrix[i][j] = 1;
                    ConnecMatrix[j][i] = 1;
                }
            }
        }
    }
    ConnecMatrix[vertex1][vertex2] = 1;
    ConnecMatrix[vertex2][vertex1] = 1;
}

bool Graph::AllConnected(){
    int i;
    for(i=1; i<=VertexNum; i++){
        if(!ConnecMatrix[1][i]) return false;
    }
    return true;
}

bool Graph::AllVisited(){
    int i;
    for(i=1; i<=VertexNum; i++){
        if(!visited[i]) return false;
    }
    return true;
}

int Graph::Search(int vertex){
    int i;
    for(i=1; i<=VertexNum; i++){
        if((AdjMatrix[vertex][i] == 1) && (!visited[i]))   return i;
    }
    return 0;
}
