#include "Graph.hpp"
#include "Queue.hpp"
#include <iostream>

using namespace std;

Status Graph::InitAdjMatrix(){
    int i, j;
    AdjMatrix = new int*[VertexNum+1];
    for(i=0; i<=VertexNum; i++){
        AdjMatrix[i] = new int[VertexNum+1];
    }
    for(i=0; i<=VertexNum; i++){
        for(j=0; j<=VertexNum; j++){
            AdjMatrix[i][j] = 0;
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
    int vertex1, vertex2;
    cout << "Enter number of vertices and edges:" << endl;
    cin >> VertexNum >> EdgeNum;
    InitAdjMatrix();
    visited = new int[VertexNum+1];
    InitVisitedArray();
    for(i=0; i<EdgeNum; i++){
        cin >> vertex1 >> vertex2;
        AdjMatrix[vertex1][vertex2] = 1;
        AdjMatrix[vertex2][vertex1] = 1;
    }
    return OK;
}

Status Graph::DFS(int start, Stack &S){
    S.Push(start);
    cout << start << '\t';
    visited[start] = true;
    DFSCheck(start, S);
    return OK;
}

void Graph::DFSCheck(int obj, Stack &S){
    S.GetTop(obj);
    if(Search(obj)){
        DFS(Search(obj), S);
    }
    else{
        S.Pop(obj);
        if(S.StackEmpty())    return;
        DFSCheck(obj, S);
    }
}

Status Graph::BFS(int start, Queue &Q){
    Q.EnQueue(start);
    cout << start << '\t';
    visited[start] = true;
    BFSCheck(start, Q);
    return OK;
}

void Graph::BFSCheck(int obj, Queue &Q){
    Q.GetHead(obj);
    if(Search(obj)){
        BFS(Search(obj), Q);
    }
    else{
        Q.DeQueue(obj);
        if(Q.QueueEmpty())    return;
        BFSCheck(obj, Q);
    }
}


int Graph::Search(int vertex){
    int i;
    for(i=1; i<=VertexNum; i++){
        if((AdjMatrix[vertex][i] == 1) && (!visited[i]))   return i;
    }
    return 0;
}