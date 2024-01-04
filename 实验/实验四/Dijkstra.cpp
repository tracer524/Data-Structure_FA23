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
        int *distance;
        Status InitVisitedArray();
        Status InitAdjMatrix();
        Status InitGraph();
        int ShortestPath(int start, int end);
        Status InitDistance(int start);
        int NearestVertex();
        Status Relax(int vertex);
        bool AllVisited();
};

int main(){
    Graph G;
    G.InitGraph();
    int start, end;
    cin >> start >> end;
    cout << G.ShortestPath(start, end) << endl;
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

int Graph::ShortestPath(int start, int end){
    InitDistance(start);
    while(!AllVisited()){
        Relax(NearestVertex());
    }
    return distance[end];
}

Status Graph::InitDistance(int start){
    int i;
    distance = new int[VertexNum+1];
    for(i=1; i<=VertexNum; i++){
        distance[i] = AdjMatrix[start][i];
    }
    visited[start] = true;
    return OK;
}

int Graph::NearestVertex(){
    int min = INT_MAX;
    int min_num;
    int i;
    for(i=1; i<=VertexNum; i++){
        if((distance[i] < min) && (!visited[i])){
            min = distance[i];
            min_num = i;
        }
    }
    return min_num;
}

Status Graph::Relax(int vertex){
    int i;
    for(i=1; i<=VertexNum; i++){
        if((AdjMatrix[vertex][i] < INT_MAX) && (distance[vertex] + AdjMatrix[vertex][i] < distance[i])){
            distance[i] = distance[vertex] + AdjMatrix[vertex][i];
        }
    }
    visited[vertex] = true;
    return OK;
}

bool Graph::AllVisited(){
    int i;
    for(i=1; i<=VertexNum; i++){
        if(!visited[i]) return false;
    }
    return true;
}
