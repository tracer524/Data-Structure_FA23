#include "define.hpp"

class Graph
{
    public:
        int VertexNum;
        int EdgeNum;
        int **AdjMatrix;    // adjacency matrix
        int *visited;   // used for mark visited vertices
        Status InitVisitedArray();
        Status InitAdjMatrix();
        Status InitGraph();
        Status DFS(int start, Stack &S);    // recursively travers the graph using a stack
        void DFSCheck(int obj, Stack &S);
        void BFSCheck(int obj, Queue &Q);
        Status BFS(int start, Queue &Q);    // recursively travers the graph using a queue
        bool NoAdjVex(int vertex);
        int Search(int vertex);
};