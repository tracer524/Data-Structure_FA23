#include "queue.h"

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