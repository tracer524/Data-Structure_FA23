#include "Queue.hpp"

Status InitQueue( LinkQueue &Q ){
    // 构造一个空队列 Q
    Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
    if(!Q.front) exit(OVERFLOW);
    Q.front->next = NULL;
    return OK;
}//InitQueue

Status DestroyQueue( LinkQueue &Q ){
    // 销毁队列 Q，Q不再存在
    ClearQueue(Q);
    free(Q.front);
    Q.front = NULL;
    Q.rear = NULL;
    return OK;
}//DestroyQueue

Status ClearQueue( LinkQueue &Q ){
    // 把 Q 置为空队列
    QueuePtr p = Q.front->next, q;
    while(p){
        q = p->next;
        free(p);
        p = q;
    }
    Q.rear = Q.front;
    Q.front->next = NULL;
    return OK;
}//ClearQueue

Status QueueEmpty( LinkQueue Q ){
    // 若队列 Q 为空队列，则返回 TRUE，否则返回 FALSE
    if(Q.front == Q.rear) return TRUE;
    else return FALSE;
}//QueueEmpty

int QueueLength( LinkQueue Q ){
    // 返回 S 的元素个数，即队列的长度
    int i = 0;
    QueuePtr p = Q.front->next;
    while(p){
        i++;
        p = p->next;
    }
    return i;
}//QueueLength

Status GetHead( LinkQueue Q, QElemType &e ){
    // 若队列不空，则用 e 返回 Q 的队头元素，并返回 OK；否则返回 ERROR
    if(Q.front == Q.rear) return ERROR;
    e = Q.front->next->data;
    return OK;
}//GetHead

Status EnQueue( LinkQueue &Q, QElemType e ){
    // 插入元素 e 为 Q 的新的队尾元素
    QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
    if(!p) exit(OVERFLOW);
    p->data = e;
    p->next = NULL;
    Q.rear->next = p;
    Q.rear = p;
    return OK;
}//EnQueue

Status DeQueue( LinkQueue &Q, QElemType &e ){
    // 若队列不空，则删除 Q 的队头元素，用 e 返回其值，并返回 OK；否则返回 ERROR
    if(Q.front == Q.rear) return ERROR;
    QueuePtr p = Q.front->next;
    e = p->data;
    Q.front->next = p->next;
    if(Q.rear == p) Q.rear = Q.front;
    free(p);
    return OK;
}//DeQueue

Status QueueTraverse( LinkQueue Q, Status (*visit)(QElemType &e) ){
    // 从队头到队尾依次对队列 Q 中每个元素调用函数 visit()。一旦 visit() 失败，则操作失败
    QueuePtr p = Q.front->next;
    while(p){
        if(!visit(p->data)) return ERROR;
        p = p->next;
    }
    return OK;
}//QueueTraverse

Status visit(QElemType &e){
    cout << e << " ";
    return OK;
}//visit