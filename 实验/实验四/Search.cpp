# define TRUE       1
# define FALSE      0
# define OK         1
# define ERROR      0
# define INFEASIBLE -1
# define OVERFLOW   -2
# define STACK_INIT_SIZE 100
# define STACKINCREMENT  10

typedef int Status;

typedef int SElemType;

typedef int QElemType;

#include <iostream>

using namespace std;

class QNode
{
    public:
        QElemType data;
        QNode *next;
};

typedef QNode *QueuePtr;

class Queue
{
    public:
        QueuePtr front;
        QueuePtr rear;
        Status InitQueue();
            // 构造一个空队列 Q
        Status DestroyQueue();
            // 销毁队列 Q，Q不再存在
        Status ClearQueue();
            // 把 Q 置为空队列
        Status QueueEmpty();
            // 若队列 Q 为空队列，则返回 TRUE，否则返回 FALSE
        int QueueLength();
            // 返回 S 的元素个数，即队列的长度
        Status GetHead(QElemType &e);
            // 若队列不空，则用 e 返回 Q 的队头元素，并返回 OK；否则返回 ERROR
        Status EnQueue(QElemType e);
            // 插入元素 e 为 Q 的新的队尾元素
        Status DeQueue(QElemType &e);
            // 若队列不空，则删除 Q 的队头元素，用 e 返回其值，并返回 OK；否则返回 ERROR
        Status QueueTraverse(Status (*visit)(QElemType &e));
            // 从队头到队尾依次对队列 Q 中每个元素调用函数 visit()。一旦 visit() 失败，则操作失败
};

class Stack
{
    public:
        SElemType *base;
        SElemType *top;
        int stacksize;
        Status InitStack();
            // 构造一个空栈S
        Status DestroyStack();
            // 销毁栈S，S不再存在
        Status ClearStack();
            // 把S置为空栈
        Status StackEmpty();
            // 若栈S为空栈，则返回TRUE，否则返回FALSE
        int StackLength();
            // 返回S的元素个数，即栈的长度
        Status GetTop(SElemType &e);
            // 若栈不空，则用e返回S的栈顶元素，并返回OK；否则返回ERROR
        Status Push(SElemType e);
            // 插入元素e为新的栈顶元素
        Status Pop(SElemType &e);
            // 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR
        Status StackTraverse(Status (*visit)(SElemType &e));
            // 从栈底到栈顶依次对栈中每个元素调用函数visit()。一旦visit()失败，则操作失败
};

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

int main(){
    int start;
    Stack S;
    Queue Q;
    S.InitStack();
    Q.InitQueue();
    Graph G;
    G.InitGraph();
    cin >> start;
    G.DFS(start, S);
    G.InitVisitedArray();
    G.BFS(start, Q);
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

Status Stack::InitStack(){
    // 构造一个空栈S
    base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if(!base) exit(OVERFLOW);     // 存储分配失败
    top = base;
    stacksize = STACK_INIT_SIZE;
    return OK;
}

Status Stack::DestroyStack(){
    // 销毁栈S，S不再存在
    free(base);
    base = NULL;
    top = NULL;
    stacksize = 0;
    return OK;
}

Status Stack::ClearStack(){
    // 把S置为空栈
    top = base;
    return OK;
}

Status Stack::StackEmpty(){
    // 若栈S为空栈，则返回TRUE，否则返回FALSE
    if(top == base) return TRUE;
    else return FALSE;
}

int Stack::StackLength(){
    // 返回S的元素个数，即栈的长度
    return top - base;
}

Status Stack::GetTop(SElemType &e){
    // 若栈不空，则用e返回S的栈顶元素，并返回OK；否则返回ERROR
    if(top == base) return ERROR;
    e = *(top - 1);
    return OK;
}

Status Stack::Push(SElemType e){
    // 插入元素e为新的栈顶元素
    if(top - base >= stacksize){  // 栈满，追加存储空间
        base = (SElemType *)realloc(base, (stacksize + STACKINCREMENT) * sizeof(SElemType));
        if(!base) exit(OVERFLOW);     // 存储分配失败
        top = base + stacksize;
        stacksize += STACKINCREMENT;
    }
    *top++ = e;
    return OK;
}

Status Stack::Pop(SElemType &e){
    // 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR
    if(top == base) return ERROR;
    e = *top;
    top--;
    return OK;
}

Status Stack::StackTraverse(Status (*visit)(SElemType &e)){
    // 从栈底到栈顶依次对栈中每个元素调用函数visit()。一旦visit()失败，则操作失败
    while(top > base){
        visit(*base++);
    }
    return OK;
}

Status Queue::InitQueue(){
    // 构造一个空队列 Q
    front = rear = (QueuePtr)malloc(sizeof(QNode));
    if(!front) exit(OVERFLOW);
    front->next = NULL;
    return OK;
}//InitQueue

Status Queue::DestroyQueue(){
    // 销毁队列 Q，Q不再存在
    ClearQueue();
    free(front);
    front = NULL;
    rear = NULL;
    return OK;
}//DestroyQueue

Status Queue::ClearQueue(){
    // 把 Q 置为空队列
    QueuePtr p = front->next, q;
    while(p){
        q = p->next;
        free(p);
        p = q;
    }
    rear = front;
    front->next = NULL;
    return OK;
}//ClearQueue

Status Queue::QueueEmpty(){
    // 若队列 Q 为空队列，则返回 TRUE，否则返回 FALSE
    if(front == rear) return TRUE;
    else return FALSE;
}//QueueEmpty

int Queue::QueueLength(){
    // 返回 S 的元素个数，即队列的长度
    int i = 0;
    QueuePtr p = front->next;
    while(p){
        i++;
        p = p->next;
    }
    return i;
}//QueueLength

Status Queue::GetHead(QElemType &e){
    // 若队列不空，则用 e 返回 Q 的队头元素，并返回 OK；否则返回 ERROR
    if(front == rear) return ERROR;
    e = front->next->data;
    return OK;
}//GetHead

Status Queue::EnQueue(QElemType e){
    // 插入元素 e 为 Q 的新的队尾元素
    QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
    if(!p) exit(OVERFLOW);
    p->data = e;
    p->next = NULL;
    rear->next = p;
    rear = p;
    return OK;
}//EnQueue

Status Queue::DeQueue(QElemType &e){
    // 若队列不空，则删除 Q 的队头元素，用 e 返回其值，并返回 OK；否则返回 ERROR
    if(front == rear) return ERROR;
    QueuePtr p = front->next;
    e = p->data;
    front->next = p->next;
    if(rear == p) rear = front;
    free(p);
    return OK;
}//DeQueue

Status Queue::QueueTraverse(Status (*visit)(QElemType &e)){
    // 从队头到队尾依次对队列 Q 中每个元素调用函数 visit()。一旦 visit() 失败，则操作失败
    QueuePtr p = front->next;
    while(p){
        if(!visit(p->data)) return ERROR;
        p = p->next;
    }
    return OK;
}//QueueTraverse