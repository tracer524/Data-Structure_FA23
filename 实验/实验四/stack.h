# define STACK_INIT_SIZE 100
# define STACKINCREMENT  10

#include <iostream>
#include "define.h"

using namespace std;

typedef int SElemType;

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
