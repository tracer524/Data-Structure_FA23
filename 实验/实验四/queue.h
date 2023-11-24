#include <iostream>
#include "define.h"

using namespace std;

typedef int QElemType;

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
