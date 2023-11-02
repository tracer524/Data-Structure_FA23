//队列的基本操作函数声明

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>
using namespace std;

#define TRUE       1
#define FALSE      0
#define OK         1
#define ERROR      0
#define INFEASIBLE -1
#define OVERFLOW   -2
#define N          10

typedef int Status;

typedef struct QNode{
    QElemType       data;
    struct QNode    *next;
}QNode, *QueuePtr;

typedef struct{
    QueuePtr    front;      // 队头指针
    QueuePtr    rear;       // 队尾指针
}LinkQueue;

//-----队列操作-----
Status InitQueue( LinkQueue &Q );
    // 构造一个空队列 Q
Status DestroyQueue( LinkQueue &Q );
    // 销毁队列 Q，Q不再存在
Status ClearQueue( LinkQueue &Q );
    // 把 Q 置为空队列
Status QueueEmpty( LinkQueue Q );
    // 若队列 Q 为空队列，则返回 TRUE，否则返回 FALSE
int QueueLength( LinkQueue Q );
    // 返回 S 的元素个数，即队列的长度
Status GetHead( LinkQueue Q, QElemType &e );
    // 若队列不空，则用 e 返回 Q 的队头元素，并返回 OK；否则返回 ERROR
Status EnQueue( LinkQueue &Q, QElemType e );
    // 插入元素 e 为 Q 的新的队尾元素
Status DeQueue( LinkQueue &Q, QElemType &e );
    // 若队列不空，则删除 Q 的队头元素，用 e 返回其值，并返回 OK；否则返回 ERROR
Status QueueTraverse( LinkQueue Q, Status (*visit)(QElemType &e) );
    // 从队头到队尾依次对队列 Q 中每个元素调用函数 visit()。一旦 visit() 失败，则操作失败

#endif