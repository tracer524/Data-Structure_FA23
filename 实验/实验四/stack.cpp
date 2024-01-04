#include "Stack.hpp"
#include <iostream>

using namespace std;

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